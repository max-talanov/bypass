from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle
from constants import *


def _flatten_gid_pool(pool):
    """
    Normalize pool arguments for connectcells/genconnect.

    Accepts:
      - flat list of gids: [16, 17, 18, ...]
      - group tuple from intgroups/musclegroups: (gids, name)
      - nested list of pools (e.g. RG_E before sum()): [[...], [...]]
    """
    if pool is None:
        return []
    if isinstance(pool, tuple) and len(pool) >= 1 and isinstance(pool[0], (list, tuple)):
        pool = pool[0]
    gids = []
    for item in pool:
        if isinstance(item, (list, tuple)):
            gids.extend(int(g) for g in item)
        else:
            gids.append(int(item))
    return gids


def addpool(leg, num, name, neurontype="int") -> list:
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
    all_gids = []  # All GIDs for this pool across all ranks

    delaytype = False
    if neurontype.lower() == "delay":
        delaytype = True

    if neurontype.lower() == "moto":
        diams = motodiams(num)

    # Create GIDs for all neurons in pool (distributed across ranks)
    for i in range(num):
        gid = get_gid()
        all_gids.append(gid)

        # Only create cell if this rank is responsible for this neuron
        if i % nhost == rank:
            if neurontype.lower() == "moto":
                cell = motoneuron(diams[i])
                leg.motos.append(cell)
            elif neurontype.lower() == "aff":
                cell = bioaffrat()
                leg.affs.append(cell)
            elif neurontype.lower() == "muscle":
                cell = muscle()
                leg.muscles.append(cell)
            elif neurontype.lower() == "bursting":
                cell = interneuron(False, bursting_mode=True)
                leg.ints.append(cell)
            else:
                cell = interneuron(delaytype)
                leg.ints.append(cell)

            gids.append(gid)
            pc.set_gid2node(gid, rank)
            nc = cell.connect2target(None)
            pc.cell(gid, nc)
            log_gid_by_lookup(leg, gid, neurontype.lower())
            leg.netcons.append(nc)

    # Groups - store all GIDs, not just local ones
    if neurontype.lower() == "muscle":
        leg.musclegroups.append((all_gids, name))
    elif neurontype.lower() == "moto":
        leg.motogroups.append((all_gids, name))
    elif neurontype.lower() == "aff":
        leg.affgroups.append((all_gids, name))
    else:
        leg.intgroups.append((all_gids, name))

    return all_gids


