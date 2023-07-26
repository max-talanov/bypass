import nest
import numpy as np
import logging
import pickle

FORMAT = '%(asctime)s %(message)s'
logging.basicConfig(format=FORMAT)

nest.set_verbosity("M_WARNING")
nest.ResetKernel()

v3F_num = 200
simtime = 1000

# Amplitude range, in pA
dcfrom = 0
dcstep = 20
dcto = 20

h = 0.1  # simulation step size in mS

v3F = nest.Create("hh_psc_alpha_clopath", v3F_num)
sr = nest.Create("spike_recorder")
sr.record_to = "memory"
nest.Connect(v3F, sr, syn_spec={"weight": 1.0, "delay": h})

n_data = int(dcto / float(dcstep))
amplitudes = np.zeros(n_data)
event_freqs = np.zeros(n_data)
log = logging.getLogger("Cur")

log.warning("Sim started ...")

for i, amp in enumerate(range(dcfrom, dcto, dcstep)):
    v3F.I_e = float(amp)
    print(f"Simulating with current I={amp} pA")
    nest.Simulate(1000)  # one second warm-up time for equilibrium state
    sr.n_events = 0  # then reset spike counts
    nest.Simulate(simtime)  # another simulation call to record firing rate

    n_events = sr.n_events
    amplitudes[i] = amp
    event_freqs[i] = n_events / (simtime / 1000.0)
    print(amplitudes, event_freqs)

with open('bypass/pickle_/amplitudes.pkl', 'wb') as handle:
    pickle.dump(amplitudes, handle)

with open('bypass/pickle_/event_freqs.pkl', 'wb') as handle:
    pickle.dump(event_freqs, handle)

log.warning("Simulation is over ...")

