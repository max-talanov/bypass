import random
import numpy as np
import logging
import h5py as hdf5
import os
from neuron import h
from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle

logging.basicConfig(filename='logs_new_new_3.log',
                    filemode='w',
                    format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S',
                    level=logging.DEBUG)
logging.info("let's get it started")

h.load_file("stdgui.hoc")
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')

# paralleling NEURON stuff

pc = h.ParallelContext()
rank = int(pc.id())
nhost = int(pc.nhost())

file_name = 'res_alina_new_new1'

N = 7  # 50
speed = 100
bs_fr = 150 #50 #150 #100  # 40 # frequency of brainstem inputs
versions = 1
CV_number = 6
k = 0.017  # CV weights multiplier to take into account air and toe stepping
CV_0_len = 12  # 125 # Duration of the CV generator with no sensory inputs
extra_layers = 0  # 1 + layers

step_number = 3

one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = one_step_time * step_number + 20

'''
network topology https://github.com/max-talanov/bypass/blob/main/figs/CPG_feedback_loops.png
'''


class CPG:

    def __init__(self, speed, bs_fr, inh_p, step_number, n):
        self.threshold = -20
        self.delay = 1
        self.nAff = 7  # 12  # 12
        self.nInt = 7 # 5
        self.nMn = 21  # 21  # 21
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
        self.recorded_spikes = []
        self.used_mn = []
        self.used_mn2 = []
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
        #
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

        '''muscles'''
        self.muscle_E = self.addpool(self.nMn * 5, "muscle_E", "muscle")
        self.muscle_F = self.addpool(self.nMn * 5, "muscle_F", "muscle")

        logging.info("done addpool")
        '''BS'''
        # periodic stimulation
        self.E_bs_gids, self.F_bs_gids = self.add_bs_geners(bs_fr, 0.5, 0.5)

        # ''' BS '''
        # for E_bs_gid in self.E_bs_gids:
        #     self.genconnect(E_bs_gid, self.BS_aff_E, 2, 1)
        #
        # for F_bs_gid in self.F_bs_gids:
        #     self.genconnect(F_bs_gid, self.BS_aff_F, 2, 1)

        ''' BS '''
        # for E_bs_gid in self.E_bs_gids:
        #     for layer in range(CV_number):
        #         self.genconnect(E_bs_gid, self.dict_RG_E[layer], 0.02, 1)
        #
        # for F_bs_gid in self.F_bs_gids:
        #     for layer in range(CV_number):
        #         self.genconnect(F_bs_gid, self.dict_RG_F[layer], 0.02, 1)

        for E_bs_gid in self.E_bs_gids:
            self.genconnect(E_bs_gid, self.muscle_E, 1.5, 1)

        for F_bs_gid in self.F_bs_gids:
            self.genconnect(F_bs_gid, self.muscle_F, 1.5, 1)

        # for layer in range(CV_number):
        #     self.connectcells(self.BS_aff_F, self.dict_RG_F[layer], 4, 1, stdptype=False)
        #     self.connectcells(self.BS_aff_E, self.dict_RG_E[layer], 4, 1, stdptype=False)
        # #
        # for layer in range(CV_number):
        #     '''Internal to RG topology'''
        #     self.connectinsidenucleus(self.dict_RG_F[layer])
        #     self.connectinsidenucleus(self.dict_RG_E[layer])
        #
        #     # '''RG2Motor'''
        #     self.connectcells(self.dict_RG_E[layer], self.muscle_E, 2, 1)
        #     self.connectcells(self.dict_RG_F[layer], self.muscle_F, 2, 1)
        #
        # # '''muscle afferents generators'''
        #
        self.E_ia_gids, self.F_ia_gids = self.add_ia_geners(self.muscle_E, self.muscle_F)


        logging.info("done connectcells")

    def addpool(self, num, name, neurontype="int") -> list:
        """
        Adds a pool of neurons.
        """
        # Начальный gid для этого пула
        start_gid = self.n_gid
        
        # Создаем полный список gids для всего пула
        all_gids = list(range(start_gid, start_gid + num))
        
        # Каждый процесс обрабатывает только свои gid
        local_gids = []
        
        for gid in all_gids:
            if (gid % nhost) == rank:  # Распределяем gid по процессам
                try:
                    # Создаем нейрон соответствующего типа
                    if neurontype.lower() == "moto":
                        cell = motoneuron(self.motodiams(num)[gid - start_gid])
                        self.motos.append(cell)
                    elif neurontype.lower() == "muscle":
                        cell = muscle()
                        self.muscles.append(cell)
                    elif neurontype.lower() == "aff":
                        cell = bioaffrat()
                        if "_F" in name:
                            cell.neuron_type = "flexor"
                        else:
                            cell.neuron_type = "extensor"
                        self.affs.append(cell)
                    elif neurontype.lower() == "bursting":
                        cell = interneuron(False, bursting_mode=True)
                        self.ints.append(cell)
                    else:
                        cell = interneuron(False)
                        self.ints.append(cell)

                    # Регистрируем gid на текущем процессе
                    pc.set_gid2node(gid, rank)
                    
                    # Создаем и регистрируем соединение
                    nc = cell.connect2target(None)
                    nc.threshold = self.threshold
                    pc.cell(gid, nc)
                    
                    # Проверяем успешность регистрации
                    if not pc.gid_exists(gid):
                        raise RuntimeError(f"Failed to register gid {gid}")
                    
                    local_gids.append(gid)
                    
                except Exception as e:
                    logging.error(f"Failed to create/register gid {gid}: {str(e)}")
                    raise
        
        # Синхронизация после создания клеток
        pc.barrier()
        
        # Обновляем Groups
        if neurontype.lower() == "muscle":
            self.musclegroups.append((all_gids, name))
        elif neurontype.lower() == "moto":
            self.motogroups.append((all_gids, name))
        elif neurontype.lower() == "aff":
            self.affgroups.append((all_gids, name))
        else:
            self.intgroups.append((all_gids, name))
        
        # Обновляем n_gid
        self.n_gid = start_gid + num
        
        # Финальная синхронизация
        pc.barrier()
        
        return all_gids

    def safe_gid2cell(self, gid):
        """
        Безопасно получает клетку по gid
        
        Parameters
        ----------
        gid : int
            Global ID клетки
            
        Returns
        -------
        cell or None
            Клетка если она существует, иначе None
        """
        try:
            # Сначала проверяем локальный кэш
            if hasattr(self, 'gid_to_cell') and gid in self.gid_to_cell:
                return self.gid_to_cell[gid]
            
            # Проверяем существование gid
            if not pc.gid_exists(gid):
                logging.warning(f"Process {rank}: gid {gid} does not exist")
                return None
                
            # Пытаемся получить клетку
            cell = pc.gid2cell(gid)
            if cell is None:
                logging.warning(f"Process {rank}: Failed to get cell for gid {gid}")
                return None
                
            # Кэшируем результат
            if not hasattr(self, 'gid_to_cell'):
                self.gid_to_cell = {}
            self.gid_to_cell[gid] = cell
            
            return cell
            
        except Exception as e:
            logging.error(f"Process {rank}: Error accessing cell for gid {gid}: {str(e)}")
            return None

    def connectcells(self, pre_cells, post_cells, weight=1.0, delay=1, threshold=-20, inhtype=False,
                     stdptype=False, N=45):
        """
        Connect two groups of cells with synapses
        
        Parameters
        ----------
        pre_cells : list
            List of presynaptic cell gids
        post_cells : list
            List of postsynaptic cell gids
        weight : float
            Base synaptic weight
        delay : float
            Base synaptic delay
        threshold : float
            Spike threshold
        inhtype : bool
            If True, use inhibitory synapses
        stdptype : bool
            If True, use STDP synapses
        N : int
            Base number of synapses per cell
        """
        # Синхронизация перед началом создания соединений
        pc.barrier()
        
        # Для каждой постсинаптической клетки
        for post_gid in post_cells:
            # Проверяем, принадлежит ли эта клетка текущему процессу
            if pc.gid_exists(post_gid):
                # Получаем клетку
                target = pc.gid2cell(post_gid)
                
                # Определяем количество синапсов для этой клетки
                nsyn = random.randint(N, N + 15)
                
                # Создаем соединения
                for i in range(nsyn):
                    # Выбираем случайную пресинаптическую клетку
                    src_gid = random.randint(pre_cells[0], pre_cells[-1])
                    
                    if stdptype:
                        # STDP синапсы
                        try:
                            syn = target.synlistexstdp[i]
                            nc = pc.gid_connect(src_gid, syn)
                            nc.delay = delay
                            nc.weight[0] = weight
                            nc.threshold = threshold
                            pc.threshold(src_gid, threshold)
                            self.netcons.append(nc)

                            # Создаем STDP механизм
                            dummy = h.Section()
                            stdpmech = h.STDP(0, dummy)
                            self.stdpmechs.append(stdpmech)
                            
                            # Пресинаптическое соединение для STDP
                            presyn = pc.gid_connect(src_gid, stdpmech)
                            presyn.delay = delay
                            presyn.weight[0] = 2
                            presyn.threshold = threshold
                            self.presyns.append(presyn)
                            
                            # Постсинаптическое соединение для STDP
                            pstsyn = pc.gid_connect(post_gid, stdpmech)
                            pstsyn.delay = delay
                            pstsyn.weight[0] = -2
                            pstsyn.threshold = threshold
                            self.postsyns.append(pstsyn)
                            
                            pc.threshold(post_gid, threshold)
                            h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)

                            # Запись изменений весов
                            weight_changes = h.Vector()
                            weight_changes.record(stdpmech._ref_synweight)
                            self.weight_changes_vectors.append((src_gid, post_gid, weight_changes))
                            
                        except Exception as e:
                            logging.error(f"Error creating STDP connection {src_gid}->{post_gid}: {str(e)}")
                            continue
                            
                    else:
                        # Обычные синапсы
                        try:
                            if inhtype:
                                syn = target.synlistinh[i]
                            else:
                                syn = target.synlistex[i]
                                
                            nc = pc.gid_connect(src_gid, syn)
                            nc.weight[0] = max(0.0, random.gauss(weight, weight / 5))
                            nc.threshold = threshold
                            nc.delay = max(0.1, random.gauss(delay, delay / 5))
                            pc.threshold(src_gid, nc.threshold)
                            self.netcons.append(nc)
                            
                        except Exception as e:
                            logging.error(f"Error creating connection {src_gid}->{post_gid}: {str(e)}")
                            continue

        # Синхронизация после создания всех соединений
        pc.barrier()

    def genconnect(self, gen_gid, afferents_gids, weight, delay, inhtype=False, N=90):
        """
        Connect a generator to a group of cells
        """
        # Синхронизация перед началом создания соединений
        pc.barrier()
        
        try:
            # Проверяем существование генератора
            if not pc.gid_exists(gen_gid):
                logging.error(f"Generator {gen_gid} does not exist")
                return
                
            # Для каждой клетки-мишени
            for target_gid in afferents_gids:
                # Проверяем существование клетки перед использованием gid2cell
                if not pc.gid_exists(target_gid):
                    logging.warning(f"Target {target_gid} does not exist, skipping")
                    continue
                    
                try:
                    # Получаем клетку
                    target = pc.gid2cell(target_gid)
                    if target is None:
                        logging.warning(f"Failed to get cell for gid {target_gid}, skipping")
                        continue
                        
                    # Определяем количество синапсов для этой клетки
                    nsyn = random.randint(N - 5, N)
                    
                    # Создаем соединения
                    for j in range(nsyn):
                        try:
                            # Выбираем тип синапса
                            if inhtype:
                                syn = target.synlistinh[j]
                            else:
                                syn = target.synlistex[j]
                                
                            # Создаем соединение
                            nc = pc.gid_connect(gen_gid, syn)
                            nc.threshold = self.threshold
                            nc.delay = max(0.1, random.gauss(delay, delay / 5))
                            nc.weight[0] = weight
                            
                            # Сохраняем соединение
                            self.stimnclist.append(nc)
                            
                        except Exception as e:
                            logging.error(f"Error creating synapse: {str(e)}")
                            continue
                            
                except Exception as e:
                    logging.error(f"Error processing target cell: {str(e)}")
                    continue
                    
        except Exception as e:
            logging.error(f"Error in genconnect: {str(e)}")
            
        finally:
            # Синхронизация после создания всех соединений
            pc.barrier()

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

    def addgener(self, start, freq, flg_interval, interval, weight=0.5, cv=False, r=True):
        """
        Creates generator and returns generator gid
        """
        # Получаем начальный gid
        gid = self.n_gid
        
        # Определяем целевой процесс
        target_rank = gid % nhost
        
        # Создаем генератор на целевом процессе
        if rank == target_rank:
            # Создаем и настраиваем стимулятор
            stim = h.NetStim()
            
            if r:
                stim.start = random.uniform(start - 3, start + 3)
            else:
                stim.start = start
            
            if flg_interval:
                stim.interval = interval
                stim.number = 10
            else:
                stim.interval = int(1000 / freq)
                stim.number = int(one_step_time / stim.interval)
            
            stim.noise = 0.01
            self.stims.append(stim)
            
            # Создаем и регистрируем соединение
            ncstim = h.NetCon(stim, None)
            ncstim.weight[0] = weight
            self.netcons.append(ncstim)
            
            # Регистрируем gid
            pc.set_gid2node(gid, target_rank)
            pc.cell(gid, ncstim)
            
            # Проверяем регистрацию
            if not pc.gid_exists(gid):
                raise RuntimeError(f"Failed to register generator gid {gid}")
        
        # Синхронизация после создания
        pc.barrier()
        
        # Проверяем, что генератор доступен на всех процессах
        if not pc.gid_exists(gid):
            logging.error(f"Process {rank}: Generator {gid} is not accessible")
            raise RuntimeError(f"Generator {gid} is not accessible on process {rank}")
        
        # Добавляем gid в список и обновляем счетчик
        self.gener_gids.append(gid)
        self.n_gid = gid + 1
        
        return gid

    def addIagener(self, mn: list, mn2: list, start: int, weight: float = 1.0) -> int:
        """
        Creates an Ia generator and returns its gid.
        """
        # Получаем начальный gid
        gid = self.n_gid
        
        # Определяем целевой процесс
        target_rank = gid % nhost
        
        if rank == target_rank:
            try:
                # --- ВЫБОР moto ---
                available_mn = list(set(mn) - set(getattr(self, "used_mn", [])))
                if not available_mn:
                    raise ValueError("All motor neurons in mn have been used already.")
                chosen_mn = random.choice(available_mn)
                self.used_mn = getattr(self, "used_mn", []) + [chosen_mn]
                
                # Проверяем существование клетки
                if not pc.gid_exists(chosen_mn):
                    raise RuntimeError(f"Motor neuron {chosen_mn} does not exist")
                moto = pc.gid2cell(chosen_mn)

                # --- ВЫБОР moto2 ---
                available_mn2 = list(set(mn2) - set(getattr(self, "used_mn2", [])))
                if not available_mn2:
                    raise ValueError("All motor neurons in mn2 have been used already.")
                chosen_mn2 = random.choice(available_mn2)
                self.used_mn2 = getattr(self, "used_mn2", []) + [chosen_mn2]
                
                # Проверяем существование клетки
                if not pc.gid_exists(chosen_mn2):
                    raise RuntimeError(f"Motor neuron {chosen_mn2} does not exist")
                moto2 = pc.gid2cell(chosen_mn2)

                # Create the Ia generator
                stim = h.IaGenerator(0.5)
                stim.start = start
                stim.interval = int(1000 / 70)
                stim.number = int(one_step_time / stim.interval) - 5

                # Set pointers for the muscle units
                muscle_unit1 = moto.muscle_unit(0.5)
                muscle_unit2 = moto2.muscle_unit(0.5)
                h.setpointer(muscle_unit1._ref_F_fHill, 'fhill', stim)
                h.setpointer(muscle_unit2._ref_F_fHill, 'fhill2', stim)

                self.stims.append(stim)

                # Создаем и регистрируем соединение
                ncstim = h.NetCon(stim, None)
                ncstim.weight[0] = weight
                self.netcons.append(ncstim)
                
                # Регистрируем gid
                pc.set_gid2node(gid, target_rank)
                pc.cell(gid, ncstim)
                
                # Проверяем регистрацию
                if not pc.gid_exists(gid):
                    raise RuntimeError(f"Failed to register generator gid {gid}")

                # Record spike times
                spike_times = h.Vector()
                ncstim.record(spike_times)
                self.recorded_spikes.append(spike_times)
                
            except Exception as e:
                logging.error(f"Failed to create Ia generator on process {rank}: {str(e)}")
                raise
        
        # Синхронизация после создания
        pc.barrier()
        
        # Проверяем, что генератор доступен на всех процессах
        if not pc.gid_exists(gid):
            logging.error(f"Process {rank}: Generator {gid} is not accessible")
            raise RuntimeError(f"Generator {gid} is not accessible on process {rank}")
        
        # Добавляем gid в список и обновляем счетчик
        self.gener_gids.append(gid)
        self.n_gid = gid + 1
        
        return gid

    def connectinsidenucleus(self, nucleus):
        self.connectcells(nucleus, nucleus, 3, delay=0.5, threshold=-20, inhtype=False, stdptype=False, N=45)

    def add_bs_geners(self, freq, weight_E, weight_F):
        E_bs_gids = []
        F_bs_gids = []
        for step in range(step_number):
            F_bs_gids.append(self.addgener(int(one_step_time * (2 * step + 1)), freq, False, 1, weight_E))
            E_bs_gids.append(self.addgener(int(one_step_time * 2 * step) + 20, freq, False, 1, weight_F))
        return E_bs_gids, F_bs_gids

    def add_ia_geners(self, mus_E, mus_F):
        E_ia_gids = []
        F_ia_gids = []
        for step in range(step_number):
            E_ia_gids.append(self.addIagener(mus_E, mus_F, 15 + one_step_time * 2 * step, weight=1))
            F_ia_gids.append(self.addIagener(mus_F, mus_E, 15 + one_step_time * (1 + 2 * step), weight=2))
        # E_ia_gids.append(self.addIagener(mus_E, mus_F, start=15, weight=1))
        # F_ia_gids.append(self.addIagener(mus_F, mus_E, start=15 + one_step_time, weight=2))
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
      location: str
          'axon' or 'soma', where to record spikes
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
            else:
                # Запись из сомы (как было раньше)
                vec.record(cell.soma(0.5)._ref_v)

        v_vec.append(vec)
    return v_vec


