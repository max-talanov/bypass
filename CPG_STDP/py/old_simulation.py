import random
from typing import Iterable

import numpy as np
import logging
import h5py as hdf5
import os

from neuron import h
from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle

logging.basicConfig(filename='logs_new_new_2.log',
                    filemode='w',
                    format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s',
                    datefmt='%H:%M:%S',
                    level=logging.DEBUG)
logging.info("let's get it started")

h.load_file("stdgui.hoc")
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')

# paralleling NEURON stuff
h.nrnmpi_init()
pc = h.ParallelContext()
rank = int(pc.id())
nhost = int(pc.nhost())

file_name = 'res_alina_50'

N = 2
speed = 50
bs_fr = 100  # 40 # frequency of brainstem inputs
versions = 1
CV_number = 6
k = 0.017  # CV weights multiplier to take into account air and toe stepping
CV_0_len = 12  # 125 # Duration of the CV generator with no sensory inputs
extra_layers = 0  # 1 + layers

step_number = 4

one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = one_step_time * step_number + 30

'''
network topology https://github.com/max-talanov/bypass/blob/main/figs/CPG_feedback_loops.png
'''


class CPG:

    def __init__(self, speed, bs_fr, inh_p, step_number, n):
        logging.info(f"Hello from rank {rank} of {nhost}")
        logging.info("NEURON version: " + h.nrnversion())
        self.threshold = 10
        self.delay = 1
        self.nAff = 2
        self.nInt = 2
        self.nMn = 2
        self.ncell = n
        self.affs = []
        self.ints = []
        self.motos = []
        self.muscles = []
        self.affgroups = []
        self.intgroups = []
        self.motogroups = []
        self.musclegroups = []
        self.gener_gids = []
        self.n_gid = 0

        self.RG_E = []  # Rhythm generators of extensors
        self.RG_F = []  # Rhythm generators of flexor
        self.CV = []

        self.netstims = []
        self.stims = []

        self.stdpmechs = []
        self.netcons = []
        self.stimnclist = []

        self.presyns = []
        self.postsyns = []

        self.weight_changes_vectors = []
        self.time_t_vectors = []

        self.C_1 = []
        self.C_0 = []
        # self.V0v = []

        for layer in range(CV_number):
            '''cut and muscle feedback'''
            # self.dict_CV_1 = {layer: 'CV{}_1'.format(layer + 1)}
            self.dict_RG_E = {layer: 'RG{}_E'.format(layer + 1)}
            self.dict_RG_F = {layer: 'RG{}_F'.format(layer + 1)}
            # self.dict_V3F = {layer: 'V3{}_F'.format(layer + 1)}
            # self.dict_C = {layer: 'C{}'.format(layer + 1)}

        for layer in range(CV_number):
            '''Cutaneous pools'''
            # self.dict_CV_1[layer] = self.addpool(self.ncell, "CV" + str(layer + 1) + "_1", "aff")
            '''Rhythm generator pools'''
            self.dict_RG_E[layer] = self.addpool(self.ncell, "RG" + str(layer + 1) + "_E", "int")
            self.dict_RG_F[layer] = self.addpool(self.ncell, "RG" + str(layer + 1) + "_F", "int")
            self.RG_E.append(self.dict_RG_E[layer])
            self.RG_F.append(self.dict_RG_F[layer])
            # self.CV.append(self.dict_CV_1[layer])

        '''RG'''
        self.RG_E = sum(self.RG_E, [])
        # self.InE = self.addpool(self.nInt, "InE", "int")
        self.RG_F = sum(self.RG_F, [])
        # self.InF = self.addpool(self.nInt, "InF", "int")

        # self.CV = sum(self.CV, [])

        '''sensory and muscle afferents and brainstem and V3F'''
        self.Ia_aff_E = self.addpool(self.nAff, "Ia_aff_E", "aff")
        self.Ia_aff_F = self.addpool(self.nAff, "Ia_aff_F", "aff")
        # self.BS_aff_E = self.addpool(self.nAff, "BS_aff_E", "aff")
        # self.BS_aff_F = self.addpool(self.nAff, "BS_aff_F", "aff")
        # self.V3F = self.addpool(self.nAff, "V3F", "int")

        '''moto neuron pools'''
        self.mns_E = self.addpool(self.nMn, "mns_E", "moto")
        self.mns_F = self.addpool(self.nMn, "mns_F", "moto")

        '''muscles'''
        self.muscle_E = self.addpool(self.nMn, "muscle_E", "muscle")
        self.muscle_F = self.addpool(self.nMn, "muscle_F", "muscle")

        # '''reflex arc'''
        # self.Ia_E = self.addpool(self.nInt, "Ia_E", "int")
        # self.R_E = self.addpool(self.nInt, "R_E", "int")  # Renshaw cells
        # self.Ia_F = self.addpool(self.nInt, "Ia_F", "int")
        # self.R_F = self.addpool(self.nInt, "R_F", "int")  # Renshaw cells

        '''BS'''
        # periodic stimulation
        # periodic stimulation
        self.E_bs_gids, self.F_bs_gids = self.add_bs_geners(bs_fr, 1)

        # self.E_bs_gids = sum(pc.py_allgather(self.E_bs_gids), [])
        # self.F_bs_gids = sum(pc.py_allgather(self.F_bs_gids), [])
        # ''' BS '''
        # for E_bs_gid in self.E_bs_gids:
        #     self.genconnect(E_bs_gid, self.muscle_E, 0.5, 1)
        #
        # for F_bs_gid in self.F_bs_gids:
        #     self.genconnect(F_bs_gid, self.muscle_F, 0.5, 1)

        # ''' BS '''
        for E_bs_gid in self.E_bs_gids:
            for layer in range(CV_number):
                self.genconnect(E_bs_gid, self.dict_RG_E[layer], 3.75, 1)

        for F_bs_gid in self.F_bs_gids:
            for layer in range(CV_number):
                self.genconnect(F_bs_gid, self.dict_RG_F[layer], 3.75, 1)

        self.E_ia_gids, self.F_ia_gids = self.add_ia_geners()

        for E_ia_gids in self.E_ia_gids:
            self.genconnect(E_ia_gids, self.Ia_aff_E, 3.5, 1, False, 20)

        for F_ia_gids in self.F_ia_gids:
            self.genconnect(F_ia_gids, self.Ia_aff_F, 3.5, 1, False, 30)

        # '''muscle afferents generators'''
        # self.Iagener_E = self.addIagener(self.muscle_E, self.muscle_F, 10, weight=20)
        # self.Iagener_F = self.addIagener(self.muscle_F, self.muscle_E, one_step_time, weight=30)

        # # '''Create connectcells'''
        # self.genconnect(self.Iagener_E, self.Ia_aff_E, 5.5, 1, False, 20)
        # self.genconnect(self.Iagener_F, self.Ia_aff_F, 5.5, 1, False, 30)

        # self.connectcells(self.muscle_E, self.Ia_aff_E, 3.5, 1, 10, False)
        # self.connectcells(self.muscle_F, self.Ia_aff_F, 3.5, 1, 10, False)

        # '''cutaneous inputs'''
        # cfr = 200
        # c_int = 1000 / cfr
        #
        # '''cutaneous inputs generators'''
        # for layer in range(CV_number):
        #     self.dict_C[layer] = []
        #     for i in range(step_number):
        #         '''25 + 50*(0-6) + (0-10)*(50*6 + 12), '''
        #         self.dict_C[layer].append(
        #             self.addgener(25 + speed * layer + i * (speed * CV_number + CV_0_len + one_step_time),
        #                           int(random.gauss(cfr, cfr / 10)), (speed / c_int + 1)))
        #
        # '''Generators'''
        # '''TODO: need it?'''
        # for i in range(step_number):
        #     self.C_0.append(
        #         self.addgener(25 + speed * 6 + i * (speed * 6 + CV_0_len), cfr, int(CV_0_len / c_int), False))
        #
        # '''TODO: need it?'''
        # for layer in range(CV_number):
        #     self.C_1.append(self.dict_CV_1[layer])
        # self.C_1 = sum(self.C_1, [])

        # ''' BS '''
        # for E_bs_gid in self.E_bs_gids:
        #     self.genconnect(E_bs_gid, self.BS_aff_E, 3.5, 3)
        #
        # for F_bs_gid in self.F_bs_gids:
        #     self.genconnect(F_bs_gid, self.BS_aff_F, 3.5, 3)

        # self.connectcells(self.BS_aff_F, self.V3F, 1.5, 3)
        '''STDP synapse'''
        # self.connectcells(self.BS_aff_F, self.RG_F, 0.1, 3, stdptype=False)
        # self.connectcells(self.BS_aff_E, self.RG_E, 0.1, 3, stdptype=False)

        # self.connectcells(self.Ia_aff_E, self.RG_E, weight=3.3, delay=3, stdptype=True)
        # self.connectcells(self.Ia_aff_F, self.RG_F, weight=3.3, delay=3, stdptype=True)

        # '''cutaneous inputs'''
        # for layer in range(CV_number):
        #     self.connectcells(self.dict_C[layer], self.dict_CV_1[layer], 0.15 * k * speed, 2)
        #     self.connectcells(self.dict_CV_1[layer], self.dict_RG_E[layer], 0.0035 * k * speed, 3)
        #
        # '''Ia2motor'''
        # self.connectcells(self.Ia_aff_E, self.mns_E, 1.55, 2)
        # self.connectcells(self.Ia_aff_F, self.mns_F, 1.55, 2)

        for layer in range(CV_number):
            '''Internal to RG topology'''
            self.connectinsidenucleus(self.dict_RG_F[layer])
            self.connectinsidenucleus(self.dict_RG_E[layer])

            '''RG2Motor'''
            self.connectcells(self.dict_RG_E[layer], self.mns_E, 2.75, 3)
            self.connectcells(self.dict_RG_F[layer], self.mns_F, 2.75, 3)
            #
            # self.connectcells(self.dict_RG_E[layer], self.InE, 2.75, 3)
            # self.connectcells(self.dict_RG_F[layer], self.InF, 2.75, 3)

            # self.connectcells(self.dict_RG_F[layer], self.V3F, 1.5, 3)

        '''motor2muscles'''
        self.connectcells(self.mns_E, self.muscle_E, 15, 2, inhtype=False, N=45, sect="muscle")
        self.connectcells(self.mns_F, self.muscle_F, 15, 2, inhtype=False, N=45, sect="muscle")

        # '''Ia2RG, RG2Motor'''
        # self.connectcells(self.InE, self.RG_F, 0.5, 1, inhtype=True)
        # self.connectcells(self.InF, self.RG_E, 0.8, 1, inhtype=True)
        #
        # self.connectcells(self.Ia_aff_E, self.Ia_E, 0.08, 1, inhtype=False)
        # self.connectcells(self.Ia_aff_F, self.Ia_F, 0.08, 1, inhtype=False)
        #
        # self.connectcells(self.mns_E, self.R_E, 0.0015, 1, inhtype=False)
        # self.connectcells(self.mns_F, self.R_F, 0.0015, 1, inhtype=False)
        #
        # self.connectcells(self.R_E, self.mns_E, 0.0015, 1, inhtype=True)
        # self.connectcells(self.R_F, self.mns_F, 0.0015, 1, inhtype=True)
        #
        # self.connectcells(self.R_E, self.Ia_E, 0.001, 1, inhtype=True)
        # self.connectcells(self.R_F, self.Ia_F, 0.001, 1, inhtype=True)
        # #
        # self.connectcells(self.Ia_E, self.mns_F, 0.08, 1, inhtype=True)
        # self.connectcells(self.Ia_F, self.mns_E, 0.08, 1, inhtype=True)

    def addpool(self, num, name, neurontype = "int") -> list:
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
        gid = self.n_gid

        delaytype = False
        if neurontype.lower() == "delay":
            delaytype = True

        if neurontype.lower() == "moto":
            diams = self.motodiams(num)
        for i in range(rank, num, nhost):
            if neurontype.lower() == "moto":
                cell = motoneuron(diams[i])
                self.motos.append(cell)
            elif neurontype.lower() == "aff":
                cell = bioaffrat()
                self.affs.append(cell)
            elif neurontype.lower() == "muscle":
                cell = muscle()
                self.muscles.append(cell)
            elif neurontype.lower() == "bursting":
                cell = interneuron(False, bursting_mode=True)
                self.ints.append(cell)
            else:
                cell = interneuron(delaytype)
                self.ints.append(cell)

            gids.append(gid)
            pc.set_gid2node(gid, rank)
            nc = cell.connect2target(None)
            pc.cell(gid, nc)
            self.netcons.append(nc)
            gid += 1

        # Groups
        if neurontype.lower() == "muscle":
            self.musclegroups.append((gids, name))
        elif neurontype.lower() == "moto":
            self.motogroups.append((gids, name))
        elif neurontype.lower() == "aff":
            self.affgroups.append((gids, name))
        else:
            self.intgroups.append((gids, name))

        self.n_gid = gid

        return gids

    def connectcells(self, pre_cells, post_cells, weight=1.0, delay=1, threshold=10, inhtype=False,
                     stdptype=False, N=50, sect="int"):
        nsyn = random.randint(N, N + 15)
        nsyn = 15
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
                        weight_changes.record(stdpmech._ref_synweight)
                        self.weight_changes_vectors.append((src_gid, post_gid, weight_changes))
                    else:
                        if inhtype:
                            syn = target.synlistinh[i]
                        else:
                            syn = target.synlistex[i]
                        nc = pc.gid_connect(src_gid, syn)
                        nc.weight[0] = random.gauss(weight, weight / 5)
                        nc.threshold = threshold
                        nc.delay = random.gauss(delay, delay / 5)
                        self.netcons.append(nc)

    def genconnect(self, gen_gid, afferents_gids, weight, delay, inhtype=False, N=50):
        nsyn = random.randint(N - 5, N)
        nsyn = 15
        for i in afferents_gids:
            if pc.gid_exists(i):
                for j in range(nsyn):
                    target = pc.gid2cell(i)
                    if inhtype:
                        syn = target.synlistinh[j]
                    else:
                        syn = target.synlistex[j]
                    nc = pc.gid_connect(gen_gid, syn)
                    nc.threshold = self.threshold
                    nc.delay = random.gauss(delay, delay / 5)
                    nc.weight[0] = random.gauss(weight, weight / 6)
                    self.stimnclist.append(nc)

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

    def addIagener(self, mn: list, mn2: list, start, weight=1.0):
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

        gid = self.n_gid
        moto = pc.gid2cell(random.randint(mn[0], mn[-1]))
        moto2 = pc.gid2cell(random.randint(mn2[0], mn2[-1]))
        stim = h.IaGenerator(0.5)
        stim.start = start
        stim.interval = int(1000 / bs_fr)
        stim.number = int(one_step_time / stim.interval)
        self.stims.append(stim)
        h.setpointer(moto.muscle_unit(0.5)._ref_F_fHill, 'fhill', stim)
        h.setpointer(moto2.muscle_unit(0.5)._ref_F_fHill, 'fhill2', stim)
        pc.set_gid2node(gid, rank)
        ncstim = h.NetCon(stim, None)
        ncstim.weight[0] = weight
        self.netcons.append(ncstim)
        pc.cell(gid, ncstim)
        self.gener_gids.append(gid)
        self.n_gid += 1

        return gid

    def addgener(self, start, freq, nums, r=True):
        '''
        Creates generator and returns generator gid
        Parameters
        ----------
        start: int
            generator start up
        freq: int
            generator frequency
        nums: int
            signals number
        Returns
        -------
        gid: int
            generator gid
        '''
        gid = self.n_gid
        stim = h.NetStim()
        # stim.number = nums
        if r:
            stim.start = random.uniform(start - 3, start + 3)
            stim.noise = 0.05
        else:
            stim.start = start
        stim.interval = int(1000 / freq)
        stim.number = int(one_step_time / stim.interval)
        self.stims.append(stim)
        pc.set_gid2node(gid, rank)
        ncstim = h.NetCon(stim, None)
        self.netcons.append(ncstim)
        pc.cell(gid, ncstim)
        self.gener_gids.append(gid)
        self.n_gid += 1

        return gid

    def connectinsidenucleus(self, nucleus):
        self.connectcells(nucleus, nucleus, 0.25, 0.5)

    def add_bs_geners(self, freq, spikes_per_step):
        E_bs_gids = []
        F_bs_gids = []
        for step in range(step_number):
            F_bs_gids.append(self.addgener(int(one_step_time * (2 * step + 1)), freq, spikes_per_step, False))
            E_bs_gids.append(self.addgener(int(one_step_time * 2 * step) + 10, freq, spikes_per_step, False))
        return E_bs_gids, F_bs_gids

    def add_ia_geners(self):
        E_ia_gids = []
        F_ia_gids = []
        for step in range(step_number):
            E_ia_gids.append(self.addIagener(self.muscle_E, self.muscle_F, 10, weight=5))
            F_ia_gids.append(self.addIagener(self.muscle_F, self.muscle_E, one_step_time, weight=8))
        return E_ia_gids, F_ia_gids


