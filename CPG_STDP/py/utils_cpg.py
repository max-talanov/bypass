from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle
from constants import *


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
            nc = cell.connect2target(None)

            registered = safe_register_gid(gid, rank, nc)
            if not registered:
                logging.warning(f"[rank {rank}] GID {gid} already registered, skipping cell()")
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


def connectcells(leg, pre_cells, post_cells, pre_name="UNKNOWN_PRE", post_name="UNKNOWN_POST", weight=1.0, delay=1, threshold=10, inhtype=False,
                 stdptype=False, N=50, sect="int"):
    #print(f"🔗 [rank {rank}] connectcells: pre_cells={len(pre_cells)}, post_cells={len(post_cells)}")
    #print(f"   weight={weight}, delay={delay}, threshold={threshold}, inhtype={inhtype}, stdptype={stdptype}")
    logging.info(
        f"connectcells start | "
        f"{pre_name}({len(pre_cells)}) -> {post_name}({len(post_cells)}) | "
        f"stdp={stdptype}, inh={inhtype}"
    )

    nsyn = random.randint(N, N + 15)
    # print(f"   nsyn={nsyn}")

    connection_count = 0

    for post_idx, post_gid in enumerate(post_cells):
        # print(f"   Processing post_cell {post_idx + 1}/{len(post_cells)}: gid={post_gid}")

        if pc.gid_exists(post_gid):
            # print(f"   ✅ GID {post_gid} exists on this rank")

            try:
                target = pc.gid2cell(post_gid)
                target_type = type(target).__name__
                # print(f"   Target type: {target_type}")
                logging.info(f"Target {post_gid} type: {target_type}")

                for i in range(nsyn):
                    pre_cells = list(pre_cells)
                    src_gid = random.choice(pre_cells)
                    logging.info(
                        f"[{pre_name} -> {post_name}] "
                        f"syn {i + 1}/{nsyn}: "
                        f"{src_gid} -> {post_gid}"
                    )

                    if stdptype:
                        # print(f"     🧠 Creating STDP connection...")
                        logging.info(
                            f"STDP [{pre_name}->{post_name}] "
                            f"{src_gid} -> {post_gid}"
                        )

                        try:
                            # Проверяем наличие STDP синапсов
                            if not hasattr(target, 'synlistexstdp'):
                                # print(f"     ❌ Target {target_type} has no synlistexstdp")
                                logging.error(f"No synlistexstdp in {target_type}")
                                continue

                            if len(target.synlistexstdp) <= i:
                                # print(f"     ❌ synlistexstdp[{i}] out of range (len={len(target.synlistexstdp)})")
                                logging.error(f"synlistexstdp index {i} out of range")
                                continue

                            syn = target.synlistexstdp[i]
                            # print(f"     ✅ Got STDP synapse: {type(syn).__name__}")

                            # Создаем основное соединение
                            if not pc.gid_exists(src_gid):
                                logging.warning(f"Source GID {src_gid} does not exist, skipping")
                                continue
                            nc = pc.gid_connect(src_gid, syn)
                            nc.delay = delay
                            nc.weight[0] = weight
                            nc.threshold = threshold
                            pc.threshold(src_gid, threshold)
                            leg.netcons.append(nc)
                            # print(f"     ✅ Main NetCon created")

                            # Создаем STDP механизм
                            # print(f"     Creating STDP mechanism...")
                            dummy = h.Section()  # Create a dummy section to put the point processes in
                            # print(f"     ✅ Dummy section created")

                            try:
                                stdpmech = h.STDP(0, dummy)
                                # print(f"     ✅ STDP mechanism created: {type(stdpmech).__name__}")
                                leg.stdpmechs.append(stdpmech)
                            except Exception as stdp_error:
                                # print(f"     ❌ STDP creation failed: {stdp_error}")
                                logging.error(f"STDP creation error: {stdp_error}")
                                continue

                            # Пресинаптическое соединение
                            # print(f"     Creating presynaptic connection...")
                            presyn = pc.gid_connect(src_gid, stdpmech)
                            presyn.delay = delay
                            presyn.weight[0] = 2
                            presyn.threshold = threshold
                            leg.presyns.append(presyn)
                            # print(f"     ✅ Presynaptic NetCon created")

                            # Постсинаптическое соединение
                            # print(f"     Creating postsynaptic connection...")
                            pstsyn = pc.gid_connect(post_gid, stdpmech)
                            pstsyn.delay = delay
                            pstsyn.weight[0] = -2
                            pstsyn.threshold = threshold
                            leg.postsyns.append(pstsyn)
                            pc.threshold(post_gid, threshold)
                            # print(f"     ✅ Postsynaptic NetCon created")

                            # Установка указателя
                            # print(f"     Setting pointer...")
                            try:
                                h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
                                # print(f"     ✅ Pointer set successfully")
                            except Exception as pointer_error:
                                # print(f"     ❌ Pointer setting failed: {pointer_error}")
                                logging.error(f"Pointer error: {pointer_error}")

                            # Запись изменений весов
                            weight_changes = h.Vector()
                            weight_changes.record(stdpmech._ref_synweight, 1.0)
                            leg.weight_changes_vectors.append((src_gid, post_gid, weight_changes))
                            # print(f"     ✅ Weight recording set up")

                            connection_count += 1

                        except Exception as stdp_conn_error:
                            # print(f"     ❌ STDP connection error: {stdp_conn_error}")
                            logging.error(f"STDP connection error {src_gid}->{post_gid}: {stdp_conn_error}")

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
                                if not hasattr(target, 'synlistex'):
                                    # print(f"     ❌ Target {target_type} has no synlistex")
                                    continue
                                syn = target.synlistex[i]
                                # print(f"     ✅ Got excitatory synapse")

                            nc = pc.gid_connect(src_gid, syn)
                            nc.weight[0] = random.gauss(weight, weight / 5)
                            nc.threshold = threshold
                            nc.delay = random.gauss(delay, delay / 5)
                            leg.netcons.append(nc)
                            # print(f"     ✅ Regular NetCon created")
                            connection_count += 1

                        except Exception as reg_conn_error:
                            # print(f"     ❌ Regular connection error: {reg_conn_error}")
                            logging.error(f"Regular connection error {src_gid}->{post_gid}: {reg_conn_error}")

            except Exception as target_error:
                # print(f"   ❌ Error getting target for GID {post_gid}: {target_error}")
                logging.error(f"Target error {post_gid}: {target_error}")

        else:
            print(f"   ⏭️ GID {post_gid} not on this rank")

    # print(f"🏁 connectcells finished: {connection_count} connections created")
    logging.info(f"connectcells end: {connection_count} connections created")


