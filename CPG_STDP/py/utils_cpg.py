from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle
from constants import *

def addpool(LEG, num, name, neurontype="int") -> list:
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
        gid = LEG.n_gid + i
        all_gids.append(gid)

        # Only create cell if this rank is responsible for this neuron
        if i % nhost == rank:
            if neurontype.lower() == "moto":
                cell = motoneuron(diams[i])
                LEG.motos.append(cell)
            elif neurontype.lower() == "aff":
                cell = bioaffrat()
                LEG.affs.append(cell)
            elif neurontype.lower() == "muscle":
                cell = muscle()
                LEG.muscles.append(cell)
            elif neurontype.lower() == "bursting":
                cell = interneuron(False, bursting_mode=True)
                LEG.ints.append(cell)
            else:
                cell = interneuron(delaytype)
                LEG.ints.append(cell)

            gids.append(gid)
            pc.set_gid2node(gid, rank)
            nc = cell.connect2target(None)
            pc.cell(gid, nc)
            log_gid_by_lookup(LEG, gid, neurontype.lower())
            LEG.netcons.append(nc)

    # Update n_gid for next pool
    LEG.n_gid += num

    # Groups - store all GIDs, not just local ones
    if neurontype.lower() == "muscle":
        LEG.musclegroups.append((all_gids, name))
    elif neurontype.lower() == "moto":
        LEG.motogroups.append((all_gids, name))
    elif neurontype.lower() == "aff":
        LEG.affgroups.append((all_gids, name))
    else:
        LEG.intgroups.append((all_gids, name))

    return all_gids

def connectcells(LEG, pre_cells, post_cells, weight=1.0, delay=1, threshold=10, inhtype=False,
                 stdptype=False, N=50, sect="int"):
    print(f"🔗 [rank {rank}] connectcells: pre_cells={len(pre_cells)}, post_cells={len(post_cells)}")
    print(f"   weight={weight}, delay={delay}, threshold={threshold}, inhtype={inhtype}, stdptype={stdptype}")
    logging.info(f"connectcells start: pre={len(pre_cells)}, post={len(post_cells)}, stdp={stdptype}")

    nsyn = random.randint(N, N + 15)
    print(f"   nsyn={nsyn}")

    connection_count = 0

    for post_idx, post_gid in enumerate(post_cells):
        print(f"   Processing post_cell {post_idx + 1}/{len(post_cells)}: gid={post_gid}")

        if pc.gid_exists(post_gid):
            print(f"   ✅ GID {post_gid} exists on this rank")

            try:
                target = pc.gid2cell(post_gid)
                target_type = type(target).__name__
                print(f"   Target type: {target_type}")
                logging.info(f"Target {post_gid} type: {target_type}")

                for i in range(nsyn):
                    src_gid = random.randint(pre_cells[0], pre_cells[-1])
                    print(f"     Synapse {i + 1}/{nsyn}: src_gid={src_gid} -> post_gid={post_gid}")

                    if stdptype:
                        print(f"     🧠 Creating STDP connection...")
                        logging.info(f"STDP connection: {src_gid} -> {post_gid}")

                        try:
                            # Проверяем наличие STDP синапсов
                            if not hasattr(target, 'synlistexstdp'):
                                print(f"     ❌ Target {target_type} has no synlistexstdp")
                                logging.error(f"No synlistexstdp in {target_type}")
                                continue

                            if len(target.synlistexstdp) <= i:
                                print(f"     ❌ synlistexstdp[{i}] out of range (len={len(target.synlistexstdp)})")
                                logging.error(f"synlistexstdp index {i} out of range")
                                continue

                            syn = target.synlistexstdp[i]
                            print(f"     ✅ Got STDP synapse: {type(syn).__name__}")

                            # Создаем основное соединение
                            nc = pc.gid_connect(src_gid, syn)
                            nc.delay = delay
                            nc.weight[0] = weight
                            nc.threshold = threshold
                            pc.threshold(src_gid, threshold)
                            LEG.netcons.append(nc)
                            print(f"     ✅ Main NetCon created")

                            # Создаем STDP механизм
                            print(f"     Creating STDP mechanism...")
                            dummy = h.Section()  # Create a dummy section to put the point processes in
                            print(f"     ✅ Dummy section created")

                            try:
                                stdpmech = h.STDP(0, dummy)
                                print(f"     ✅ STDP mechanism created: {type(stdpmech).__name__}")
                                LEG.stdpmechs.append(stdpmech)
                            except Exception as stdp_error:
                                print(f"     ❌ STDP creation failed: {stdp_error}")
                                logging.error(f"STDP creation error: {stdp_error}")
                                continue

                            # Пресинаптическое соединение
                            print(f"     Creating presynaptic connection...")
                            presyn = pc.gid_connect(src_gid, stdpmech)
                            presyn.delay = delay
                            presyn.weight[0] = 2
                            presyn.threshold = threshold
                            LEG.presyns.append(presyn)
                            print(f"     ✅ Presynaptic NetCon created")

                            # Постсинаптическое соединение
                            print(f"     Creating postsynaptic connection...")
                            pstsyn = pc.gid_connect(post_gid, stdpmech)
                            pstsyn.delay = delay
                            pstsyn.weight[0] = -2
                            pstsyn.threshold = threshold
                            LEG.postsyns.append(pstsyn)
                            pc.threshold(post_gid, threshold)
                            print(f"     ✅ Postsynaptic NetCon created")

                            # Установка указателя
                            print(f"     Setting pointer...")
                            try:
                                h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
                                print(f"     ✅ Pointer set successfully")
                            except Exception as pointer_error:
                                print(f"     ❌ Pointer setting failed: {pointer_error}")
                                logging.error(f"Pointer error: {pointer_error}")

                            # Запись изменений весов
                            weight_changes = h.Vector()
                            weight_changes.record(stdpmech._ref_synweight)
                            LEG.weight_changes_vectors.append((src_gid, post_gid, weight_changes))
                            print(f"     ✅ Weight recording set up")

                            connection_count += 1

                        except Exception as stdp_conn_error:
                            print(f"     ❌ STDP connection error: {stdp_conn_error}")
                            logging.error(f"STDP connection error {src_gid}->{post_gid}: {stdp_conn_error}")

                    else:
                        print(f"     🔗 Creating regular connection...")
                        try:
                            if inhtype:
                                if not hasattr(target, 'synlistinh'):
                                    print(f"     ❌ Target {target_type} has no synlistinh")
                                    continue
                                syn = target.synlistinh[i]
                                print(f"     ✅ Got inhibitory synapse")
                            else:
                                if not hasattr(target, 'synlistex'):
                                    print(f"     ❌ Target {target_type} has no synlistex")
                                    continue
                                syn = target.synlistex[i]
                                print(f"     ✅ Got excitatory synapse")

                            nc = pc.gid_connect(src_gid, syn)
                            nc.weight[0] = random.gauss(weight, weight / 5)
                            nc.threshold = threshold
                            nc.delay = random.gauss(delay, delay / 5)
                            LEG.netcons.append(nc)
                            print(f"     ✅ Regular NetCon created")
                            connection_count += 1

                        except Exception as reg_conn_error:
                            print(f"     ❌ Regular connection error: {reg_conn_error}")
                            logging.error(f"Regular connection error {src_gid}->{post_gid}: {reg_conn_error}")

            except Exception as target_error:
                print(f"   ❌ Error getting target for GID {post_gid}: {target_error}")
                logging.error(f"Target error {post_gid}: {target_error}")

        else:
            print(f"   ⏭️ GID {post_gid} not on this rank")

    print(f"🏁 connectcells finished: {connection_count} connections created")
    logging.info(f"connectcells end: {connection_count} connections created")

