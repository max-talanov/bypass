import os
import sys

import bokeh
from neuron import h, gui
import matplotlib.pyplot as plt
import numpy as np
from interneuron import interneuron
from motoneuron import motoneuron
from bioaffrat import bioaffrat
from muscle import muscle

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show


sys.path.append('../')
my_path = os.path.abspath('')

themes = 'light_minimal'


def simple_sim():
    # Настраиваем симуляцию
    h.dt = 0.1
    h.tstop = 10000
    threshold = 1  # Set voltage threshold
    delay = 1  # Set connection delay
    ## Create cells
    dummy = h.Section(name='dummy')  # Create a dummy section to put the point processes in
    ncells = 4
    cells = []
    stdpnx = []
    for c in range(ncells): cells.append(h.IntFire4(0, sec=dummy))  # Create the cells

    netstim = h.NetStim()
    netstim.number = 25  # Количество генерируемых спайков
    netstim.start = 0  # Время начала генерации спайков
    netstim.interval = 10  # Интервал между спайками (в мс)

    # Создание NetCon для соединения NetStim с первым IntFire4 нейроном
    ncstim = h.NetCon( netstim, cells[0])
    ncstim.weight[0] = 5


    # print(stdpmech)# Create the STDP mechanism

    singlesyn = h.NetCon(cells[0], cells[1], threshold, delay, 0.11)  # Create a connection between the cells
    stdpmech = h.STDP(0, dummy)
    presyn = h.NetCon(cells[0], stdpmech, threshold, delay,
                      1)  # Feed presynaptic spikes to the STDP mechanism -- must have weight >0
    pstsyn = h.NetCon(cells[1], stdpmech, threshold, delay,
                      -1)  # Feed postsynaptic spikes to the STDP mechanism -- must have weight <0
    h.setpointer(singlesyn._ref_weight[0], 'synweight', stdpmech)
    stdpmech.verbose = 2
    # Create array to store weight changes
    weight_changes = h.Vector()
    weight_changes.record(stdpmech._ref_synweight)
    time = h.Vector()
    time.record(h._ref_t)

    # Run the simulation
    h.run()

    return weight_changes, time


def our_sim():
    # Настройка симуляции
    h.dt = 0.1
    h.tstop = 10000

    threshold = 10  # Set voltage threshold
    delay = 1  # Set connection delay

    # Создание нейронов с механизмом Hodgkin-Huxley
    ncells = 2
    cells = []
    for _ in range(ncells):
        cell = h.Section(name='hhcell')
        cell.insert('hh')
        cells.append(cell)

    # RG = interneuron(False)
    # cells.append(RG)
    #
    # la = bioaffrat()
    # cells.append(la)
    # Создание источника спайков
    netstim = h.NetStim()
    netstim.number = 25  # Количество спайков
    netstim.start = 0  # Время начала генерации спайков
    netstim.interval = 10  # Интервал между спайками (в мс)

    synapses = []
    for cell in cells:
        syn = h.ExpSyn(cell(1))  # Создание синапса
        syn.tau = 0.5  # Время константы синапса
        syn.e = 0  # Реверсивный потенциал
        synapses.append(syn)

    # Соединяем нейроны синаптическими связями
    for i in range(1, ncells):
        nc = h.NetCon(cells[i - 1](0.5)._ref_v, synapses[i], sec=cells[i - 1])
        nc.weight[0] = 1  # Вес синапса
        nc.delay = 1  # Задержка синапса
    # Подключение NetStim к первому нейрону
    ncstim = h.NetCon(netstim, synapses[0])
    ncstim.weight[0] = 10



    dummy = h.Section()
    stdpmech = h.STDP(0, dummy)
    singlesyn = h.NetCon(cells[0](0.5)._ref_v, synapses[1], threshold, delay, 0.11)
    presyn = h.NetCon(cells[0](0.5)._ref_v, stdpmech, threshold, delay, 1, sec=cells[0])  # Feed presynaptic spikes to the STDP mechanism -- must have weight >0
    pstsyn = h.NetCon(cells[1](0.5)._ref_v, stdpmech, threshold, delay, -1, sec=cells[1])  # Feed postsynaptic spikes to the STDP mechanism -- must have weight <0
    h.setpointer(singlesyn._ref_weight[0], 'synweight', stdpmech)
    stdpmech.verbose = 2
    # Create array to store weight changes
    weight_changes = h.Vector()
    weight_changes.record(stdpmech._ref_synweight)
    time = h.Vector()
    time.record(h._ref_t)

    # Run the simulation
    h.run()
    return weight_changes, time

if __name__ == "__main__":

    pc = h.ParallelContext()

    weight_changes, time = our_sim()

    # Convert weight_changes to a NumPy array
    weight_changes_array = np.array(weight_changes.as_numpy())
    time_array = np.array(time.as_numpy())

    figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
    output_file('change_res.html')
    figur.line(time_array, weight_changes_array, line_width=2)

    show(figur)
