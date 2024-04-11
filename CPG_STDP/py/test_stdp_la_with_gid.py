import random
import numpy as np
import logging
import h5py as hdf5

from neuron import h
from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle

logging.basicConfig(filename='logs.log',
                    filemode='a',
                    format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s',
                    datefmt='%H:%M:%S',
                    level=logging.DEBUG)
logging.info("let's get it started")

h.load_file("stdgui.hoc")
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')

# paralleling NEURON stuff

pc = h.ParallelContext()
rank = int(pc.id())
nhost = int(pc.nhost())

N = 50
speed: int = 50
bs_fr: int = 100  # 40 # frequency of brainstem inputs
versions: int = 1
CV_number = 6
k: float = 0.017  # CV weights multiplier to take into account air and toe stepping
CV_0_len: int = 12  # 125 # Duration of the CV generator with no sensory inputs
extra_layers = 0  # 1 + layers

step_number = 10

one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = 300 + one_step_time * step_number

'''
network topology https://github.com/max-talanov/bypass/blob/main/figs/CPG_feedback_loops.png
'''


class CPG:

    def __init__(self, speed, bs_fr, inh_p, step_number, N):
        self.threshold = 10
        self.delay = 1
        self.nAff = 12
        self.nInt = 5
        self.nMn = 21
        self.ncell = N
        self.affs = []
        self.ints = []
        self.motos = []
        self.muscles = []
        self.affgroups = []
        self.intgroups = []
        self.motogroups = []
        self.musclegroups = []
        self.n_gid = 0

        self.RG_E = []  # Rhythm generators of extensors
        self.RG_F = []  # Rhythm generators of flexor

        self.netstims = []
        self.stims = []

        self.stdpmechs = []
        self.netcons = []
        self.stimnclist = []

        self.presyns = []
        self.postsyns = []

        self.weight_changes_vectors = []
        self.time_t_vectors = []

        '''sensory and muscle afferents and brainstem and V3F'''
        self.Ia_aff_E = self.addpool(self.nAff, "Ia_aff_E", "aff", count=0)
        self.Ia_aff_F = self.addpool(self.nAff, "Ia_aff_F", "aff")
        self.BS_aff_E = self.addpool(self.nAff, "BS_aff_E", "aff")
        self.BS_aff_F = self.addpool(self.nAff, "BS_aff_F", "aff")
        self.V3F = self.addpool(self.nAff, "V3F", "int")

        for layer in range(CV_number):
            '''cut and muscle feedback'''
            self.dict_RG_E = {layer: 'RG{}_E'.format(layer + 1)}
            self.dict_RG_F = {layer: 'RG{}_F'.format(layer + 1)}

        for layer in range(CV_number):
            '''Rhythm generator pools'''
            self.dict_RG_E[layer] = self.addpool(self.ncell, "RG" + str(layer + 1) + "_E", "int")
            self.dict_RG_F[layer] = self.addpool(self.ncell, "RG" + str(layer + 1) + "_F", "int")
            self.RG_E.append(self.dict_RG_E[layer])
            self.RG_F.append(self.dict_RG_F[layer])

        '''RG'''
        self.RG_E = sum(self.RG_E, [])
        self.InE = self.addpool(self.nInt, "InE", "int")
        self.RG_F = sum(self.RG_F, [])
        self.InF = self.addpool(self.nInt, "InF", "int")

        '''moto neuron pools'''
        self.mns_E = self.addpool(self.nMn, "mns_E", "moto")
        self.mns_F = self.addpool(self.nMn, "mns_F", "moto")

        '''muscles'''
        self.muscle_E = self.addpool(self.nMn * 30, "muscle_E", "muscle")
        self.muscle_F = self.addpool(self.nMn * 20, "muscle_F", "muscle")

        '''reflex arc'''
        self.Ia_E = self.addpool(self.nInt, "Ia_E", "int")
        self.R_E = self.addpool(self.nInt, "R_E", "int")  # Renshaw cells
        self.Ia_F = self.addpool(self.nInt, "Ia_F", "int")
        self.R_F = self.addpool(self.nInt, "R_F", "int")  # Renshaw cells

        '''muscle afferents generators'''
        self.Iagener_E = self.addIagener(self.muscle_E, self.muscle_E, 10, weight=20)
        self.Iagener_F = self.addIagener(self.muscle_F, self.muscle_F, speed * 6, weight=20)

        '''Create connectcells'''
        self.genconnect(self.Iagener_E, self.Ia_aff_E, 0.5, 1, False, 5)
        self.connectcells(self.Ia_aff_E, self.RG_E, weight=0.13, stdptype=True)

        '''Ia2motor'''
        self.connectcells(self.Ia_aff_E, self.mns_E, 1.55, 1.5)
        self.connectcells(self.Ia_aff_F, self.mns_F, 0.5, 1.5)
        '''motor2muscles'''
        self.connectcells(self.mns_E, self.muscle_E, 15.5, 2, False, 45)
        self.connectcells(self.mns_F, self.muscle_F, 15.5, 2, False, 45)

        for layer in range(CV_number):
            '''Internal to RG topology'''
            self.connectinsidenucleus(self.dict_RG_F[layer])
            self.connectinsidenucleus(self.dict_RG_E[layer])

            '''RG2Motor'''
            self.connectcells(self.dict_RG_E[layer], self.mns_E, 2.75, 3)
            self.connectcells(self.dict_RG_F[layer], self.mns_F, 2.75, 3)

            '''RG2Motor, RG2Ia'''
            self.connectcells(self.dict_RG_F[layer], self.mns_F, 3.75, 2)
            '''Neg feedback loop RG->Ia'''
            self.connectcells(self.dict_RG_F[layer], self.Ia_aff_F, 0.95, 1, True)

    def addpool(self, num, name, neurontype="int", count=1) -> list:
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
        if count == 0:
            gid = 0
        else:
            gid = self.n_gid
        if neurontype.lower() == "delay":
            delaytype = True
        else:
            delaytype = False

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
        if (neurontype.lower() == "muscle"):
            self.musclegroups.append((gids, name))
        elif (neurontype.lower() == "moto"):
            self.motogroups.append((gids, name))
        elif neurontype.lower() == "aff":
            self.affgroups.append((gids, name))
        else:
            self.intgroups.append((gids, name))

        self.n_gid = gid

        return gids

    def connectcells(self, pre_cells, post_cells, weight=1.0, delay=1, threshold=10, inhtype=False, stdptype=False):
        nsyn = random.randint(N - 15, N)
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
        self.n_gid += 1

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

    def connectinsidenucleus(self, nucleus):
        self.connectcells(nucleus, nucleus, 0.25, 0.5)


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