# def draw(weight_changes, time_t):
#     i = 0
#     # Convert weight_changes to a NumPy array
#     for w, t in zip(weight_changes, time_t):
#         weight_changes_array = np.array(w.as_numpy())
#         time_array = np.array(t.as_numpy())
#
#         figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
#         output_file(f'results_stdp/change_res_{i}.html')
#         i += 1
#         figur.line(time_array, weight_changes_array, line_width=2)
#         show(figur)


def spike_record(pool, extra=False, location='soma'):
    ''' Records spikes from gids
      Parameters
      ----------
      pool: list
        list of neurons gids
      extra: bool
          extracellular or intracellular voltages to record
      Returns
      -------
      v_vec: list of h.Vector()
          recorded voltages
    '''
    v_vec = []

    for i in pool:
        cell = pc.gid2cell(i)
        vec = h.Vector(np.zeros(int(time_sim / 0.025 + 1), dtype=np.float32))
        if extra:
            vec.record(cell.soma(0.5)._ref_vext[0])
        else:
            if location == 'axon':
                # Изменение на запись из первого узла аксона (здесь будут нормальные спайки)
                vec.record(cell.node[0](1.0)._ref_v)
            elif location == 'muscle':
                vec.record(cell.muscle_unit(0.5)._ref_v)
            elif location == 'am':
                vec.record(cell.muscle_unit(0.5)._ref_AM_CaSP)
            else:
                # Запись из сомы (как было раньше)
                vec.record(cell.soma(0.5)._ref_v)
        v_vec.append(vec)
    return v_vec