def genconnect(leg, gen_gid, afferents_gids, weight, delay, gen_name="GEN", target_name="TARGET", inhtype=False, N=50):
    nsyn = random.randint(N - 5, N)
    logger_genconnect.info(
        f"genconnect start | leg={leg.name} | "
        f"{gen_name}({gen_gid}) -> {target_name}({len(afferents_gids)}) | "
        f"nsyn_per_target={nsyn} | "
        f"weight={weight} | delay={delay} | inhtype={inhtype}"
    )
    for i in afferents_gids:
        if pc.gid_exists(i):
            for j in range(nsyn):
                target = pc.gid2cell(i)
                if inhtype:
                    syn = target.synlistinh[j]
                else:
                    syn = target.synlistex[j]
                nc = pc.gid_connect(gen_gid, syn)
                nc.threshold = leg.threshold
                nc.delay = random.gauss(delay, delay / 5)
                nc.weight[0] = random.gauss(weight, weight / 6)

                # ---------------------------------------
                # ЛОГИРУЕМ СОЕДИНЕНИЕ
                # ---------------------------------------
                logger_genconnect.info(
                    "NetCon created | %s(%s) -> %s(%s) | syn_index=%s | "
                    "threshold=%.4f | delay=%.4f | weight=%.4f | inhtype=%s",
                    gen_name,
                    gen_gid,
                    target_name,
                    i,
                    j,
                    nc.threshold,
                    nc.delay,
                    nc.weight[0],
                    inhtype
                )
                # ---------------------------------------
                leg.stimnclist.append(nc)


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
    for step in range(step_number):
        right_F_bs_gids.append(addgener(LEG_R, (one_step_time * (2 * step + 1)), freq, False, r=False))
        right_E_bs_gids.append(addgener(LEG_R, int(one_step_time * 2 * step) + 10, freq, False, r=False))
        # added generators in anti-phase
        left_E_bs_gids.append(addgener(LEG_L, (one_step_time * (2 * step + 1)), freq, False, r=False))
        left_F_bs_gids.append(addgener(LEG_L, int(one_step_time * 2 * step) + 10, freq, False, r=False))
    return left_E_bs_gids, left_F_bs_gids, right_E_bs_gids, right_F_bs_gids

