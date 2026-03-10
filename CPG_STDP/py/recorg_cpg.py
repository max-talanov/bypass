from constants import *

def spike_record(pool, extra=False, location='soma', max_units = None, seed = 0):
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

    pool = list(pool)
    if max_units is not None and len(pool) > max_units:
        rng = np.random.default_rng(seed)
        pool = rng.choice(pool, size=max_units, replace=False).tolist()

    n = len(pool)
    n_pts = int(time_sim / 0.025 + 1)
    v_vec = [None] * n
    _gid2cell = pc.gid2cell
    _Vector = h.Vector

    if extra:
        get_ref = lambda c: c.soma(0.5)._ref_vext[0]
    elif location == 'axon':
        get_ref = lambda c: c.node[0](1.0)._ref_v
    elif location == 'muscle':
        get_ref = lambda c: c.muscle_unit(0.5)._ref_v
    elif location == 'am':
        get_ref = lambda c: c.muscle_unit(0.5)._ref_AM_CaSP
    else:
        get_ref = lambda c: c.soma(0.5)._ref_v

    for idx in range(n):
        cell = _gid2cell(pool[idx])
        vec = _Vector(n_pts)
        vec.record(get_ref(cell))
        v_vec[idx] = vec
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

    n_pool = len(pool)
    if n_pool > 0:
        n_pts = int(time_sim / 0.025 + 1)
        outavg = np.asarray(v_vec[0], dtype=np.float32).copy()
        for j in range(1, n_pool):
            outavg += np.asarray(v_vec[j], dtype=np.float32)
        outavg /= n_pool
    else:
        outavg = np.empty(0, dtype=np.float32)

    vec = h.Vector()
    vec.from_python(outavg)

    pc.barrier()
    result = pc.py_gather(vec, 0)

    if rank == 0:
        logging.info("start recording " + name)
        out = np.asarray(result[0], dtype=np.float32).copy()
        for r in result[1:]:
            out += np.asarray(r, dtype=np.float32)
        out /= len(result)

        bs_offset = int(1000 / bs_fr) * 40
        step_width = one_step_time * 40
        fname = f'./{file_name}/{name}_sp_{speed}_CVs_{CV_number}_bs_{bs_fr}_{leg}.hdf5'
        with hdf5.File(fname, 'w') as file:
            for i in range(step_number * 2):
                start = bs_offset + i * step_width
                end = start + step_width
                file.create_dataset(f'#0_step_{i}', data=out[start:end], compression="gzip")
        logging.info("done recording average")
    else:
        logging.info(rank)

def setup_recorders(leg, recorder_list, group_attr, group_name):
    """Настраивает рекордеры для указанной группы нейронов"""
    print(f"      Setting up {group_name} recorders...")
    recorder_list.extend([spike_record(group[k_nrns], max_units=2, seed=123) for group in getattr(leg, group_attr)])


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
