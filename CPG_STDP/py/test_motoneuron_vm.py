import os
import sys
import time
import statistics

from neuron import h
import matplotlib.pyplot as plt

THIS_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, THIS_DIR)

from motoneuron import motoneuron


def run_one_cell(T=150.0, dt=0.025,
                 stim_amp=0.1,
                 stim_delay=10.0,
                 stim_dur=50.0,
                 v_init=-65.0):

    h.load_file("stdrun.hoc")
    h.dt = dt

    cell = motoneuron(diam=30)

    stim = h.IClamp(cell.soma(0.5))
    stim.delay = stim_delay
    stim.dur = stim_dur
    stim.amp = stim_amp

    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(cell.soma(0.5)._ref_v)

    t0 = time.perf_counter()
    h.finitialize(v_init)
    h.continuerun(T)
    t1 = time.perf_counter()

    wall = t1 - t0

    t = list(t_vec)
    v = list(v_vec)

    print(f"Sim time: {T} ms, dt={dt} ms -> wall time {wall:.4f} s")
    print(f"Vm min/max: {min(v):.2f} / {max(v):.2f} mV")

    return t, v, wall


def benchmark(n_runs=5):
    times = []
    for i in range(n_runs):
        _, _, wall = run_one_cell()
        times.append(wall)

    print("\nBenchmark:")
    print("Mean:", statistics.mean(times))
    print("Std :", statistics.stdev(times))


if __name__ == "__main__":
    t, v, wall = run_one_cell()

    plt.figure(figsize=(8, 4))
    plt.plot(t, v)
    plt.xlabel("Time (ms)")
    plt.ylabel("Membrane potential (mV)")
    plt.title("Motoneuron soma Vm")
    plt.tight_layout()
    plt.show()

    # benchmark()