def connectcells(leg, pre_cells, post_cells, weight=1.0, delay=1, threshold=10, inhtype=False,
                 stdptype=False, N=50, sect="int", pre_name="UNKNOWN_PRE", post_name="UNKNOWN_POST",
                 use_synlistees=False):
    pre_gids = _flatten_gid_pool(pre_cells)
    post_gids = _flatten_gid_pool(post_cells)
    if not pre_gids:
        logging.error(f"connectcells: empty pre_gids for {pre_name} -> {post_name}")
        return
    if not post_gids:
        logging.error(f"connectcells: empty post_gids for {pre_name} -> {post_name}")
        return

    # Removed verbose start logging to reduce log volume.

    nsyn_requested = random.randint(N, N + 15)
    connection_count = 0
    regular_errors = 0
    stdp_errors = 0
    target_errors = 0
    clamped_synapses = 0

    for post_idx, post_gid in enumerate(post_gids):
        post_gid = int(post_gid)
        if pc.gid_exists(post_gid):
            try:
                target = pc.gid2cell(post_gid)
                target_type = type(target).__name__

                if stdptype:
                    avail = len(getattr(target, 'synlistexstdp', []))
                elif inhtype:
                    avail = len(getattr(target, 'synlistinh', []))
                elif use_synlistees and getattr(target, 'synlistees', None):
                    avail = len(target.synlistees)
                else:
                    avail = len(getattr(target, 'synlistex', []))
                nsyn = min(nsyn_requested, avail)
                if nsyn < nsyn_requested:
                    clamped_synapses += 1

                for i in range(nsyn):
                    src_gid = int(random.choice(pre_gids))

                    if stdptype:
                        try:
                            if not hasattr(target, 'synlistexstdp'):
                                logging.error(f"No synlistexstdp in {target_type}")
                                continue

                            if len(target.synlistexstdp) <= i:
                                logging.error(f"synlistexstdp index {i} out of range")
                                continue

                            syn = target.synlistexstdp[i]

                            nc = pc.gid_connect(int(src_gid), syn)
                            nc.delay = delay
                            nc.weight[0] = weight
                            nc.threshold = threshold
                            pc.threshold(int(src_gid), threshold)
                            leg.netcons.append(nc)

                            try:
                                stdpmech = h.STDP(0.5, sec=target.soma)
                                leg.stdpmechs.append(stdpmech)
                            except Exception as stdp_error:
                                logging.error(
                                    f"STDP creation error {src_gid}->{post_gid}: {stdp_error}"
                                )
                                continue

                            pc.threshold(src_gid, threshold)
                            pc.threshold(post_gid, threshold)

                            presyn = pc.gid_connect(src_gid, stdpmech)
                            presyn.delay = delay
                            presyn.weight[0] = 2
                            presyn.threshold = threshold
                            leg.presyns.append(presyn)

                            pstsyn = pc.gid_connect(post_gid, stdpmech)
                            pstsyn.delay = delay
                            pstsyn.weight[0] = -2
                            pstsyn.threshold = threshold
                            leg.postsyns.append(pstsyn)

                            pointer_ok = False
                            try:
                                h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
                                pointer_ok = True
                            except Exception as pointer_error:
                                logging.error(f"Pointer error: {pointer_error}")

                            if pointer_ok:
                                weight_changes = h.Vector()
                                weight_changes.record(stdpmech._ref_synweight, 10.0)
                                leg.weight_changes_vectors.append((src_gid, post_gid, weight_changes))

                            connection_count += 1

                        except Exception as stdp_conn_error:
                            stdp_errors += 1

                    else:
                        # print(f"     🔗 Creating regular connection...")
                        try:
                            if inhtype:
                                if not hasattr(target, 'synlistinh'):
                                    # print(f"     ❌ Target {target_type} has no synlistinh")
                                    continue
                                syn = target.synlistinh[i]
                                # print(f"     ✅ Got inhibitory synapse")
                            else:
                                if use_synlistees and getattr(target, 'synlistees', None):
                                    if len(target.synlistees) <= i:
                                        continue
                                    syn = target.synlistees[i]
                                elif not hasattr(target, 'synlistex'):
                                    # print(f"     ❌ Target {target_type} has no synlistex")
                                    continue
                                else:
                                    syn = target.synlistex[i]
                                # print(f"     ✅ Got excitatory synapse")

                            nc = pc.gid_connect(int(src_gid), syn)
                            nc.weight[0] = random.gauss(weight, weight / 5)
                            nc.threshold = threshold
                            nc.delay = random.gauss(delay, delay / 5)
                            leg.netcons.append(nc)
                            # print(f"     ✅ Regular NetCon created")
                            connection_count += 1

                        except Exception as reg_conn_error:
                            regular_errors += 1

            except Exception as target_error:
                target_errors += 1

        else:
            continue

    if regular_errors or stdp_errors or target_errors or clamped_synapses:
        logging.warning(
            "connectcells summary | %s(%s) -> %s(%s) | created=%s | "
            "regular_errors=%s | stdp_errors=%s | target_errors=%s | clamped_synapses=%s",
            pre_name,
            len(pre_gids),
            post_name,
            len(post_gids),
            connection_count,
            regular_errors,
            stdp_errors,
            target_errors,
            clamped_synapses,
        )


