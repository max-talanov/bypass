from constants import *

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


def velocity_record(gids, attr='_ref_vel'):
    """
    Records velocity-related variable (vel or v0) from IaGenerator instances

    Parameters
    ----------
    gids : list of int
        gids of IaGenerator processes
    attr : str
        which attribute to record ('_ref_vel' or '_ref_v0')

    Returns
    -------
    vecs : list of h.Vector()
        list of recorded vectors for each gid
    """
    vecs = []
    for gid in gids:
        cell = pc.gid2cell(gid)
        vec = h.Vector(np.zeros(int(time_sim / 0.025 + 1), dtype=np.float32))
        vec.record(getattr(cell, attr))
        vecs.append(vec)
    return vecs


def spikeout(pool, name, version, v_vec, leg):
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

    # Создаем директорию для индивидуальных записей, если её нет
    if rank == 0:
        individual_dir = f'./{file_name}/{name}_individual'
        if not os.path.exists(individual_dir):
            os.makedirs(individual_dir)

    for i in range(nhost):
        if i == rank:
            # Подготовка средних значений (как в оригинале)
            outavg = []
            for j in range(len(pool)):
                outavg.append(list(v_vec[j]))

                # Сохранение индивидуальных значений для каждого нейрона
                if rank == 0:  # Сохраняем только на узле 0 для простоты
                    individual_file = f'{individual_dir}/neuron_{pool[j]}_sp_{speed}_CVs_{CV_number}_bs_{bs_fr}_{leg}.hdf5'
                    with hdf5.File(individual_file, 'w') as indiv_file:
                        neuron_data = list(v_vec[j])
                        for step in range(step_number):
                            sl = slice((int(1000 / bs_fr) * 40 + step * one_step_time * 40),
                                       (int(1000 / bs_fr) * 40 + (step + 1) * one_step_time * 40))
                            indiv_file.create_dataset(f'#0_step_{step}', data=np.array(neuron_data)[sl],
                                                      compression="gzip")

            # Продолжение обработки средних значений
            outavg = np.mean(np.array(outavg), axis=0, dtype=np.float32)
            vec = vec.from_python(outavg)
        pc.barrier()

    pc.barrier()
    result = pc.py_gather(vec, 0)

    # Сохранение средних значений (как в оригинале)
    if rank == 0:
        logging.info("start recording " + name)
        result = np.mean(np.array(result), axis=0, dtype=np.float32)
        with hdf5.File(f'./{file_name}/{name}_sp_{speed}_CVs_{CV_number}_bs_{bs_fr}_{leg}.hdf5', 'w') as file:
            for i in range(step_number):
                sl = slice((int(1000 / bs_fr) * 40 + i * one_step_time * 40),
                           (int(1000 / bs_fr) * 40 + (i + 1) * one_step_time * 40))
                file.create_dataset('#0_step_{}'.format(i), data=np.array(result)[sl], compression="gzip")
        logging.info("done recording average")
        logging.info("done recording individual neurons")
    else:
        logging.info(rank)

def setup_recorders(leg, recorder_list, group_attr, group_name):
    """Настраивает рекордеры для указанной группы нейронов"""
    print(f"      Setting up {group_name} recorders...")
    recorder_list.extend(spike_record(group[k_nrns]) for group in getattr(leg, group_attr))


def generator_spikeout(gen_vecs, name, version, leg):
    """
    Saves generator spike times
    Parameters
    ----------
    gen_vecs : list of (gid, h.Vector)
        recorded generator spike times
    name : str
        generator group name
    version : int
        test number
    leg : str
        left / right
    """
    global rank
    pc.barrier()

    if rank == 0:
        gen_dir = f'./{file_name}/{name}_generators'
        if not os.path.exists(gen_dir):
            os.makedirs(gen_dir)

    pc.barrier()

    local_data = [(gid, list(vec)) for gid, vec in gen_vecs]

    gathered = pc.py_gather(local_data, 0)

    if rank == 0:
        logging.info(f"start recording generators {name}")

        # gathered = [rank0_data, rank1_data, ...]
        for rank_data in gathered:
            if rank_data is None:
                continue
            for gid, spikes in rank_data:
                fname = (
                    f'{gen_dir}/gen_{gid}_rank{rank}_'
                    f'sp_{speed}_CVs_{CV_number}_bs_{bs_fr}_{leg}_v{version}.hdf5'
                )
                with hdf5.File(fname, 'w') as f:
                    f.create_dataset(
                        'spike_times',
                        data=np.array(spikes, dtype=np.float32),
                        compression="gzip"
                    )

        logging.info("done recording generators")