def genconnect(LEG, gen_gid, afferents_gids, weight, delay, inhtype=False, N=50):
    nsyn = random.randint(N - 5, N)
    for i in afferents_gids:
        if pc.gid_exists(i):
            for j in range(nsyn):
                target = pc.gid2cell(i)
                if inhtype:
                    syn = target.synlistinh[j]
                else:
                    syn = target.synlistex[j]
                nc = pc.gid_connect(gen_gid, syn)
                nc.threshold = LEG.threshold
                nc.delay = random.gauss(delay, delay / 5)
                nc.weight[0] = random.gauss(weight, weight / 6)
                LEG.stimnclist.append(nc)

def motodiams(LEG, number):
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
    
def add_bs_geners(LEG, freq, spikes_per_step):
        E_bs_gids = []
        F_bs_gids = []
        for step in range(step_number):
            F_bs_gids.append(addgener(int(one_step_time * (2 * step + 1)), freq, False, 1))
            E_bs_gids.append(addgener(int(one_step_time * 2 * step) + 10, freq, False, 1))
        return E_bs_gids, F_bs_gids

def log_gid_by_lookup(LEG, gid: int, name):
        if not pc.gid_exists(gid):
            print(f"[rank {rank}] GID {gid} not assigned to this process.")
            return

        obj = pc.gid2cell(gid)
        typename = type(obj).__name__
        if name:
            print(f"[rank {rank}] Added GID {gid} (type: {typename}) - name: {name}")
        else: print(f"[rank {rank}] Added GID {gid} (type: {typename})")


def addgener(LEG, start, freq, flg_interval, interval, cv=False, r=True):
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
    gid = LEG.n_gid
    # Only create generator on rank 0 to avoid duplicates
    if rank == 0:
        stim = h.NetStim()
        # stim.number = nums
        if r:
            stim.start = random.uniform(start - 3, start + 3)
            stim.noise = 0.05
        else:
            stim.start = start
        if cv:
            stim.interval = int(1000 / freq)
            stim.number = int(int(one_step_time / stim.interval) / CV_number) + 0.45 * int(
                int(one_step_time / stim.interval) / CV_number)
        else:
            stim.interval = int(1000 / freq)
            stim.number = int(one_step_time / stim.interval) - 7
        LEG.stims.append(stim)
        pc.set_gid2node(gid, rank)
        ncstim = h.NetCon(stim, None)
        LEG.netcons.append(ncstim)
        pc.cell(gid, ncstim)
        log_gid_by_lookup(LEG, gid, "gen")
    else:
        # Other ranks just need to know the GID is assigned to rank 0
        pc.set_gid2node(gid, 0)

    LEG.gener_gids.append(gid)
    LEG.n_gid += 1

    return gid