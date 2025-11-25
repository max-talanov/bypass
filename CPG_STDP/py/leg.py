from constants import *
from utils_cpg import *

class LEG:

    def __init__(self, speed, bs_fr, inh_p, step_number, n, leg_l=False):
        logging.info(f"Hello from rank {rank} of {nhost}")
        logging.info("NEURON version: " + h.nrnversion())
        self.threshold = 10
        self.delay = 1
        self.nAff = 5 #15 #35 #5
        self.nInt = 5 #10 #21 #5
        self.nMn = 5 #10 #21 #5
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
        self.gener_Iagids = []
        # self.n_gid = get_gid()

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
        self.V0v = []
        self.V3F = []
        self.V0d = []
        self.V2a = []

        for layer in range(CV_number):
            '''cut and muscle feedback'''
            self.dict_CV_1 = {layer: 'CV{}_1'.format(layer + 1)}
            self.dict_RG_E = {layer: 'RG{}_E'.format(layer + 1)}
            self.dict_RG_F = {layer: 'RG{}_F'.format(layer + 1)}
            self.dict_V3F = {layer: 'V3{}_F'.format(layer + 1)}
            self.dict_C = {layer: 'C{}'.format(layer + 1)}

        for layer in range(CV_number):
            '''Cutaneous pools'''
            self.dict_CV_1[layer] = addpool(self, self.ncell, "CV" + str(layer + 1) + "_1", "aff")
            '''Rhythm generator pools'''
            self.dict_RG_E[layer] = addpool(self, self.ncell, "RG" + str(layer + 1) + "_E", "int")
            self.dict_RG_F[layer] = addpool(self, self.ncell, "RG" + str(layer + 1) + "_F", "int")
            self.RG_E.append(self.dict_RG_E[layer])
            self.RG_F.append(self.dict_RG_F[layer])
            self.CV.append(self.dict_CV_1[layer])

        '''RG'''
        self.RG_E = sum(self.RG_E, [])
        self.InE = addpool(self, self.nInt, "InE", "int")
        self.RG_F = sum(self.RG_F, [])
        self.InF = addpool(self, self.nInt, "InF", "int")

        self.In1 = addpool(self, self.nInt, "In1", "int")

        self.V0v = addpool(self, self.nInt, "V0v", "int")
        self.V2a = addpool(self, self.nInt, "V2a", "int")
        self.V0d = addpool(self, self.nInt, "V0d", "int")

        self.CV = sum(self.CV, [])


        '''cutaneous inputs'''
        cfr = 90
        c_int = 1000 / cfr

        '''cutaneous inputs generators'''
        for layer in range(CV_number):
            self.dict_C[layer] = []
            for i in range(step_number):
                step_leg = 10 + speed * layer + i * (speed * CV_number + CV_0_len + one_step_time) + 7 - layer * 12
                if leg_l:
                    step_leg += one_step_time
                self.dict_C[layer].append(
                    addgener(self, step_leg, cfr,
                        True, int((one_step_time / CV_number) * 0.15), cv=True))

        for layer in range(CV_number):
            self.C_1.append(self.dict_CV_1[layer])
        self.C_1 = sum(self.C_1, [])

        '''cutaneous inputs'''
        for layer in range(CV_number):
            connectcells(self, self.dict_C[layer], self.dict_CV_1[layer], 0.15 * k * speed, 2)
            connectcells(self, self.dict_CV_1[layer], self.dict_RG_E[layer], 0.0035 * k * speed, 3)


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
        weight: float
            weight of the connection
        Returns
        -------
        gid: int
            generators gid
        '''
        print(f"🎯 [rank {rank}] Creating IaGenerator: start={start}, weight={weight}")
        logging.info(f"IaGenerator creation start: start={start}, weight={weight}")

        gid = get_gid()
        print(f"   Assigned GID: {gid}")

        # Only create on rank 0 to avoid conflicts
        if rank == 0:
            try:
                # Check if we have motor neurons available
                if not mn or not mn2:
                    print(f"   ❌ Empty motor neuron lists")
                    logging.error("Empty motor neuron lists for IaGenerator")
                    return gid

                # Get random motor neurons from the lists
                moto_gid = random.choice(mn)
                moto2_gid = random.choice(mn2)
                print(f"   Selected motor neurons: {moto_gid}, {moto2_gid}")

                # Check if motor neurons exist on any rank
                moto_rank = None
                moto2_rank = None
                for r in range(nhost):
                    if pc.gid_exists(moto_gid):
                        moto_rank = r
                    if pc.gid_exists(moto2_gid):
                        moto2_rank = r

                if moto_rank is None or moto2_rank is None:
                    print(f"   ⚠️ Motor neurons not found locally, creating simplified IaGenerator")
                    # Create simplified generator without muscle connections
                    stim = h.IaGenerator()
                    stim.start = start
                    stim.interval = int(1000 / bs_fr)
                    stim.number = int(one_step_time / stim.interval) - 2

                    self.stims.append(stim)
                    pc.set_gid2node(gid, rank)
                    ncstim = h.NetCon(stim, None)
                    ncstim.weight[0] = weight
                    self.netcons.append(ncstim)
                    pc.cell(gid, ncstim)

                else:
                    # Create full IaGenerator with muscle connections
                    moto = pc.gid2cell(moto_gid)
                    moto2 = pc.gid2cell(moto2_gid)
                    print(f"   Got motor neuron objects: {type(moto).__name__}, {type(moto2).__name__}")

                    stim = h.IaGenerator()
                    print(f"   ✅ IaGenerator created: {type(stim).__name__}")
                    logging.info(f"IaGenerator object created successfully")

                    stim.start = start
                    stim.interval = int(1000 / bs_fr)
                    stim.number = int(one_step_time / stim.interval) - 2
                    print(f"   Parameters set: start={stim.start}, interval={stim.interval}, number={stim.number}")

                    self.stims.append(stim)

                    # Set pointers if motor neurons have muscle_unit
                    try:
                        if hasattr(moto, 'muscle_unit'):
                            h.setpointer(moto.muscle_unit(0.5)._ref_F_fHill, 'fhill', stim)
                            print(f"   ✅ First pointer set (fhill)")
                    except Exception as ptr1_error:
                        print(f"   ⚠️ First pointer warning: {ptr1_error}")

                    try:
                        if hasattr(moto2, 'muscle_unit'):
                            h.setpointer(moto2.muscle_unit(0.5)._ref_F_fHill, 'fhill2', stim)
                            print(f"   ✅ Second pointer set (fhill2)")
                    except Exception as ptr2_error:
                        print(f"   ⚠️ Second pointer warning: {ptr2_error}")

                    pc.set_gid2node(gid, rank)
                    ncstim = h.NetCon(stim, None)
                    ncstim.weight[0] = weight
                    self.netcons.append(ncstim)
                    pc.cell(gid, ncstim)

                log_gid_by_lookup(self, gid, "Ia")
                print(f"🎯 IaGenerator creation completed successfully: GID={gid}")
                logging.info(f"IaGenerator creation completed: GID={gid}")

            except Exception as ia_error:
                print(f"❌ IaGenerator creation failed: {ia_error}")
                logging.error(f"IaGenerator creation failed: {ia_error}")
                # Still increment GID to maintain consistency
                pass

        else:
            # Other ranks just register the GID assignment
            pc.set_gid2node(gid, 0)

        self.gener_Iagids.append(gid)
        return gid

    def connectinsidenucleus(self, nucleus):
        connectcells(self, nucleus, nucleus, 0.25, 0.5)

    def add_ia_geners(self, leg_l):
        E_ia_gids = []
        F_ia_gids = []
        for step in range(step_number):
            # E_ia_gids.append(self.addIagener(self.muscle_E, self.muscle_F, 10, weight=5))
            # F_ia_gids.append(self.addIagener(self.muscle_F, self.muscle_E, one_step_time, weight=8))
            start_time_e = 15 + one_step_time * 2 * step
            start_time_f = 15 + one_step_time * (1 + 2 * step)
            if leg_l:
                start_time_e += one_step_time + 4
                start_time_f += one_step_time + 4
            E_ia_gids.append(self.addIagener(self.muscle_E, self.muscle_F, start_time_e, weight=0.1))
            F_ia_gids.append(
                self.addIagener(self.muscle_F, self.muscle_E, start_time_f, weight=0.1))
        return E_ia_gids, F_ia_gids