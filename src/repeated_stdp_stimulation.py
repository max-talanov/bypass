import nest
import nest.raster_plot
import matplotlib.pyplot as plt
import logging
import numpy as np


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
logging.basicConfig(format=FORMAT, level=logging.INFO)
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
num_steps = 5  # 5  # number of trials to perform

v3F_num = 200
v3F_hi = 200.0  # Hz spiking rate
v3F_mid = 100.0
v3F_lo = 50.0  # Hz spiking rate
bs_num = 100

cut_num = 100
cut_lo = 5.0  # Hz spiking rate
cut_hi = 50.0  # 200.0 # 50.0  # Hz spiking rate
cut_chunk = int(cut_num / simulation_hill_toe_phases)

## synapses
d = 1.0
Je = 100.0 # 20.0
Ke = 20

## stdp parameters
alpha_min = 0.1
alpha_max = 2.
w_min = 0.5
w_max = 5.
w_mean = 10.0
w_std = 5.0
delay_def = 1.0

###############################################################################
# Third, the network is set up.  We reset the kernel and create a
# ``poisson_generator``, in which the handle is stored in `pg`.
#
# The parameters for rate and start and stop of activity are given as optional
# parameters in the form of a dictionary.

nest.ResetKernel()
nest.total_num_virtual_procs = 15
# pg_params = {"rate": rate, "start": start, "stop": stop}
# g_params = {"start": start, "stop": stop, "rate_times": [1, 600, 800], "rate_values": [50, 200, 50]}
v3F_g_params = {"rate": v3F_lo}
cut_g_params = {"rate": cut_lo}
## Generators
bs_generator = nest.Create("poisson_generator", bs_num, params=v3F_g_params)
cut_fiber_generator = nest.Create("poisson_generator", cut_num, params=cut_g_params)

## Nuclei
v3F_neurons = nest.Create("hh_psc_alpha_clopath", v3F_num)
bs_neurons = nest.Create("hh_psc_alpha_clopath", bs_num)

###############################################################################
# The ``spike_recorder`` is created and the handle stored in `sr`.
bs_sr = nest.Create("spike_recorder")
bs_neurons_sr = nest.Create("spike_recorder")
v3F_neurons_sr = nest.Create("spike_recorder")
v3F_neurons_wr = nest.Create("weight_recorder")

###############################################################################
# The ``Connect`` function connects the nodes so spikes from pg are collected by
# the ``spike_recorder`` `sr`
nest.Connect(bs_generator, bs_sr)
nest.Connect(bs_neurons, bs_neurons_sr)
nest.Connect(v3F_neurons, v3F_neurons_sr)
# generator w neurons
conn_dict_ex = {"rule": "fixed_indegree", "indegree": Ke}
gen2neuron_dict = {"rule": "all_to_all"}
syn_dict_ex = {"delay": d, "weight": Je}
nest.Connect(bs_generator, bs_neurons, gen2neuron_dict, syn_dict_ex)

neuron2neuron_stdp_dict = {"rule": "all_to_all"}
nest.CopyModel("stdp_synapse", "stdp_synapse_rec", {"weight_recorder": v3F_neurons_wr[0]})
syn_stdp_dict = {"synapse_model": "stdp_synapse_rec",
            "alpha": nest.random.uniform(min=alpha_min, max=alpha_max),
            "weight": nest.random.lognormal(mean=w_mean, std=w_std),
            "delay": delay_def
            }
nest.Connect(bs_neurons, v3F_neurons, neuron2neuron_stdp_dict, syn_stdp_dict)

###############################################################################
# Before each trial, we set the ``origin`` of the ``poisson_generator`` to the
# current simulation time. This automatically sets the start and stop time of
# the ``poisson_generator`` to the specified times with respect to the origin.
# The simulation is then carried out for the specified time in trial_duration.

log.info('Simulation started ...')
for n in range(num_steps):
    log.info("Step = " + str(n))
    for ph in range(num_phases):
        bs_generator.origin = nest.biological_time
        rate = get_V3_rate(ph, v3F_lo, v3F_mid, v3F_hi)
        log.debug("Rate = " + str(rate))
        bs_generator.rate = rate
        cut_fiber_generator[:].rate = cut_lo
        cut_chunk_number, cut_freq = identity_cut_chunk(ph, cut_hi, cut_lo)
        for chn in cut_chunk_number:
            ## log.info(str(chn*cut_chank) + ": " + str((chn+1)*cut_chank-1))
            cut_fiber_generator[chn * cut_chunk:(chn + 1) * cut_chunk - 1].rate = cut_freq
        nest.Simulate(phase_duration)

log.info('Simulation completed ...')
###############################################################################
# Now we plot the result, including a histogram using the ``nest.raster_plot``
# function. Note: The histogram will show spikes seemingly located before
# 100 ms into each trial. This is due to sub-optimal automatic placement of
# histogram bin borders.

#nest.raster_plot.from_device(bs_sr, hist=True, hist_binwidth=100.0, title="brainstem generator spikes")
#plt.show()

# nest.raster_plot.from_device(bs_neurons_sr, hist=True, hist_binwidth=100.0, title="brainstem spikes")
# plt.show()

#V3 spikes
nest.raster_plot.from_device(v3F_neurons_sr, hist=True, hist_binwidth=100.0, title="v3F spikes")
plt.show()

# plot results
fs = 22
lw = 2.5
#V3 weights
senders = v3F_neurons_wr.events["senders"]
targets = v3F_neurons_wr.events["targets"]
weights = v3F_neurons_wr.events["weights"]
times = v3F_neurons_wr.events["times"]
# synaptic weights
plt.figure(figsize=(20, 15))
plt.subplot(111)
plt.plot(times[100:], weights[100:], 'tab:purple')
plt.tight_layout()
plt.show()

log.info('Completed draw')
