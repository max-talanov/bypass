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

'''
network topology https://github.com/max-talanov/bypass/blob/main/figs/CPG_feedback_loops.png
'''

speed = 50


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
        self.stims = []

        self.stdpmechs = []
        self.netcons = []
        self.stimnclist = []

        self.presyns = []
        self.postsyns = []

        self.weight_changes_vectors = []
        self.time_t_vectors = []

        '''Create neurons'''
        self.Ia_aff_E = self.addpool(self.nAff, neurontype="aff")
        self.Ia_aff_F = self.addpool(self.nAff, neurontype="aff")
        self.RG_E = self.addpool(self.nInt, neurontype="int")
        self.RG_F = self.addpool(self.nInt, neurontype="int")
        self.muscle_E = self.addpool(self.nMn * 30, "muscle")
        self.muscle_F = self.addpool(self.nMn * 30, "muscle")
        self.mns_E = self.addpool(self.nMn, neurontype="moto")
        self.mns_F = self.addpool(self.nMn, neurontype="moto")
        self.R_E = self.addpool(self.nInt, neurontype="int")
        self.R_F = self.addpool(self.nInt, neurontype="int")
        self.Ia_E = self.addpool(self.nAff, neurontype="aff")
        self.Ia_F = self.addpool(self.nAff, neurontype="aff")

        '''Create generator'''
        # self.generator(self.Ia_aff_E, weight=0.3)
        self.Iagener_E = self.addIagener(self.muscle_E, self.muscle_E, 10, weight=20)
        self.Iagener_F = self.addIagener(self.muscle_F, self.muscle_F, speed * 6, weight=20)

        '''Create connectcells'''
        self.genconnect(self.Iagener_E, self.Ia_aff_E, 0.5, 1, False, 5)
        self.genconnect(self.Iagener_F, self.Ia_aff_F, 1.5, 1, False, 15)
        self.connectcells(self.Ia_aff_E, self.RG_E, weight=0.001, stdptype=True)
        self.connectcells(self.Ia_aff_F, self.RG_F, weight=0.001, stdptype=True)
        '''Ia2motor'''
        self.connectcells(self.Ia_aff_E, self.mns_E, 1.55, 1.5)
        self.connectcells(self.Ia_aff_F, self.mns_F, 0.5, 1.5)

        self.connectcells(self.RG_E, self.mns_E, 2.75, 3)
        self.connectcells(self.RG_F, self.mns_F, 2.75, 3)
        self.connectcells(self.mns_E, self.R_E, 0.00015, 1)
        self.connectcells(self.mns_F, self.R_F, 0.00015, 1)
        self.connectcells(self.R_E, self.mns_E, 0.00015, 1, inhtype=True)
        self.connectcells(self.R_F, self.mns_F, 0.00015, 1, inhtype=True)
        self.connectcells(self.R_E, self.Ia_E, 0.001, 1, inhtype=True)
        self.connectcells(self.R_F, self.Ia_F, 0.001, 1, inhtype=True)
        self.connectcells(self.Ia_aff_E, self.Ia_E, 0.008, 1)
        self.connectcells(self.Ia_aff_F, self.Ia_F, 0.008, 1)
        self.connectcells(self.mns_E, self.muscle_E, 15.5, 2, N=45)
        self.connectcells(self.mns_F, self.muscle_F, 15.5, 2, N=45)

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
                nc_es_stim = h.NetCon(netstim, cell.synlistees[i])
                nc_es_stim.delay = self.delay
                nc_es_stim.weight[0] = weight
                self.netcons.append(nc_es_stim)

    def connectcells(self, pre_cells, post_cells, weight=1.0, delay=1, threshold=10, N=50, inhtype=False,
                     stdptype=False):
        nsyn = 5
        ids = set()
        for post in post_cells:
            for i in range(nsyn):
                id = random.randint(0, len(pre_cells) - 1)
                if len(ids) == 0:
                    ids.add(id)
                else:
                    while id in ids:
                        id = random.randint(0, len(pre_cells) - 1)
                    ids.add(id)
                if stdptype:
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

    def addIagener(self, mn, mn2, start, weight=1.0):
        '''
        Creates self.Ia generators and returns generator gids
        Parameters
        ----------
        mn:
            motor neurons of agonist muscle that contract spindle
        mn2:
            motor neurons of antagonist muscle that extend spindle
        start: int
            generator start up
        num: int
            number in pool
        w_in: int
            weight of the connection
        Returns
        -------
        gids: list
            generators gids
        '''
        id_moto = random.randint(0, len(mn) - 1)
        id_moto2 = random.randint(0, len(mn2) - 1)
        moto = self.muscles[id_moto]
        moto2 = self.muscles[id_moto2]
        stim = h.IaGenerator(0.5)
        stim.start = start
        h.setpointer(moto.muscle_unit(0.5)._ref_F_fHill, 'fhill', stim)
        h.setpointer(moto2.muscle_unit(0.5)._ref_F_fHill, 'fhill2', stim)
        self.stims.append(stim)
        ncstim = h.NetCon(stim, None)
        ncstim.weight[0] = weight
        self.netcons.append(ncstim)

        return stim

    def genconnect(self, gen, afferents, weight, delay, inhtype=False, N=50):
        nsyn = random.randint(N, N + 5)
        for cell in afferents:
            for j in range(nsyn):
                if inhtype:
                    syn = cell.synlistinh[j]
                else:
                    syn = cell.synlistees[j]
                nc = h.NetCon(gen, syn)
                self.stimnclist.append(nc)
                nc.delay = random.gauss(delay, delay / 5)
                nc.weight[0] = random.gauss(weight, weight / 6)


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
    h.tstop = 25
    cpg = CPG()

    h.run()

    w = cpg.weight_changes_vectors
    t = cpg.time_t_vectors

    draw(w, t)