def genconnect(leg, gen_gid, afferents_gids, weight, delay, inhtype=False, N=50, gen_name="GEN", target_name="TARGET"):
    nsyn_requested = random.randint(N - 5, N)
    gen_gid = int(gen_gid)
    aff_gids = _flatten_gid_pool(afferents_gids)
    clamped_synapses = 0
    for i in aff_gids:
        if pc.gid_exists(i):
            target = pc.gid2cell(i)
            if inhtype:
                avail = len(target.synlistinh)
            elif getattr(target, 'synlistees', None):
                avail = len(target.synlistees)
            else:
                avail = len(target.synlistex)
            nsyn = min(nsyn_requested, avail)
            if nsyn < nsyn_requested:
                clamped_synapses += 1
            for j in range(nsyn):
                if inhtype:
                    syn = target.synlistinh[j]
                elif getattr(target, 'synlistees', None) and len(target.synlistees) > j:
                    syn = target.synlistees[j]
                else:
                    syn = target.synlistex[j]
                nc = pc.gid_connect(gen_gid, syn)
                nc.threshold = leg.threshold
                nc.delay = random.gauss(delay, delay / 5)
                nc.weight[0] = random.gauss(weight, weight / 6)

                # ---------------------------------------
                # ЛОГИРУЕМ СОЕДИНЕНИЕ
                # ---------------------------------------
                # logger_genconnect.info(
                #     "NetCon created | %s(%s) -> %s(%s) | syn_index=%s | "
                #     "threshold=%.4f | delay=%.4f | weight=%.4f | inhtype=%s",
                #     gen_name,
                #     gen_gid,
                #     target_name,
                #     i,
                #     j,
                #     nc.threshold,
                #     nc.delay,
                #     nc.weight[0],
                #     inhtype
                # )
                # ---------------------------------------
                leg.stimnclist.append(nc)
    if clamped_synapses:
        logging.warning(
            "genconnect summary | %s(%s) -> %s(%s) | clamped_synapses=%s",
            gen_name,
            gen_gid,
            target_name,
            len(aff_gids),
            clamped_synapses,
        )


def motodiams(number):
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


def add_bs_geners(freq, LEG_L, LEG_R):
    left_E_bs_gids = []
    left_F_bs_gids = []
    right_E_bs_gids = []
    right_F_bs_gids = []

    interval = int(1000 / freq)
    number = int(one_step_time / interval) - 2
    _is_rank0 = (rank == 0)
    _NetStim = h.NetStim
    _NetCon = h.NetCon
    _Vector = h.Vector
    _set_gid2node = pc.set_gid2node
    _cell = pc.cell

    for step in range(step_number):
        f_start = one_step_time * (2 * step + 1)
        e_start = int(one_step_time * 2 * step) + 10

        for leg_obj, start, gid_list in (
            (LEG_R, f_start, right_F_bs_gids),
            (LEG_R, e_start, right_E_bs_gids),
            (LEG_L, f_start, left_E_bs_gids),
            (LEG_L, e_start, left_F_bs_gids),
        ):
            gid = get_gid()
            if _is_rank0:
                stim = _NetStim()
                stim.start = start
                stim.interval = interval
                stim.number = number
                # logger_addgener.info(
                #     "STIM created | gid=%s | start=%.3f | interval=%s | number=%s  | cv=%s | r=%s",
                #     gid, stim.start, interval, number, False, False
                # )
                leg_obj.stims.append(stim)
                _set_gid2node(gid, rank)
                ncstim = _NetCon(stim, None)
                spike_times = _Vector()
                ncstim.record(spike_times)
                leg_obj.gen_spike_vectors.append((gid, spike_times))
                leg_obj.netcons.append(ncstim)
                _cell(gid, ncstim)
                log_gid_by_lookup(leg_obj, gid, "gen")
            else:
                _set_gid2node(gid, 0)
            leg_obj.gener_gids.append(gid)
            gid_list.append(gid)

    return left_E_bs_gids, left_F_bs_gids, right_E_bs_gids, right_F_bs_gids

def log_gid_by_lookup(leg, gid: int, name):
    return


