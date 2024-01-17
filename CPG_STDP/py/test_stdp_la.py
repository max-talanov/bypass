import random
import os
import sys
import bokeh
from neuron import h, gui
from bioaffrat import bioaffrat
from interneuron import interneuron
import numpy as np

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show

sys.path.append('../')
my_path = os.path.abspath('')

themes = 'light_minimal'


def our_stim():
    # Настройка симуляции
    h.dt = 0.1
    h.tstop = 100

    threshold = 10  # Set voltage threshold
    delay = 1  # Set connection delay

    cells = []

    netstim = h.NetStim()
    netstim.number = 30  # Количество генерируемых спайков
    netstim.start = 0  # Время начала генерации спайков
    netstim.interval = 10  # Интервал между спайками (в мс)
    N = 50

    cell_la = bioaffrat()
    cell_RG = interneuron()

    nsyn = random.randint(5, 10)
    for i in range(nsyn):
        print('Я в первом цикле')
        nc_ex_stim = h.NetCon(netstim, cell_la.synlistex[i])
        nc_ex_stim.delay = delay
        nc_ex_stim.threshold = threshold
        nc_ex_stim.weight[0] = 10
        nc_es_stim = h.NetCon(netstim, cell_la.synlistees[i])
        nc_es_stim.delay = delay
        nc_es_stim.threshold = threshold
        nc_es_stim.weight[0] = 10
        nc_in_stim = h.NetCon(netstim, cell_la.synlistinh[i])
        nc_in_stim.delay = delay
        nc_in_stim.threshold = threshold
        nc_in_stim.weight[0] = 10
    # ncells = 2
    # cells = []
    # for _ in range(ncells):
    #     cell = h.Section(name='hhcell')
    #     cell.insert('hh')
    #     cells.append(cell)
    # synapses = []
    # for cell in cells:
    #     syn = h.ExpSyn(cell(1))  # Создание синапса
    #     syn.tau = 0.5  # Время константы синапса
    #     syn.e = 0  # Реверсивный потенциал
    #     synapses.append(syn)

    # Соединяем нейроны синаптическими связями
    # for i in range(1, ncells):
    #     nc = h.NetCon(cells[i - 1](0.5)._ref_v, synapses[i], sec=cells[i - 1])
    #     nc.weight[0] = 1  # Вес синапса
    #     nc.delay = 1  # Задержка синапса
    # # Подключение NetStim к первому нейрону
    # ncstim = h.NetCon(netstim, synapses[0])
    # ncstim.weight[0] = 10

    weight_changes = h.Vector()
    time = h.Vector()

    for i in range(nsyn):
        print('Я во втором цикле')
        #cell_la.node[len(cell_la.node) - 1](0.5)._ref_v
        nc = h.NetCon(cell_la.soma(0.5)._ref_v,
                      cell_RG.synlistexstdp[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_la.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_la.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_la.soma
                          )
        pstsyn = h.NetCon(cell_RG.axon(1)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_RG.axon
                          )
        h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        # Create array to store weight changes

        weight_changes.record(stdpmech._ref_synweight)
        print(weight_changes)
        time.record(h._ref_t)

        # Run the simulation
    h.run()

    return weight_changes, time


if __name__ == '__main__':
    pc = h.ParallelContext()

    weight_changes, time = our_stim()

    # Convert weight_changes to a NumPy array
    weight_changes_array = np.array(weight_changes.as_numpy())
    time_array = np.array(time.as_numpy())

    figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
    output_file('change_res.html')
    figur.line(time_array, weight_changes_array, line_width=2)

    show(figur)