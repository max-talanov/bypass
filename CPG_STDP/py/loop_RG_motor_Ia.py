import random
import os
import sys
import bokeh
from neuron import h, gui
from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle
import numpy as np

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show


themes = 'light_minimal'

speed = 50 # duration of layer 25 = 21 cm/s; 50 = 15 cm/s; 125 = 6 cm/s
#100 Hz is the motor cortex frequency
bs_fr = 100 #40 # frequency of brainstem inputs
versions = 1

step_number = 2 
CV_0_len = 12 
one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = 25 + one_step_time * step_number
cfr = 200
c_int = 1000 / cfr

def stim_creation(nsyn, cell_type, netstim, delay, threshold):
    for i in range(nsyn):
        print('Я в первом цикле')
        nc_ex_stim = h.NetCon(netstim, cell_type.synlistex[i])
        nc_ex_stim.delay = delay
        nc_ex_stim.threshold = threshold
        nc_ex_stim.weight[0] = 10
        '''nc_es_stim = h.NetCon(netstim, cell_type.synlistees[i])
        nc_es_stim.delay = delay
        nc_es_stim.threshold = threshold
        nc_es_stim.weight[0] = 10
        nc_in_stim = h.NetCon(netstim, cell_type.synlistinh[i])
        nc_in_stim.delay = delay
        nc_in_stim.threshold = threshold
        nc_in_stim.weight[0] = 10'''
        return nc_ex_stim #, nc_es_stim, #nc_in_stim

def our_stim():
    # Настройка симуляции
    h.dt = 0.1
    h.tstop = time_sim

    threshold = 10  # Set voltage threshold
    delay = 1  # Set connection delay

    cells = []

    netstim = h.NetStim()
    #netstim.number = time_sim  # Количество генерируемых спайков
    netstim.start = 0  # Время начала генерации спайков
    netstim.interval = c_int  # Интервал между спайками (в мс)
    N = 50

    cell_cut = bioaffrat()
    cell_RG = interneuron()
    cell_Ia = bioaffrat()
    cell_muscle = muscle()
    cell_moto = motoneuron(1)
    
    cell_types = [cell_cut, cell_RG, cell_Ia, cell_muscle, cell_moto]
    
    nsyn = random.randint(5, 10)
    
    stim_list = []
    for cell_type in cell_types:
        stim_list.append(stim_creation(nsyn, cell_type, netstim, delay, threshold))
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

    weight_changes_cut_RG = h.Vector()
    weight_changes_Ia_RG = h.Vector()
    weight_changes_m_cut = h.Vector()
    weight_changes_m_Ia = h.Vector()
    weight_changes_RG_moto = h.Vector()
    weight_changes_moto_m = h.Vector()
    weight_changes_Ia_moto = h.Vector()
    time = h.Vector()

    for i in range(nsyn):
        print('Я во втором цикле')
        #cell_la.node[len(cell_la.node) - 1](0.5)._ref_v
        nc_cut_RG = h.NetCon(cell_cut.soma(0.5)._ref_v,
                      cell_RG.synlistexstdp[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_cut.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_cut.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_cut.soma
                          )
        pstsyn = h.NetCon(cell_RG.axon(1)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_RG.axon
                          )
        h.setpointer(nc_cut_RG._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        # Create array to store weight changes

        weight_changes_cut_RG.record(stdpmech._ref_synweight)
        
        nc_Ia_RG = h.NetCon(cell_Ia.soma(0.5)._ref_v,
                      cell_RG.synlistex[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_Ia.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_Ia.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_Ia.soma
                          )
        pstsyn = h.NetCon(cell_RG.axon(1)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_RG.axon
                          )
        h.setpointer(nc_Ia_RG._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        
        weight_changes_Ia_RG.record(stdpmech._ref_synweight)
        
        nc_m_cut = h.NetCon(cell_muscle.soma(0.5)._ref_v,
                      cell_cut.synlistex[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_muscle.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_muscle.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_muscle.soma
                          )
        pstsyn = h.NetCon(cell_cut.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_cut.soma
                          )
        h.setpointer(nc_m_cut._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        
        weight_changes_m_cut.record(stdpmech._ref_synweight)
        
        nc_m_Ia = h.NetCon(cell_muscle.soma(0.5)._ref_v,
                      cell_Ia.synlistex[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_muscle.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_muscle.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_muscle.soma
                          )
        pstsyn = h.NetCon(cell_Ia.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_Ia.soma
                          )
        h.setpointer(nc_m_Ia._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        
        weight_changes_m_Ia.record(stdpmech._ref_synweight)
        
        nc_RG_moto = h.NetCon(cell_RG.soma(0.5)._ref_v,
                      cell_moto.synlistex[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_RG.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_RG.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_RG.soma
                          )
        pstsyn = h.NetCon(cell_moto.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_moto.soma
                          )
        h.setpointer(nc_RG_moto._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        weight_changes_RG_moto.record(stdpmech._ref_synweight)
        
        nc_moto_m = h.NetCon(cell_moto.soma(0.5)._ref_v,
                      cell_muscle.synlistex[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_moto.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_moto.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_moto.soma
                          )
        pstsyn = h.NetCon(cell_muscle.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_muscle.soma
                          )
        h.setpointer(nc_moto_m._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        
        weight_changes_moto_m.record(stdpmech._ref_synweight)
        
        nc_Ia_moto = h.NetCon(cell_Ia.soma(0.5)._ref_v,
                      cell_moto.synlistex[i],
                      threshold,
                      delay,
                      0.15,
                      sec = cell_Ia.soma)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_Ia.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec = cell_Ia.soma
                          )
        pstsyn = h.NetCon(cell_moto.soma(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          -2,
                          sec=cell_moto.soma
                          )
        h.setpointer(nc_Ia_moto._ref_weight[0], 'synweight', stdpmech)
        stdpmech.verbose = 2
        weight_changes_Ia_moto.record(stdpmech._ref_synweight)
        #print(weight_changes_1)
        time.record(h._ref_t)

        # Run the simulation
    h.run()

    return [np.array(weight_changes_cut_RG), np.array(weight_changes_Ia_RG), np.array(weight_changes_m_cut), np.array(weight_changes_m_Ia), np.array(weight_changes_RG_moto), np.array(weight_changes_moto_m), np.array(weight_changes_Ia_moto), np.array(time)]


if __name__ == '__main__':
    pc = h.ParallelContext()

    result = our_stim()
    time = result[7]
    values = result[:7]
    figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
    output_file(f'change_res_loop_6.html')
    figur.line(time, result[6], line_width=2)
    show(figur)
    '''for i in values:
        figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
        output_file(f'change_res_loop_{i}.html')
        figur.line(time, i, line_width=2)
    show(figur)'''