def force_record(pool):
    ''' Records force from gids of motor neurons muscle unit
      Parameters
      ----------
      Returns
      -------
      v_vec: list of h.Vector()
          recorded voltage
    '''
    v_vec = []
    for i in pool:
        cell = pc.gid2cell(i)
        vec = h.Vector(np.zeros(int(time_sim / 0.025 + 1), dtype=np.float32))
        vec.record(cell.muscle_unit(0.5)._ref_F_fHill)
        v_vec.append(vec)
    return v_vec


def spikeout(pool, name, version, v_vec):
    ''' Reports simulation results
      Parameters
      ----------
      pool: list
        list of neurons gids
      name: string
        pool name
      version: int
          test number
      v_vec: list of h.Vector()
          recorded voltage
    '''
    global rank
    pc.barrier()
    vec = h.Vector()
    for i in range(nhost):
        if i == rank:
            outavg = []
            for j in range(len(pool)):
                outavg.append(list(v_vec[j]))
            outavg = np.mean(np.array(outavg), axis=0, dtype=np.float32)
            vec = vec.from_python(outavg)
        pc.barrier()
    pc.barrier()
    result = pc.py_gather(vec, 0)
    if rank == 0:
        logging.info("start recording " + name)
        result = np.mean(np.array(result), axis=0, dtype=np.float32)
        with hdf5.File(f'./{file_name}/{name}_sp_{speed}_CVs_{CV_number}_bs_{bs_fr}.hdf5', 'w') as file:
            for i in range(step_number):
                sl = slice((int(1000 / bs_fr) * 40 + i * one_step_time * 40),
                           (int(1000 / bs_fr) * 40 + (i + 1) * one_step_time * 40))
                file.create_dataset('#0_step_{}'.format(i), data=np.array(result)[sl], compression="gzip")
        logging.info("done recording")
    else:
        logging.info(rank)


