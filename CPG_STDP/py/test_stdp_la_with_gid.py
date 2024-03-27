import random
import bokeh
import sys, os

from neuron import h

h.load_file('neuron.hoc')
from bioaffrat import bioaffrat
from interneuron import interneuron
import numpy as np

from motoneuron import motoneuron
from muscle import muscle

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show

sys.path.append('../')
my_path = os.path.abspath('')
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')

# paralleling NEURON stuff
pc = h.ParallelContext()
rank = int(pc.id())
nhost = int(pc.nhost())

'''
network topology https://github.com/max-talanov/bypass/blob/main/figs/CPG_feedback_loops.png
'''


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
        self.RG_E = self.addpool(self.nInt, neurontype="int")
        self.muscle_E = self.addpool(self.nMn * 30, "muscle")
        '''Create generator'''
        self.Iagener_E = self.addIagener(self.muscle_E, self.muscle_E, 10, weight=20)

        '''Create connectcells'''
        self.genconnect(self.Iagener_E, self.Ia_aff_E, 0.5, 1, False, 5)
        self.connectcells(self.Ia_aff_E, self.RG_E, weight=0.13, stdptype=True)

    def addpool(self, num, neurontype="int"):
        '''
        Creates pool of cells determined by the neurontype and returns gids of the pool
        Parameters
        ----------
        num: int
            neurons number in pool
        name: string
            the name of the pool
        neurontype: string
            int: interneuron
            delay: interneuron with 5ht
            bursting: interneuron with bursting
            moto: motor neuron
            aff: afferent
            muscle: muscle fiber
        Returns
        -------
        gids: list
            the list of cells gids
        '''
        gids = []
        gid = 0
        if neurontype.lower() == "delay":
            delaytype = True
        else:
            delaytype = False

        if neurontype.lower() == "moto":
            diams = self.motodiams(num)
        for i in range(rank, num, nhost):
            if neurontype.lower() == "moto":
                cell = motoneuron(diams[i])
                self.motoneurons.append(cell)
            elif neurontype.lower() == "aff":
                cell = bioaffrat()
                self.afferents.append(cell)
            elif neurontype.lower() == "muscle":
                cell = muscle()
                self.muscles.append(cell)
            elif neurontype.lower() == "bursting":
                cell = interneuron(False, bursting_mode=True)
                self.interneurons.append(cell)
            else:
                cell = interneuron(delaytype)
                self.interneurons.append(cell)

            while pc.gid_exists(gid) != 0:
                gid += 1
            gids.append(gid)
            pc.set_gid2node(gid, rank)
            nc = cell.connect2target(None)
            self.netcons.append(nc)
            pc.cell(gid, nc)

        # # Groups
        # if (neurontype.lower() == "muscle"):
        #     self.musclegroups.append((gids, name))
        # elif (neurontype.lower() == "moto"):
        #     self.motogroups.append((gids, name))
        # elif neurontype.lower() == "aff":
        #     self.affgroups.append((gids, name))
        # else:
        #     self.groups.append((gids, name))

        return gids

    def connectcells(self, pre_cells, post_cells, weight=1.0, delay=1, threshold=10, inhtype=False, stdptype=False):
        nsyn = 5
        for post_gid in post_cells:
            if pc.gid_exists(post_gid):
                for i in range(nsyn):
                    src_gid = random.randint(pre_cells[0], pre_cells[-1])
                    target = pc.gid2cell(post_gid)
                    if stdptype:
                        syn = target.synlistexstdp[i]
                        nc = pc.gid_connect(src_gid, syn)
                        nc.delay = delay
                        nc.weight[0] = weight
                        nc.threshold = threshold
                        pc.threshold(src_gid, threshold)
                        self.netcons.append(nc)

                        dummy = h.Section()  # Create a dummy section to put the point processes in
                        stdpmech = h.STDP(0, dummy)
                        self.stdpmechs.append(stdpmech)
                        presyn = pc.gid_connect(src_gid,
                                                stdpmech)  # threshold, delay, 1)  # Feed presynaptic spikes to the STDP mechanism -- must have weight >0
                        presyn.delay = delay
                        presyn.weight[0] = 2
                        presyn.threshold = threshold
                        self.presyns.append(presyn)
                        pstsyn = pc.gid_connect(post_gid,
                                                stdpmech)  # threshold, delay, -1)  # Feed postsynaptic spikes to the STDP mechanism -- must have weight <0
                        pstsyn.delay = delay
                        pstsyn.weight[0] = -2
                        pstsyn.threshold = threshold
                        self.postsyns.append(pstsyn)
                        pc.threshold(post_gid, threshold)
                        h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)

                        weight_changes = h.Vector()
                        time_t = h.Vector()
                        weight_changes.record(stdpmech._ref_synweight)
                        time_t.record(h._ref_t)
                        self.weight_changes_vectors.append(weight_changes)
                        self.time_t_vectors.append(time_t)
                    else:
                        if inhtype:
                            syn = target.synlistinh[i]
                            nc = pc.gid_connect(src_gid, syn)
                            nc.weight[0] = random.gauss(weight, weight / 5)
                            nc.delay = random.gauss(delay, delay / 5)
                            self.netcons.append(nc)
                        else:
                            syn = target.synlistex[i]
                            nc = pc.gid_connect(src_gid, syn)
                            nc.weight[0] = random.gauss(weight, weight / 5)
                            nc.delay = random.gauss(delay, delay / 5)
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
        Creates self.Ia generators and returns generator gid
        Parameters
        ----------
        mn: list
            motor neurons of agonist muscle that contract spindle
        mn2: list
            motor neurons of antagonist muscle that extend spindle
        start: int
            generator start up
        num: int
            number in pool
        w_in: int
            weight of the connection
        Returns
        -------
        gid: int
            generators gid
        '''
        gid = 0
        moto = pc.gid2cell(random.randint(mn[0], mn[-1]))
        moto2 = pc.gid2cell(random.randint(mn2[0], mn2[-1]))
        stim = h.IaGenerator(0.5)
        stim.start = start
        h.setpointer(moto.muscle_unit(0.5)._ref_F_fHill, 'fhill', stim)
        h.setpointer(moto2.muscle_unit(0.5)._ref_F_fHill, 'fhill2', stim)
        self.stims.append(stim)
        while pc.gid_exists(gid):
            gid += 1
        pc.set_gid2node(gid, rank)
        ncstim = h.NetCon(stim, None)
        ncstim.weight[0] = weight
        self.netcons.append(ncstim)
        pc.cell(gid, ncstim)

        return gid

    def genconnect(self, gen_gid, afferents_gids, weight, delay, inhtype=False, N=50):
        nsyn = random.randint(N, N + 5)
        for i in afferents_gids:
            if pc.gid_exists(i):
                for j in range(nsyn):
                    target = pc.gid2cell(i)
                    if inhtype:
                        syn = target.synlistinh[j]
                    else:
                        syn = target.synlistees[j]
                    nc = pc.gid_connect(gen_gid, syn)
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
    h.tstop = 50
    cpg = CPG()

    h.run()

    w = cpg.weight_changes_vectors
    t = cpg.time_t_vectors

    draw(w, t)
