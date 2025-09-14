from constants import *
from utils_cpg import *

class LEG:

    def __init__(self, speed, bs_fr, inh_p, step_number, n):
        logging.info(f"Hello from rank {rank} of {nhost}")
        logging.info("NEURON version: " + h.nrnversion())
        self.threshold = 10
        self.delay = 1
        self.nAff = 5 #35
        self.nInt = 5 #21
        self.nMn = 5 #21
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

        '''sensory and muscle afferents and brainstem and V3F'''
        self.Ia_aff_E = addpool(self, self.nAff, "Ia_aff_E", "aff")
        self.Ia_aff_F = addpool(self, self.nAff, "Ia_aff_F", "aff")
        # self.BS_aff_E = addpool(self, self.nAff, "BS_aff_E", "aff")
        # self.BS_aff_F = addpool(self, self.nAff, "BS_aff_F", "aff")
        self.V3F = addpool(self, self.nInt, "V3F", "int")

        '''moto neuron pools'''
        self.mns_E = addpool(self, self.nMn, "mns_E", "moto")
        self.mns_F = addpool(self, self.nMn, "mns_F", "moto")

        '''muscles'''
        self.muscle_E = addpool(self, self.nMn, "muscle_E", "muscle")
        self.muscle_F = addpool(self, self.nMn, "muscle_F", "muscle")

        # '''reflex arc'''
        self.Ia_E = addpool(self, self.nInt, "Ia_E", "int")
        self.R_E = addpool(self, self.nInt, "R_E", "int")  # Renshaw cells
        self.Ia_F = addpool(self, self.nInt, "Ia_F", "int")
        self.R_F = addpool(self, self.nInt, "R_F", "int")  # Renshaw cells

        '''BS'''
        # periodic stimulation
        # self.E_bs_gids, self.F_bs_gids = add_bs_geners(bs_fr)

        # self.E_bs_gids = sum(pc.py_allgather(self.E_bs_gids), [])
        # self.F_bs_gids = sum(pc.py_allgather(self.F_bs_gids), [])
        # ''' BS '''
        # for E_bs_gid in self.E_bs_gids:
        #     self.genconnect(E_bs_gid, self.muscle_E, 0.5, 1)
        #
        # for F_bs_gid in self.F_bs_gids:
        #     self.genconnect(F_bs_gid, self.muscle_F, 0.5, 1)


        self.E_ia_gids, self.F_ia_gids = self.add_ia_geners()

        for E_ia_gids in self.E_ia_gids:
            genconnect(self, E_ia_gids, self.Ia_aff_E, 0.01, 1, False, 20)

        for F_ia_gids in self.F_ia_gids:
            genconnect(self, F_ia_gids, self.Ia_aff_F, 0.01, 1, False, 30)

        # # '''muscle afferents generators'''
        # self.Iagener_E = self.addIagener(self.muscle_E, self.muscle_F, 10, weight=3)
        # self.Iagener_F = self.addIagener(self.muscle_F, self.muscle_E, one_step_time, weight=3)
        #
        # # # '''Create connectcells'''
        # self.genconnect(self.Iagener_E, self.Ia_aff_E, 5.5, 1, False, 20)
        # self.genconnect(self.Iagener_F, self.Ia_aff_F, 5.5, 1, False, 30)

        # connectcells(self, self.muscle_E, self.Ia_aff_E, 3.5, 1, 10, False)
        # connectcells(self, self.muscle_F, self.Ia_aff_F, 3.5, 1, 10, False)

        '''cutaneous inputs'''
        cfr = 90
        c_int = 1000 / cfr

        '''cutaneous inputs generators'''
        for layer in range(CV_number):
            self.dict_C[layer] = []
            for i in range(step_number):
                self.dict_C[layer].append(
                    addgener(self,
                        10 + speed * layer + i * (speed * CV_number + CV_0_len + one_step_time) + 7 - layer * 12, cfr,
                        True, int((one_step_time / CV_number) * 0.15), cv=True))
        #
        # '''Generators'''
        # '''TODO: need it?'''
        # for i in range(step_number):
        #     self.C_0.append(
        #         self.addgener(25 + speed * 6 + i * (speed * 6 + CV_0_len), cfr, int(CV_0_len / c_int), False))
        #
        # '''TODO: need it?'''
        for layer in range(CV_number):
            self.C_1.append(self.dict_CV_1[layer])
        self.C_1 = sum(self.C_1, [])

        # ''' BS '''
        # for E_bs_gid in self.E_bs_gids:
        #     self.genconnect(E_bs_gid, self.BS_aff_E, 3.5, 3)
        #
        # for F_bs_gid in self.F_bs_gids:
        #     self.genconnect(F_bs_gid, self.BS_aff_F, 3.5, 3)

        # connectcells(self, self.BS_aff_F, self.V3F, 1.5, 3)
        '''STDP synapse'''
        # connectcells(self, self.BS_aff_F, self.RG_F, 0.1, 3, stdptype=False)
        # connectcells(self, self.BS_aff_E, self.RG_E, 0.1, 3, stdptype=False)

        connectcells(self, self.Ia_aff_E, self.RG_E, weight=1.3, delay=3, stdptype=True)
        connectcells(self, self.Ia_aff_F, self.RG_F, weight=1.3, delay=3, stdptype=True)

        # '''cutaneous inputs'''
        for layer in range(CV_number):
            connectcells(self, self.dict_C[layer], self.dict_CV_1[layer], 0.15 * k * speed, 2)
            connectcells(self, self.dict_CV_1[layer], self.dict_RG_E[layer], 0.0035 * k * speed, 3)

        # '''Ia2motor'''
        connectcells(self, self.Ia_aff_E, self.mns_E, 1.55, 2)
        connectcells(self, self.Ia_aff_F, self.mns_F, 1.55, 2)

        for layer in range(CV_number):
            '''Internal to RG topology'''
            self.connectinsidenucleus(self.dict_RG_F[layer])
            self.connectinsidenucleus(self.dict_RG_E[layer])

            '''RG2Motor'''
            connectcells(self, self.dict_RG_E[layer], self.mns_E, 2.75, 3)
            connectcells(self, self.dict_RG_F[layer], self.mns_F, 2.75, 3)
            #
            connectcells(self, self.dict_RG_E[layer], self.InE, 2.75, 3)
            connectcells(self, self.dict_RG_F[layer], self.InF, 2.75, 3)

            connectcells(self, self.dict_RG_F[layer], self.V3F, 1.5, 3)

        '''motor2muscles'''
        connectcells(self, self.mns_E, self.muscle_E, 10, 2, inhtype=False, N=45, sect="muscle")
        connectcells(self, self.mns_F, self.muscle_F, 10, 2, inhtype=False, N=45, sect="muscle")

        # '''Ia2RG, RG2Motor'''
        connectcells(self, self.InE, self.RG_F, 0.5, 1, inhtype=True)
        connectcells(self, self.InF, self.RG_E, 0.8, 1, inhtype=True)

        connectcells(self, self.In1, self.RG_F, 0.5, 1, inhtype=True)

        connectcells(self, self.Ia_aff_E, self.Ia_E, 0.08, 1, inhtype=False)
        connectcells(self, self.Ia_aff_F, self.Ia_F, 0.08, 1, inhtype=False)

        connectcells(self, self.mns_E, self.R_E, 0.015, 1, inhtype=False)
        connectcells(self, self.mns_F, self.R_F, 0.015, 1, inhtype=False)

        connectcells(self, self.R_E, self.mns_E, 0.015, 1, inhtype=True)
        connectcells(self, self.R_F, self.mns_F, 0.015, 1, inhtype=True)

        connectcells(self, self.R_E, self.Ia_E, 0.001, 1, inhtype=True)
        connectcells(self, self.R_F, self.Ia_F, 0.001, 1, inhtype=True)
        #
        connectcells(self, self.Ia_E, self.mns_F, 0.08, 1, inhtype=True)
        connectcells(self, self.Ia_F, self.mns_E, 0.08, 1, inhtype=True)

        connectcells(self, self.RG_F, self.V2a, 0.75, 3)
        connectcells(self, self.RG_F, self.V0d, 0.75, 3)
        connectcells(self, self.V2a, self.V0v, 1.2, 3)

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
                    stim.number = int(one_step_time / stim.interval)

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
                    stim.number = int(one_step_time / stim.interval)
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

    def add_ia_geners(self):
        E_ia_gids = []
        F_ia_gids = []
        for step in range(step_number):
            # E_ia_gids.append(self.addIagener(self.muscle_E, self.muscle_F, 10, weight=5))
            # F_ia_gids.append(self.addIagener(self.muscle_F, self.muscle_E, one_step_time, weight=8))
            E_ia_gids.append(self.addIagener(self.muscle_E, self.muscle_F, 15 + one_step_time * 2 * step, weight=0.1))
            F_ia_gids.append(
                self.addIagener(self.muscle_F, self.muscle_E, 15 + one_step_time * (1 + 2 * step), weight=0.1))
        return E_ia_gids, F_ia_gids