def force_record(pool):
    ''' Records force from gids of motor neurons muscle unit
      Parameters
      ----------
      pool: list
        neurons gids
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
        neurons gids
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
        with hdf5.File(f'./{file_name}/{name}_sp_{speed}_CVs_{CV_number}_bs_{bs_fr}.hdf5', 'w') as file:
            for i in range(step_number):
                sl = slice((int(1000 / bs_fr) * 40 + i * one_step_time * 40),
                           (int(1000 / bs_fr) * 40 + (i + 1) * one_step_time * 40))
                file.create_dataset('#0_step_{}'.format(i), data=np.array(result)[sl], compression="gzip")
        logging.info("done recording")
    else:
        logging.info(rank)


def spikeout_individual_files(pool, name, version, v_vec):
    ''' Reports individual neuron simulation results into separate files with slices
      Parameters
      ----------
      pool: list
        neurons gids
      name: string
        pool name
      version: int
          test number
      v_vec: list of h.Vector()
          recorded voltage
    '''
    global rank

    if len(pool) > 5:
        pool = pool[:5]
        v_vec = v_vec[:5]

        # Синхронизация всех процессов перед началом работы
    pc.barrier()

    # Создаем для каждого нейрона из списка свой объект h.Vector для локального хранения данных
    neuron_vecs = {}
    for neuron in pool:
        neuron_vecs[neuron] = h.Vector()

    # Каждый процесс по очереди передаёт свои данные для каждого нейрона.
    # Важно, чтобы в каждый момент времени только один процесс занимался передачей данных.
    for proc in range(nhost):
        if proc == rank:
            for idx, neuron in enumerate(pool):
                # Преобразуем данные из v_vec в список и записываем в h.Vector
                data = list(v_vec[idx])
                neuron_vecs[neuron].from_python(data)
        pc.barrier()  # синхронизация между процессами
    pc.barrier()  # дополнительная синхронизация после заполнения данных

    # Собираем данные с каждого процесса для каждого нейрона с помощью py_gather
    gathered_neuron_data = {}
    for neuron in pool:
        gathered_neuron_data[neuron] = pc.py_gather(neuron_vecs[neuron], 0)

    # На процессе с rank == 0 производится запись данных в отдельные файлы
    if rank == 0:
        logging.info("Начало записи индивидуальных файлов для 5 нейронов.")
        for neuron in pool:
            # Объединяем данные, например, усредняя полученные векторы с разных процессов
            vectors_list = [list(vec) for vec in gathered_neuron_data[neuron]]
            combined = np.mean(np.array(vectors_list), axis=0, dtype=np.float32)

            # Формируем имя файла для данного нейрона, например:
            # "./{file_name}/{name}_neuron_{neuron}_v{version}.hdf5"
            file_path = f"./{file_name}/{name}_neuron_{neuron}_v{version}.hdf5"
            with hdf5.File(file_path, 'w') as file:
                # Разбиваем объединённый вектор на срезы и записываем каждый срез в отдельный датасет.
                for i in range(step_number):
                    # Расчёт начала и конца среза. Формулу можно корректировать под ваши данные.
                    start = int(1000 / bs_fr) * 40 + i * one_step_time * 40
                    end = int(1000 / bs_fr) * 40 + (i + 1) * one_step_time * 40
                    dataset_name = f"step_{i}"
                    file.create_dataset(dataset_name, data=combined[start:end], compression="gzip")
        logging.info("Запись индивидуальных файлов для 5 нейронов завершена.")
    else:
        logging.info(f"Процесс с rank {rank} завершил сбор данных для индивидуальных файлов.")


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
    if not os.path.exists(file_name):
        os.mkdir(file_name)

    for i in range(versions):
        cpg_ex = CPG(speed, bs_fr, 100, step_number, N)
        logging.info("created")
        musclerecorders = []
        musclerecorders_extra = []
        force_recorders = []
        muscle_units_recorders = []
        recorders = []
        recorders_extra = []
        for group in cpg_ex.intgroups:
            # recorders_extra.append(spike_record(group[k_nrns], True))
            recorders.append(spike_record(group[k_nrns]))
        for group in cpg_ex.musclegroups:
            musclerecorders.append(spike_record(group[k_nrns]))
            # musclerecorders_extra.append(spike_record(group[k_nrns], True))
            force_recorders.append(force_record(group[k_nrns]))
            muscle_units_recorders.append(spike_record(group[k_nrns], 'muscle'))

        logging.info("added recorders")

        print("- " * 10, "\nstart")
        logging.info("---------------------start")
        t = prun(speed, step_number)
        logging.info("---------------------------end")
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

        for group, recorder in zip(cpg_ex.musclegroups, musclerecorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)
        for group, recorder in zip(cpg_ex.intgroups, recorders):
            spikeout(group[k_nrns], group[k_name], i, recorder)

        for group, recorder in zip(cpg_ex.musclegroups, force_recorders):
            spikeout(group[k_nrns], 'force_{}'.format(group[k_name]), i, recorder)
        for group, recorder in zip(cpg_ex.musclegroups, muscle_units_recorders):
            spikeout(group[k_nrns], 'units_{}'.format(group[k_name]), i, recorder)


        for idx, spike_vec in enumerate(cpg_ex.recorded_spikes):
            with open(f'./{file_name}/spike_times_{idx}.txt', 'w') as f:
                for t in spike_vec:
                    f.write(f"{t}\n")
        logging.info("recorded")

    finish()
