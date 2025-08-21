import platform
from neuron import h


def run_simple_test():
    """Простой тест для проверки основной функциональности"""
    print(f"Platform: {platform.system()}")
    print(f"NEURON version: {h.nrnversion()}")

    # Простая симуляция без MPI
    h.load_file("stdrun.hoc")

    # Создаем простую ячейку
    soma = h.Section()
    soma.L = soma.diam = 10
    soma.insert('hh')

    # Стимул
    stim = h.IClamp(soma(0.5))
    stim.delay = 10
    stim.dur = 100
    stim.amp = 0.3

    # Запись
    v = h.Vector()
    t = h.Vector()
    v.record(soma(0.5)._ref_v)
    t.record(h._ref_t)

    # Симуляция
    h.tstop = 200
    h.finitialize(-65)

    print("Starting simple simulation...")
    h.run()
    print(f"Simulation completed. Final time: {h.t}")

    return len(t) > 0


if __name__ == '__main__':
    if run_simple_test():
        print("✅ Basic NEURON functionality works")
    else:
        print("❌ Basic NEURON test failed")