import time
import matplotlib.pyplot as plt
from neuron import h

from interneuron import interneuron

def run_one_cell(T=150.0, dt=0.025, use_istim=True):
    h.load_file("stdrun.hoc")
    h.dt = dt

    cell = interneuron()

    stim = None
    if use_istim:
        stim = h.IClamp(cell.soma(0.5))
        stim.delay = 10
        stim.dur = 50
        stim.amp = 0.1

    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(cell.soma(0.5)._ref_v)

    t0 = time.perf_counter()
    h.finitialize(-65)
    h.continuerun(T)
    t1 = time.perf_counter()

    print(f"Sim time: {T} ms, dt={dt} ms -> wall time {t1 - t0:.4f} s, steps ~ {int(T/dt)}")

    return list(t_vec), list(v_vec)

if __name__ == "__main__":
    t, v = run_one_cell(T=150.0, dt=0.025, use_istim=True)
    plt.figure()
    plt.plot(t, v)
    plt.xlabel("t (ms)")
    plt.ylabel("Vm (mV)")
    plt.title("Interneuron soma Vm")
    plt.show()