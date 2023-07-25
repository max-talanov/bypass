import pytest
import nest
import numpy as np
import matplotlib.pyplot as plt
import logging

FORMAT = '%(asctime)s %(message)s'
logging.basicConfig(format=FORMAT)

nest.set_verbosity("M_WARNING")
nest.ResetKernel()

v3F_num = 200
simtime = 1000

# Amplitude range, in pA
dcfrom = 0
dcstep = 20
dcto = 2000

h = 0.1  # simulation step size in mS


class TestBS:

    def setup(self):
        self.v3F = nest.Create("hh_psc_alpha_clopath", v3F_num)
        self.sr = nest.Create("spike_recorder")
        self.sr.record_to = "memory"
        nest.Connect(self.v3F, self.sr, syn_spec={"weight": 1.0, "delay": h})

    def test_simulation(self):
        self.setup()
        # Simulation loop
        n_data = int(dcto / float(dcstep))
        amplitudes = np.zeros(n_data)
        event_freqs = np.zeros(n_data)
        log = logging.getLogger("Cur")

        log.warning("Sim started ...")

        for i, amp in enumerate(range(dcfrom, dcto, dcstep)):
            self.v3F.I_e = float(amp)
            print(f"Simulating with current I={amp} pA")
            nest.Simulate(1000)  # one second warm-up time for equilibrium state
            self.sr.n_events = 0  # then reset spike counts
            nest.Simulate(simtime)  # another simulation call to record firing rate

            n_events = self.sr.n_events
            amplitudes[i] = amp
            event_freqs[i] = n_events / (simtime / 1000.0)

        log.warning("Simulation is over ...")
        plt.plot(amplitudes, event_freqs)
        plt.show()

