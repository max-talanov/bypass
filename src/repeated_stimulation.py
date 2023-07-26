# -*- coding: utf-8 -*-
#
# repeated_stimulation.py
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.

"""
Repeated Stimulation
--------------------

Simple example for how to repeat a stimulation protocol
using the ``origin`` property of devices.

In this example, a ``poisson_generator`` generates a spike train that is
recorded directly by a ``spike_recorder``, using the following paradigm:

1. A single trial last for 1000 ms.
2. Within each trial, the ``poisson_generator`` is active from 100 ms to 500 ms.

We achieve this by defining the `start` and `stop` properties of the
generator to 100 ms and 500 ms, respectively, and setting the ``origin`` to the
simulation time at the beginning of each trial. Start and stop are interpreted
relative to the ``origin``.

"""

###############################################################################
# First, the modules needed for simulation and analysis are imported.


import nest
import nest.raster_plot
import matplotlib.pyplot as plt
import logging


# Functions
def get_V3_rate(phase, lo, mid, hi) -> float:
    if 5 < phase < 9:
        return hi
    elif 4 < phase < 10:
        return mid
    else:
        return lo


def identity_cut_chunk(step, hi, lo):
    ## chunk_number
    chunk_number = [0]
    if step < 2:
        chunk_number = [0]
    elif step < 3:
        chunk_number = [0, 1]
    elif step < 4:
        chunk_number = [1]
    elif step < 6:
        chunk_number = [1, 2]
    elif step < 7:
        chunk_number = [2]
    elif step < 8:
        chunk_number = [2, 3]
    elif step < 10:
        chunk_number = [3]
    return chunk_number, hi


FORMAT = '%(asctime)s %(message)s'
logging.basicConfig(format=FORMAT)
log = logging.getLogger("Cur")
###############################################################################
# Second, we set the parameters so the ``poisson_generator`` generates 1000
# spikes per second and is active from 100 to 500 ms


rate = 200.0  # generator rate in spikes/s
start = 0.0  # start of simulation relative to trial start, in ms
stop = 1000.0  # end of simulation relative to trial start, in ms

###############################################################################
# The simulation is supposed to take 1s (1000 ms) and is repeated 5 times

trial_duration = 1000.0  # trial duration, in ms
phase_duration = 100.0
simulation_hill_toe_phases = 4
num_phases = 10
num_trials = 5  # number of trials to perform
v3F_num = 200
v3F_hi = 200.0  # Hz spiking rate
v3F_mid = 100.0
v3F_lo = 50.0  # Hz spiking rate
bs_num = 100
cut_num = 100

cut_lo = 5.0  # Hz spiking rate
cut_hi = 50.0  # Hz spiking rate

cut_chunk = int(cut_num/simulation_hill_toe_phases)

###############################################################################
# Third, the network is set up.  We reset the kernel and create a
# ``poisson_generator``, in which the handle is stored in `pg`.
#
# The parameters for rate and start and stop of activity are given as optional
# parameters in the form of a dictionary.


nest.ResetKernel()
# pg_params = {"rate": rate, "start": start, "stop": stop}
# g_params = {"start": start, "stop": stop, "rate_times": [1, 600, 800], "rate_values": [50, 200, 50]}
v3F_g_params = {"rate": v3F_lo}
cut_g_params = {"rate": cut_lo}
## inhomogeneous_poisson_generator
# pg = nest.Create("poisson_generator", bs_num, params=pg_params)
pg = nest.Create("poisson_generator", bs_num, params=v3F_g_params)
cut_fiber = nest.Create("poisson_generator", cut_num, params=cut_g_params)
v3F = nest.Create("hh_psc_alpha_clopath", v3F_num)

###############################################################################
# The ``spike_recorder`` is created and the handle stored in `sr`.

sr = nest.Create("spike_recorder")

###############################################################################
# The ``Connect`` function connects the nodes so spikes from pg are collected by
# the ``spike_recorder`` `sr`

# nest.Connect(pg, sr)
# nest.Connect(pg, v3F)
# nest.Connect(v3F, sr)
nest.Connect(cut_fiber, sr)

###############################################################################
# Before each trial, we set the ``origin`` of the ``poisson_generator`` to the
# current simulation time. This automatically sets the start and stop time of
# the ``poisson_generator`` to the specified times with respect to the origin.
# The simulation is then carried out for the specified time in trial_duration.


for n in range(num_trials):
    for ph in range(num_phases):
        pg.origin = nest.biological_time
        rate = get_V3_rate(ph, v3F_lo, v3F_mid, v3F_hi)
        log.warning(rate)
        pg.rate = rate

        cut_fiber[:].rate = cut_lo
        cut_chunk_number, cut_freq = identity_cut_chunk(ph, cut_hi, cut_lo)
        for chn in cut_chunk_number:
            ## log.info(str(chn*cut_chank) + ": " + str((chn+1)*cut_chank-1))
            cut_fiber[chn * cut_chunk:(chn + 1) * cut_chunk - 1].rate = cut_freq

        nest.Simulate(phase_duration)

###############################################################################
# Now we plot the result, including a histogram using the ``nest.raster_plot``
# function. Note: The histogram will show spikes seemingly located before
# 100 ms into each trial. This is due to sub-optimal automatic placement of
# histogram bin borders.

nest.raster_plot.from_device(sr, hist=True, hist_binwidth=100.0, title="Repeated stimulation by Poisson generator")
plt.show()