def addgener(leg, start, freq, cv=False, r=True):
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
    gid = get_gid()
    # Only create generator on rank 0 to avoid duplicates
    if rank == 0:
        stim = h.NetStim()

        if r:
            stim.start = random.uniform(start - 3, start + 3)
            stim.noise = 0.05
        else:
            stim.start = start

        interval = int(1000 / freq)
        stim.interval = interval

        if cv:
            base_cv = int(one_step_time / interval) // CV_number
            stim.number = int(1.45 * base_cv)
        else:
            stim.number = int(one_step_time / interval) - 2

        # -----------------------------------------
        # ЛОГИРУЕМ ВСЕ ПАРАМЕТРЫ STIM
        # -----------------------------------------
        # Detailed STIM logging is disabled to keep logs compact.
        # logger_addgener.info(
        #     "STIM created | gid=%s | start=%.3f | interval=%s | number=%s  | cv=%s | r=%s",
        #     gid, stim.start, interval, stim.number, cv, r
        # )
        # -----------------------------------------

        leg.stims.append(stim)
        pc.set_gid2node(gid, rank)
        ncstim = h.NetCon(stim, None)
        spike_times = h.Vector()
        ncstim.record(spike_times)
        leg.gen_spike_vectors.append((gid, spike_times))
        leg.netcons.append(ncstim)
        pc.cell(gid, ncstim)
        log_gid_by_lookup(leg, gid, "gen")

    else:
        # Other ranks just need to know the GID is assigned to rank 0
        pc.set_gid2node(gid, 0)

    leg.gener_gids.append(gid)

    return gid


def create_connect_bs(LEG_L, LEG_R):
    LEG_L.left_E_bs_gids, LEG_L.left_F_bs_gids, LEG_R.right_E_bs_gids, LEG_R.right_F_bs_gids = add_bs_geners(bs_fr, LEG_L, LEG_R)

    ''' BS '''
    '''Left leg'''
    for E_bs_gid in LEG_L.left_E_bs_gids:
        for layer in range(CV_number):
            genconnect(LEG_L, E_bs_gid, LEG_L.dict_RG_E[layer], 1.75, 1, gen_name="E_bs_gid", target_name=f"LEG_L_RG_E_{layer+1}")

    for F_bs_gid in LEG_L.left_F_bs_gids:
        for layer in range(CV_number):
            genconnect(LEG_L, F_bs_gid, LEG_L.dict_RG_F[layer], 1.75, 1, gen_name="F_bs_gid", target_name=f"LEG_L_RG_F_{layer+1}")
            #genconnect(LEG_L, F_bs_gid, LEG_L.V3F, 1.75, 1)

    '''Right leg'''
    for E_bs_gid in LEG_R.right_E_bs_gids:
        for layer in range(CV_number):
            genconnect(LEG_R, E_bs_gid, LEG_R.dict_RG_E[layer], 1.75, 1, gen_name="E_bs_gid", target_name=f"LEG_R_RG_E_{layer+1}")

    for F_bs_gid in LEG_R.right_F_bs_gids:
        for layer in range(CV_number):
            genconnect(LEG_R, F_bs_gid, LEG_R.dict_RG_F[layer], 1.75, 1, gen_name="F_bs_gid", target_name=f"LEG_R_RG_F_{layer+1}")
            #genconnect(LEG_R, F_bs_gid, LEG_R.V3F, 1.75, 1)


def add_external_connections(LEG_L, LEG_R):
    connectcells(LEG_L, LEG_L.V3F, LEG_R.RG_F, weight=0.5, delay=3)
    connectcells(LEG_R, LEG_R.V3F, LEG_L.RG_F, weight=0.5, delay=3)
    connectcells(LEG_L, LEG_L.V0v, LEG_R.In1, weight=1.3, delay=3)
    connectcells(LEG_R, LEG_R.V0v, LEG_L.In1, weight=1.3, delay=3)
    connectcells(LEG_L, LEG_L.V0d, LEG_R.RG_F, weight=1.3, delay=3, inhtype=True)
    connectcells(LEG_R, LEG_R.V0d, LEG_L.RG_F, weight=1.3, delay=3, inhtype=True)


def safe_filename(name: str) -> str:
    """Преобразует строку в безопасное имя файла."""
    return re.sub(r'[^\w\-_.]', '_', name)


def get_gid():
    global global_gid
    global_gid += 1
    return global_gid