def prun(speed, step_number):
    ''' simulation control
    Parameters
    ----------
    speed: int
      duration of each layer

    Returns
    -------
    t: list of h.Vector()
      recorded time
    '''
    pc.timeout(0)
    t = h.Vector().record(h._ref_t)
    tstop = time_sim
    pc.set_maxstep(10)
    h.finitialize(-65)
    h.stdinit()
    pc.psolve(tstop)
    return t


def finish():
    ''' proper exit '''
    pc.runworker()
    pc.done()
    # print("hi after finish")
    h.quit()


# if __name__ == '__main__':
#     # h.dt = 0.1
#     # h.tstop = 50
#     # cpg = CPG()
#     #
#     # h.run()
#     #
#     # w = cpg.weight_changes_vectors
#     # t = cpg.time_t_vectors
#     #
#     # draw(w, t)


if __name__ == '__main__':
    '''
    cpg_ex: cpg
        topology of central pattern generation + reflex arc
    '''
    k_nrns = 0
    k_name = 1
    if not os.path.isdir(file_name):
        os.mkdir(file_name)

    for i in range(versions):
        cpg_ex = CPG(speed, bs_fr, 100, step_number, N)
        logging.info("created")
        motorecorders = []
        motorecorders_mem = []
        musclerecorders = []
        muscle_units_recorders = []
        muscle_am_recorders = []
        force_recorders = []
        # for group in cpg_ex.motogroups:
        #     motorecorders.append(spike_record(group[k_nrns], True))

        for group in cpg_ex.motogroups:
            motorecorders_mem.append(spike_record(group[k_nrns]))
        affrecorders = []
        for group in cpg_ex.affgroups:
            affrecorders.append(spike_record(group[k_nrns]))
        recorders = []
        for group in cpg_ex.intgroups:
            recorders.append(spike_record(group[k_nrns]))
        for group in cpg_ex.musclegroups:
            musclerecorders.append(spike_record(group[k_nrns]))
            force_recorders.append(force_record(group[k_nrns]))
            muscle_units_recorders.append(spike_record(group[k_nrns], location='muscle'))
            muscle_am_recorders.append(spike_record(group[k_nrns], location='am'))

        logging.info("added recorders")

        print("- " * 10, "\nstart")
        t = prun(speed, step_number)
        print("- " * 10, "\nend")

        logging.info("simulation done")

        with open(f'./{file_name}/time.txt', 'w') as time_file:
            for time in t:
                time_file.write(str(time) + "\n")

        # for cpg_weight in cpg_ex.weight_changes_vectors:
        #     with hdf5.File('./res_alina/stdp_1/{}_{}.hdf5'.format(str(pc.gid2cell(cpg_weight[0])).split('.')[0],
        #                                                         str(pc.gid2cell(cpg_weight[1])).split('.')[0]),
        #                    'w') as file:
        #         file.create_dataset('#0_step_{}'.format(i), data=cpg_weight[2], compression="gzip")

        # for group, recorder in zip(cpg_ex.motogroups, motorecorders):
        #     spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.musclegroups, musclerecorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.motogroups, motorecorders_mem):
            spikeout(group[k_nrns], 'mem_{}'.format(group[k_name]), i, recorder)
        for group, recorder in zip(cpg_ex.affgroups, affrecorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.intgroups, recorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.musclegroups, force_recorders):
            spikeout(group[k_nrns], 'force_{}'.format(group[k_name]), i, recorder)
        for group, recorder in zip(cpg_ex.musclegroups, muscle_units_recorders):
            spikeout(group[k_nrns], 'units_{}'.format(group[k_name]), i, recorder)
        for group, recorder in zip(cpg_ex.musclegroups, muscle_am_recorders):
            spikeout(group[k_nrns], 'am_{}'.format(group[k_name]), i, recorder)

            logging.info("recorded")

    finish()