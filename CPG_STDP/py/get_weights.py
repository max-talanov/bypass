from rybak_rat_cpg import rybak_rat_cpg

def stdp_weight_record(list):
    ''' Records spikes from gids
      Parameters
      ----------
      list
        list of nc connections
      Returns
      -------
      w_vec: list of h.Vector()
          recorded weights
    '''
    w_vec = []

    for i in list:
        vec = h.Vector(np.zeros(int(time_sim/0.025 + 1), dtype=np.float32))
        vec.record(i._ref_weight[0])
        w_vec.append(vec)
    return w_vec

def weights_out(lst, name, version, w_vec):
    ''' Reports simulation results
      Parameters
      ----------
      list
        list of stdp connections
      version: int
          test number
      w_vec: list of h.Vector()
          recorded weights
    '''
    global rank
    pc.barrier()
    vec = h.Vector()
    for i in range(nhost):
        if i == rank:
            outavg = []
            for j in range(len()):
                outavg.append(list(w_vec[j]))
            outavg = np.mean(np.array(outavg), axis = 0, dtype=np.float32)
            vec = vec.from_python(outavg)
        pc.barrier()
    pc.barrier()
    result = pc.py_gather(vec, 0)
    if rank == 0:
        logging.info("start recording")
        result = np.mean(np.array(result), axis = 0, dtype=np.float32)
        with hdf5.File('./res/new_rat4_{}_speed_{}_layers_{}1_eeshz_{}.hdf5'.format(name, speed, CV_number, bs_fr), 'w') as file:
            for i in range(step_number):
                sl = slice((int(1000 / bs_fr) * 40 + i * one_step_time * 40), (int(1000 / bs_fr) * 40 + (i + 1) * one_step_time * 40))
                file.create_dataset('#0_step_{}'.format(i), data=np.array(result)[sl], compression="gzip")
    else:
        logging.info(rank)