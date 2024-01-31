import random
import os
import sys
import bokeh
from neuron import h, gui
import time
from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle
import numpy as np

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show

sys.path.append('../')
my_path = os.path.abspath('')

themes = 'light_minimal'
nInt = 5
nAff = 12
nMn = 21
N = 5

weight_changes = h.Vector()
time_t = h.Vector()


class CPG:
    def __init__(self):
        self.interneurons = []
        self.motoneurons = []
        self.muscles = []
        self.afferents = []
        self.RG_Es = []  # Rhythm generators of extensors
        self.RG_Fs = []  # Rhythm generators of flexor



        self.Ia_aff_E = self.addpool(1, neurontype="aff")
        self.mns_E = self.addpool(nMn, neurontype="moto")
        self.RG_E = self.addpool(1, neurontype="int")
        self.R_E = self.addpool(nInt, neurontype="int")
        self.Ia_E = self.addpool(nAff, neurontype="aff")

        generator(self.Ia_aff_E)

        # connectcells(self.Ia_aff_E, self.mns_E, 1.5, 1)
        connectcells(self.Ia_aff_E, self.RG_E, 0.03, 1, stdptype=True)
        # connectcells(self.Ia_aff_E, self.Ia_E, 0.5, 1)
        # connectcells(self.RG_E, self.mns_E, 0.8, 1)
        # connectcells(self.mns_E, self.R_E, 0.5, 1)
        # connectcells(self.R_E, self.mns_E, 0.5, 1, inhtype=True)
        # connectcells(self.R_E, self.Ia_E, 0.8, 1, inhtype=True)

    def addpool(self, num, name="test", neurontype="int"):

        gids = []
        gid = 0
        if neurontype.lower() == "delay":
            delaytype = True
        else:
            delaytype = False

        if neurontype.lower() == "moto":
            diams = motodiams(num)
        cells = []
        for i in range(num):
            if neurontype.lower() == "moto":
                cell = motoneuron(diams[i])
                self.motoneurons.append(cell)
            elif neurontype == "aff":
                cell = bioaffrat()
                self.afferents.append(cell)
            elif neurontype == "muscle":
                cell = muscle()
                self.muscles.append(cell)
            else:
                cell = interneuron(delaytype)
                self.interneurons.append(cell)
            cells.append(cell)

            # while pc.gid_exists(gid) != 0:
            #     gid += 1
            # gids.append(gid)
            # pc.set_gid2node(gid, rank)
            # nc = cell.connect2target(None)
            # pc.cell(gid, nc)
        return cells


def connectcells(pre, post, weight, delay=1, threshold=10, inhtype=False, stdptype=False, N=30):
    # nsyn = random.randint(N - 15, N)
    nsyn = 1
    for i in post:
        for j in range(nsyn):
            print('Я во втором цикле')
            # cell_la.node[len(cell_la.node) - 1](0.5)._ref_v
            if stdptype:
                id = random.randint(0, len(pre))
                id = 0
                nc = h.NetCon(pre[id].soma(0.5)._ref_v,
                              i.synlistexstdp[j],
                              threshold,
                              delay,
                              weight,
                              sec=pre[id].soma)
                dummy = h.Section()  # Create a dummy section to put the point processes in
                stdpmech = h.STDP(0, dummy)
                presyn = h.NetCon(pre[id].soma(0.5)._ref_v,
                                  stdpmech,
                                  threshold,
                                  delay,
                                  2,
                                  sec=pre[id].soma
                                  )
                pstsyn = h.NetCon(i.soma(1)._ref_v,
                                  stdpmech,
                                  threshold,
                                  delay,
                                  -2,
                                  sec=i.soma
                                  )
                h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
                stdpmech.verbose = 2
                # Create array to store weight changes
                time.sleep(3)
                weight_changes.record(stdpmech._ref_synweight)

                time_t.record(h._ref_t)
            else:
                id = random.randint(0, len(pre)-1)
                if inhtype:
                    nc = h.NetCon(pre[id].soma(0.5)._ref_v,
                                  i.synlistinh[j],
                                  threshold,
                                  delay,
                                  weight,
                                  sec=pre[id].soma)
                else:
                    nc = h.NetCon(pre[id].soma(0.5)._ref_v,
                                  i.synlistex[j],
                                  threshold,
                                  delay,
                                  weight,
                                  sec=pre[id].soma)


def generator(cell, weight=10, delay=1):
    netstim = h.NetStim()
    netstim.number = 30  # Количество генерируемых спайков
    netstim.start = 0  # Время начала генерации спайков
    netstim.interval = 10  # Интервал между спайками (в мс)

    nsyn = random.randint(15, 30)
    for i in cell:
        for j in range(nsyn):
            print('Я в первом цикле')
            nc_es_stim = h.NetCon(netstim, i.synlistees[j])
            nc_es_stim.delay = delay
            nc_es_stim.weight[0] = weight
            nc_in_stim = h.NetCon(netstim, i.synlistinh[j])
            nc_in_stim.delay = delay
            nc_in_stim.weight[0] = weight

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
        nc_es_stim = h.NetCon(netstim, cell_la.synlistees[i])
        nc_es_stim.delay = delay
        nc_es_stim.weight[0] = 0.3
        nc_in_stim = h.NetCon(netstim, cell_la.synlistinh[i])
        nc_in_stim.delay = delay
        nc_in_stim.weight[0] = 0.3
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
        # cell_la.node[len(cell_la.node) - 1](0.5)._ref_v
        nc = h.NetCon(cell_la.axon(0.5)._ref_v,
                      cell_RG.synlistexstdp[i],
                      threshold,
                      delay,
                      0.15,
                      sec=cell_la.axon)
        dummy = h.Section()  # Create a dummy section to put the point processes in
        stdpmech = h.STDP(0, dummy)
        presyn = h.NetCon(cell_la.axon(0.5)._ref_v,
                          stdpmech,
                          threshold,
                          delay,
                          2,
                          sec=cell_la.axon
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


def motodiams(number):
    nrn_number = number
    standby_percent = 70
    active_percent = 100 - standby_percent

    standby_size = int(nrn_number * standby_percent / 100)
    active_size = nrn_number - standby_size

    loc_active, scale_active = 27, 3
    loc_stanby, scale_stanby = 44, 4

    x2 = np.concatenate([np.random.normal(loc=loc_active, scale=scale_active, size=active_size),
                         np.random.normal(loc=loc_stanby, scale=scale_stanby, size=standby_size)])

    return x2


if __name__ == '__main__':
    # pc = h.ParallelContext()
    #
    # weight_changes, time = our_stim()
    h.dt = 0.1
    h.tstop = 100

    cpg = CPG()

    h.run()


    # Convert weight_changes to a NumPy array
    weight_changes_array = np.array(weight_changes.as_numpy())
    time_array = np.array(time_t.as_numpy())

    figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
    output_file('change_res.html')
    figur.line(time_array, weight_changes_array, line_width=2)

    show(figur)
