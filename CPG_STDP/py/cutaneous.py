speed = 50 # duration of layer 25 = 21 cm/s; 50 = 15 cm/s; 125 = 6 cm/s
#100 Hz is the motor cortex frequency
bs_fr = 100 #40 # frequency of brainstem inputs
versions = 1

step_number = 20 # number of steps

CV_number = 6
nMN = 210 # 21 # 210 # Number of motor neurons
nAff = 120  # 120 # Number of afferents
nInt = 50 #19 # 196 # Number of neurons in interneuronal pools
N = 50 #5 #50
CV_0_len = 12 
one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = 25 + one_step_time * step_number
cfr = 200
c_int = 1000 / cfr

for layer in range(CV_number):
    '''Cutaneous pools'''
    ##self.dict_CV[layer] = self.addpool(self.ncell, "CV" + str(layer + 1), "aff")
    self.dict_CV_1[layer] = self.addpool(self.ncell, "CV" + str(layer + 1) + "_1", "aff")

    '''Rhythm generator pools'''
    self.dict_RG_E[layer] = self.addpool(self.ncell, "RG" + str(layer + 1) + "_E", "int")
    self.dict_RG_F[layer] = self.addpool(self.ncell, "RG" + str(layer + 1) + "_F", "int")
    self.RG_E.append(self.dict_RG_E[layer])
    self.RG_F.append(self.dict_RG_F[layer])

    '''RG'''
    self.RG_E = sum(self.RG_E, [])
    self.InE = self.addpool(nInt, "InE", "int")
    self.RG_F = sum(self.RG_F, [])
    self.InF = self.addpool(nInt, "InF", "int")


'''cutaneous inputs generators'''
for layer in range(CV_number):
    self.dict_C[layer] = []
    for i in range(step_number):
        self.dict_C[layer].append(self.addgener(25 + speed * layer + i * (speed * CV_number + CV_0_len),
                                                        random.gauss(cfr, cfr/10), (speed / c_int + 1)))

self.C_1 = []
self.C_0 = []
self.V0v = []

'''Generators'''
for i in range(step_number):
    self.C_0.append(self.addgener(25 + speed * 6 + i * (speed * 6 + CV_0_len), cfr, CV_0_len/c_int, False))
    ## TODO possibly we don't need this
    self.V0v.append(self.addgener(40 + speed * 6 + i * (speed * 6 + CV_0_len), cfr, 100/c_int, False))

    # self.C_0.append(self.addgener(0, cfr, (speed / c_int)))

for layer in range(CV_number):
    self.C_1.append(self.dict_CV_1[layer])
    self.C_1 = sum(self.C_1, [])
    # self.C_0 = sum(self.C_0, [])

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
        
import random
import os
import sys
import bokeh
from neuron import h, gui
from bioaffrat import bioaffrat
from interneuron import interneuron
import numpy as np

#bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show

#sys.path.append('../')
#my_path = os.path.abspath('')

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
    output_file('cutaneous_change_res.html')
    figur.line(time_array, weight_changes_array, line_width=2)

    show(figur)