import csv
import random
import bokeh
import sys, os

from CPG_STDP.py.bioaffrat import bioaffrat
from CPG_STDP.py.interneuron import interneuron
from neuron import h
import numpy as np
import h5py as hdf5

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
        self.net_connect = []
        self.stimnclist = []

        self.presyns = []
        self.postsyns = []

        self.weight_changes_vectors = []
        self.time_t_vectors = []

        '''To calculate the spike power'''
        self.calc_spike = []

        '''Create neurons'''
        self.Ia_aff_E = self.addpool(self.nAff, neurontype="aff")
        self.RG_E = self.addpool(self.nInt, neurontype="int")
        self.muscle_E = self.addpool(self.nMn * 30, "muscle")
        self.mns_E = self.addpool(self.nMn, neurontype="moto")
        self.R_E = self.addpool(self.nInt, neurontype="int")
        self.Ia_E = self.addpool(self.nAff, neurontype="aff")

        self.Ia_aff_F = self.addpool(self.nAff, neurontype="aff")
        self.RG_F = self.addpool(self.nInt, neurontype="int")
        self.muscle_F = self.addpool(self.nMn * 30, "muscle")
        self.mns_F = self.addpool(self.nMn, neurontype="moto")
        self.R_F = self.addpool(self.nInt, neurontype="int")
        self.Ia_F = self.addpool(self.nAff, neurontype="aff")

        '''Create generator'''
        # self.generator(self.Ia_aff_E, weight=0.3)
        self.Iagener_E = self.addIagener(self.muscle_E, self.muscle_E, 10, weight=20)
        self.Iagener_F = self.addIagener(self.muscle_F, self.muscle_F, speed * 6, weight=20)

        '''Create connectcells'''
        self.genconnect(self.Iagener_E, self.Ia_aff_E, 0.5, 1, False, 5)
        self.connectcells(self.Ia_aff_E, self.RG_E, weight=0.1, stdptype=True, name=('Ia_aff_E', 'RG_E'))
        self.genconnect(self.Iagener_F, self.Ia_aff_F, 1.5, 1, False, 15)
        self.connectcells(self.Ia_aff_F, self.RG_F, weight=0.1, stdptype=True, name=('Ia_aff_F', 'RG_F'))

        '''Ia2motor'''
        self.connectcells(self.Ia_aff_E, self.mns_E, 1.55, 1.5, name=('Ia_aff_E', 'mns_E'))
        self.connectcells(self.RG_E, self.mns_E, 2.75, 3, name=('RG_E', 'mns_E'))
        self.connectcells(self.mns_E, self.R_E, 0.015, 1, name=('mns_E', 'R_E'))
        self.connectcells(self.R_E, self.mns_E, 0.015, 1, inhtype=True, name=('R_E', 'mns_E'))
        self.connectcells(self.R_E, self.Ia_E, 0.001, 1, inhtype=True, name=('R_E', 'Ia_E'))
        self.connectcells(self.Ia_aff_E, self.Ia_E, 0.008, 1, name=('Ia_aff_E', 'Ia_E'))
        self.connectcells(self.mns_E, self.muscle_E, 15.5, 2, N=45, name=('mns_E', 'muscle_E'))



        self.connectcells(self.Ia_aff_F, self.mns_F, 0.5, 1.5, name=('Ia_aff_F', 'mns_F'))
        self.connectcells(self.R_F, self.Ia_F, 0.001, 1, inhtype=True, name=('R_F', 'Ia_F'))
        self.connectcells(self.R_F, self.mns_F, 0.00015, 1, inhtype=True, name=('R_F', 'mns_F'))
        self.connectcells(self.mns_F, self.R_F, 0.00015, 1, name=('mns_F', 'R_F'))
        self.connectcells(self.RG_F, self.mns_F, 2.75, 3, name=('RG_F', 'mns_F'))
        self.connectcells(self.Ia_aff_F, self.Ia_F, 0.008, 1, name=('Ia_aff_F', 'Ia_F'))
        self.connectcells(self.mns_F, self.muscle_F, 15.5, 2, N=45, name=('mns_F', 'muscle_F'))

        self.spike_rec = self.spike_record()

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

    def connectcells(self, pre_cells, post_cells, weight=1.0, delay=1, threshold=0, N=50, inhtype=False,
                     stdptype=False, name=('int', 'int')):
        nsyn = 5
        ids = set()
        for post in post_cells:
            for i in range(nsyn):
                id = random.randint(0, len(pre_cells) - 1)
                # if len(ids) == 0:
                #     ids.add(id)
                # else:
                #     while id in ids:
                #         id = random.randint(0, len(pre_cells) - 1)
                #     ids.add(id)
                if stdptype:
                    nc = h.NetCon(pre_cells[id].soma(0.5)._ref_v,
                                  post.synlistexstdp[i],
                                  threshold,
                                  delay,
                                  weight,
                                  sec=pre_cells[id].soma)
                    self.net_connect.append(nc)

                    e_syn = post.synlistexstdp[i].e

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
                    self.weight_changes_vectors.append([name[0], name[1], weight_changes])
                    self.time_t_vectors.append(time_t)
                else:
                    if inhtype:
                        nc = h.NetCon(pre_cells[id].soma(0.5)._ref_v,
                                      post.synlistinh[i],
                                      threshold,
                                      delay,
                                      weight,
                                      sec=pre_cells[id].soma)
                        self.net_connect.append(nc)
                        e_syn = post.synlistinh[i].e
                    else:
                        nc = h.NetCon(pre_cells[id].soma(0.5)._ref_v,
                                      post.synlistex[i],
                                      threshold,
                                      delay,
                                      weight,
                                      sec=pre_cells[id].soma)
                        self.net_connect.append(nc)
                        e_syn = post.synlistex[i].e

                volt = h.Vector()
                volt.record(post.soma(0.5)._ref_v)
                ina = h.Vector()
                ina.record(post.soma(0.5)._ref_ina)
                ik = h.Vector()
                ik.record(post.soma(0.5)._ref_ik)
                il = h.Vector()
                type_post_nrn = name[1].split('_')[0]
                if type_post_nrn == 'R' or type_post_nrn == 'RG' or type_post_nrn == 'muscle':
                    il.record(post.soma(0.5)._ref_il_fastchannels)
                elif type_post_nrn == 'mns':
                    il.record(post.soma(0.5)._ref_il_motoneuron)
                elif type_post_nrn == 'Ia':
                    il.record(post.soma(0.5)._ref_il_hh)
                # ica = h.Vector()
                # ica.record(post.soma(0.5)._ref_ica)

                self.calc_spike.append([name[0], name[1], weight, e_syn, volt, ina, ik, il])

    def spike_record(self):

        spike_times = [h.Vector() for nc in self.net_connect]
        for nc, spike_times_vec in zip(self.net_connect, spike_times):
            nc.record(spike_times_vec)

        return spike_times

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
        output_file(f'results_stdp_1/change_res_1_{i}.html')
        i += 1
        figur.line(time_array, weight_changes_array, line_width=2)
        show(figur)

    with hdf5.File('./res_weight/time.hdf5', 'w') as file:
        file.create_dataset('#0_step', data=np.array(time_t[0].as_numpy), compression="gzip")

    for i, weight in enumerate(weight_changes):
        with hdf5.File(f'./res_weight/weight_{weight[0]}_{weight[1]}_{i}.hdf5', 'w') as file:
            file.create_dataset('#0_step', data=np.array(weight[2].as_numpy), compression="gzip")