def spike_record(pool, extra=False):
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
            vec.record(cell.soma(0.5)._ref_v)
        v_vec.append(vec)
    return v_vec


def force_record(pool):
    ''' Records force from gids of motor neurons muscle unit
      Parameters
      ----------
      pool: list
        list of neurons gids
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
        logging.info("start recording")
        result = np.mean(np.array(result), axis=0, dtype=np.float32)
        with hdf5.File('./res/{}_sp_{}_CVs_{}_bs_{}.hdf5'.format(name, speed, CV_number, bs_fr), 'w') as file:
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
    tstop = time_sim  # 25 + (6 * speed + 125) * step_number
    pc.set_maxstep(10)
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

    for i in range(versions):
        cpg_ex = CPG(speed, bs_fr, 100, step_number, N)
        logging.info("created")
        motorecorders = []
        motorecorders_mem = []
        force_recorders = []
        for group in cpg_ex.motogroups:
            motorecorders.append(spike_record(group[k_nrns], True))

        for group in cpg_ex.motogroups:
            motorecorders_mem.append(spike_record(group[k_nrns]))
        affrecorders = []
        for group in cpg_ex.affgroups:
            affrecorders.append(spike_record(group[k_nrns]))
        recorders = []
        for group in cpg_ex.intgroups:
            recorders.append(spike_record(group[k_nrns]))
        for group in cpg_ex.musclegroups:
            force_recorders.append(force_record(group[k_nrns]))

        logging.info("added recorders")

        print("- " * 10, "\nstart")
        t = prun(speed, step_number)
        print("- " * 10, "\nend")

        logging.info("simulation done")

        with open('./res/time.txt', 'w') as time_file:
            for time in t:
                time_file.write(str(time) + "\n")

        for group, recorder in zip(cpg_ex.motogroups, motorecorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.motogroups, motorecorders_mem):
            spikeout(group[k_nrns], 'mem_{}'.format(group[k_name]), i, recorder)
        for group, recorder in zip(cpg_ex.affgroups, affrecorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.intgroups, recorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.musclegroups, force_recorders):
            spikeout(group[k_nrns], 'force_{}'.format(group[k_name]), i, recorder)

            logging.info("recorded")

    finish()
