import random
import bokeh
import sys, os

from CPG_STDP.py.bioaffrat import bioaffrat
from CPG_STDP.py.interneuron import interneuron
from neuron import h
import numpy as np

from CPG_STDP.py.motoneuron import motoneuron
from CPG_STDP.py.muscle import muscle

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show

sys.path.append('../')
my_path = os.path.abspath('')
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')


class CPG:
    def __init__(self):
        self.threshold = 10
        self.delay = 1
        self.nAff = 12
        self.nInt = 5
        self.nMn = 21
        self.afferents = []
        self.interneurons = []
        self.motoneurons = []
        self.muscles = []

        self.netstims = []

        self.stdpmechs = []
        self.netcons = []

        self.presyns = []
        self.postsyns = []

        self.weight_changes_vectors = []
        self.time_t_vectors = []

        '''Create neurons'''
        self.Ia_aff_E = self.addpool(self.nAff, neurontype="aff")
        self.RG_E = self.addpool(self.nInt, neurontype="int")
        self.muscle_E = self.addpool(self.nMn * 30, "muscle")
        self.mns_E = self.addpool(self.nMn, neurontype="moto")
        self.R_E = self.addpool(self.nInt, neurontype="int")
        self.Ia_E = self.addpool(self.nAff, neurontype="aff")

        '''Create generator'''
        self.generator(self.Ia_aff_E, weight=0.3)

        '''Create connectcells'''
        self.connectcells(self.Ia_aff_E, self.RG_E, weight=0.13, stdptype=True)
        self.connectcells(self.Ia_aff_E, self.mns_E, weight=0.01)
        self.connectcells(self.RG_E, self.mns_E, weight=0.02)
        self.connectcells(self.mns_E, self.R_E, weight=0.02)
        self.connectcells(self.R_E, self.mns_E, weight=0.05, inhtype=True)
        self.connectcells(self.R_E, self.Ia_E, weight=0.03, inhtype=True)
        self.connectcells(self.Ia_aff_E, self.Ia_E, weight=0.04)

    def addpool(self, num, neurontype="int"):
        cells = []
        if neurontype.lower() == "moto":
            diams = self.motodiams(num)
        for i in range(num):
            if neurontype.lower() == "moto":
                cell = motoneuron(diams[i])
                self.motoneurons.append(cell)
            elif neurontype.lower() == "aff":
                cell = bioaffrat()
                self.afferents.append(cell)
            elif neurontype.lower() == "muscle":
                cell = muscle()
                self.muscles.append(cell)
            else:
                cell = interneuron()
                self.interneurons.append(cell)
            cells.append(cell)

        return cells

    def generator(self, cells, weight=1.0):
        netstim = h.NetStim()
        netstim.number = 30  # Количество генерируемых спайков
        netstim.start = 0  # Время начала генерации спайков
        netstim.interval = 10

        self.netstims.append(netstim)

        nsyn = 1
        for cell in cells:
            for i in range(nsyn):
                print('Я в первом цикле')
                nc_es_stim = h.NetCon(netstim, cell.synlistees[i])
                nc_es_stim.delay = self.delay
                nc_es_stim.weight[0] = weight
                self.netcons.append(nc_es_stim)

    def connectcells(self, pre_cells, post_cells, weight=1.0, delay=1, threshold=10, inhtype=False, stdptype=False):
        nsyn = 5
        for post in post_cells:
            for i in range(nsyn):
                id = random.randint(0, len(pre_cells) - 1)
                if stdptype:
                    print('Я во втором цикле')
                    # cell_la.node[len(cell_la.node) - 1](0.5)._ref_v
                    nc = h.NetCon(pre_cells[id].soma(0.5)._ref_v,
                                  post.synlistexstdp[i],
                                  threshold,
                                  delay,
                                  weight,
                                  sec=pre_cells[id].soma)
                    self.netcons.append(nc)

                    dummy = h.Section(name='i')  # Create a dummy section to put the point processes in
                    stdpmech = h.STDP(0, dummy)
                    self.stdpmechs.append(stdpmech)
                    presyn = h.NetCon(pre_cells[id].soma(0.5)._ref_v,
                                      stdpmech,
                                      threshold,
                                      delay,
                                      2,
                                      sec=pre_cells[id].soma
                                      )
                    self.presyns.append(presyn)
                    pstsyn = h.NetCon(post.soma(1)._ref_v,
                                      stdpmech,
                                      threshold,
                                      delay,
                                      -2,
                                      sec=post.soma
                                      )
                    self.postsyns.append(pstsyn)
                    h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
                    # stdpmech.verbose = 2
                    # Create array to store weight changes

                    weight_changes = h.Vector()
                    time_t = h.Vector()
                    weight_changes.record(stdpmech._ref_synweight)
                    time_t.record(h._ref_t)
                    self.weight_changes_vectors.append(weight_changes)
                    self.time_t_vectors.append(time_t)
                else:
                    if inhtype:
                        nc = h.NetCon(pre_cells[id].soma(0.5)._ref_v,
                                      post.synlistinh[i],
                                      threshold,
                                      delay,
                                      weight,
                                      sec=pre_cells[id].soma)
                        self.netcons.append(nc)
                    else:
                        nc = h.NetCon(pre_cells[id].soma(0.5)._ref_v,
                                      post.synlistex[i],
                                      threshold,
                                      delay,
                                      weight,
                                      sec=pre_cells[id].soma)
                        self.netcons.append(nc)

    def motodiams(self, number):
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


def draw(weight_changes, time_t):
    i = 0
    # Convert weight_changes to a NumPy array
    for w, t in zip(weight_changes, time_t):
        weight_changes_array = np.array(w.as_numpy())
        time_array = np.array(t.as_numpy())

        figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
        output_file(f'results_stdp/change_res_{i}.html')
        i += 1
        figur.line(time_array, weight_changes_array, line_width=2)
        show(figur)


if __name__ == '__main__':
    h.dt = 0.1
    h.tstop = 50
    cpg = CPG()

    h.run()

    w = cpg.weight_changes_vectors
    t = cpg.time_t_vectors

    draw(w, t)