def log_gid_by_lookup(leg, gid: int, name):
    if not pc.gid_exists(gid):
        print(f"[rank {rank}] GID {gid} not assigned to this process.")
        return

    obj = pc.gid2cell(gid)
    typename = type(obj).__name__
    if name:
        print(f"[rank {rank}] Added GID {gid} (type: {typename}) - name: {name}")
    else:
        print(f"[rank {rank}] Added GID {gid} (type: {typename})")


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

        stim.interval = int(1000 / freq)

        if cv:
            stim.number = int(int(int(one_step_time / stim.interval) / CV_number) + \
                          0.45 * int(int(one_step_time / stim.interval) / CV_number))
        else:
            stim.number = int(one_step_time / stim.interval) - 2

        # -----------------------------------------
        # ЛОГИРУЕМ ВСЕ ПАРАМЕТРЫ STIM
        # -----------------------------------------
        logger_addgener.info(
            "STIM created | gid=%s | start=%.3f | interval=%s | number=%s  | cv=%s | r=%s",
            gid,
            stim.start,
            stim.interval,
            stim.number,
            cv,
            r
        )
        # -----------------------------------------

        leg.stims.append(stim)
        ncstim = h.NetCon(stim, None)
        spike_times = h.Vector()
        ncstim.record(spike_times)
        leg.gen_spike_vectors.append((gid, spike_times))
        leg.netcons.append(ncstim)
        registered = safe_register_gid(gid, rank, ncstim)
        if not registered:
            logger_addgener.warning(f"GID {gid} already registered, generator skipped")
        log_gid_by_lookup(leg, gid, "gen")

    else:
        # Other ranks just need to know the GID is assigned to rank 0
        if not pc.gid_exists(gid):
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
    connectcells(LEG_L, LEG_L.V3F, LEG_R.RG_F, weight=1.3, delay=3)
    connectcells(LEG_R, LEG_R.V3F, LEG_L.RG_F, weight=1.3, delay=3)
    connectcells(LEG_L, LEG_L.V0v, LEG_R.In1, weight=1.3, delay=3)
    connectcells(LEG_R, LEG_R.V0v, LEG_L.In1, weight=1.3, delay=3)
    connectcells(LEG_L, LEG_L.V0d, LEG_R.RG_F, weight=1.3, delay=3, inhtype=True)
    connectcells(LEG_R, LEG_R.V0d, LEG_L.RG_F, weight=1.3, delay=3, inhtype=True)


def safe_filename(name: str) -> str:
    """Преобразует строку в безопасное имя файла."""
    return re.sub(r'[^\w\-_.]', '_', name)


def get_gid():
    global global_gid
    gid = rank + global_gid * nhost
    global_gid += 1
    return gid

def safe_register_gid(gid, node, nc=None):
    if pc.gid_exists(gid):
        if pc.gid2node(gid) != node:
            raise RuntimeError(
                f"GID {gid} already exists on node {pc.gid2node(gid)}, "
                f"attempt to assign to node {node}"
            )
        return False

    pc.set_gid2node(gid, node)

    if nc is not None:
        pc.cell(gid, nc)

    return True