def write_calc_spike(calc_spike, spike_rec, time):
    columns = ['pre', 'target', 'weight', 'e_syn', 'voltage', 'ina', 'ik', 'il', 'spike_times', 'time']

    filename = 'res_calc_spike/res/data.csv'

    with hdf5.File('./res_calc_spike/res/time.hdf5', 'w') as file:
        file.create_dataset('#0_step', data=np.array(time[0].as_numpy), compression="gzip")

    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(columns)

        for row, spike_times in zip(calc_spike, spike_rec):
            i = calc_spike.index(row)
            spikes = list(spike_times)
            if len(spikes) > 0:
                with hdf5.File('./res_calc_spike/res/{}_{}_{}_voltage.hdf5'.format(row[0], row[1], i), 'w') as file:
                    file.create_dataset('#0_step_{}'.format(i), data=np.array(row[4].as_numpy), compression="gzip")
                with hdf5.File('./res_calc_spike/res/{}_{}_{}_ina.hdf5'.format(row[0], row[1], i), 'w') as file:
                    file.create_dataset('#0_step_{}'.format(i), data=np.array(row[5].as_numpy), compression="gzip")
                with hdf5.File('./res_calc_spike/res/{}_{}_{}_ik.hdf5'.format(row[0], row[1], i), 'w') as file:
                    file.create_dataset('#0_step_{}'.format(i), data=np.array(row[6].as_numpy), compression="gzip")
                with hdf5.File('./res_calc_spike/res/{}_{}_{}_il.hdf5'.format(row[0], row[1], i), 'w') as file:
                    file.create_dataset('#0_step_{}'.format(i), data=np.array(row[7].as_numpy), compression="gzip")
                with hdf5.File('./res_calc_spike/res/{}_{}_{}_ica.hdf5'.format(row[0], row[1], i), 'w') as file:
                    file.create_dataset('#0_step_{}'.format(i), data=np.array(row[8].as_numpy), compression="gzip")
                row.append(spikes)
                row.append(i)
                writer.writerow(row)


if __name__ == '__main__':
    h.dt = 0.01
    h.tstop = 50
    cpg = CPG()

    h.run()

    w = cpg.weight_changes_vectors
    t = cpg.time_t_vectors
    calc_spike = cpg.calc_spike
    spike_rec = cpg.spike_rec

    # draw(w, t)
    write_calc_spike(calc_spike, spike_rec, t)
