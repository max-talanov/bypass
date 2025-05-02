from neuron import h

h.load_file('stdlib.hoc')  # for h.lambda_f

import random
from axon import Axon


class bioaffrat(Axon):
    '''
    Afferent with bio-axon class with parameters:
      soma: NEURON Section (creates by topol())
      dend: NEURON Section (creates by topol())
      axon parameters from: https://senselab.med.yale.edu/ModelDB/ShowModel.cshtml?model=3810&file=/MRGaxon/MRGaxon.hoc#tabs-2
      synlistinh: list (creates by synapses())
        list of inhibitory synapses
      synlistex: list (creates by synapses())
        list of excitatory synapses
      synlistees: list (creates by synapses())
        list of excitatory synapses for connection with generators
    '''
    # from axon import make_axon, topol_axon, geom_axon, biophys_axon

    def __init__(self, neuron_type="extensor"):
        self.nc = None
        self.soma = None
        self.all = None
        self.nu = random.randint(8, 11)
        super().__init__(self.nu)
        self.neuron_type = neuron_type
        self.topol()
        self.subsets()
        self.geom()
        self.biophys()
        self.synlistees = []
        self.synlistex = []
        self.synlistinh = []
        self.synapses()

    def __del__(self):
        # print 'delete ', self
        pass

    def topol(self):
        '''
        Creates sections soma, dend, axon and connects them
        '''
        self.soma = h.Section(name='soma', cell=self)
        # self.axon = h.Section(name='axon', cell=self)
        self.node[0].connect(self.soma(1))
        self.node[-1].connect(self.soma(1))
        # self.axon.connect(self.soma(1))

        # self.basic_shape()

    def subsets(self):
        '''
        NEURON staff
        adds sections in NEURON SectionList
        '''
        self.all = h.SectionList()
        for sec in h.allsec():
            self.all.append(sec=sec)

    def geom(self):
        '''
        Adds length and diameter to sections
        '''
        self.soma.L = self.soma.diam = random.uniform(15, 20)  # microns
        # self.axon.L = 150  # microns
        # self.axon.diam = 1  # microns
        h.define_shape()

    def biophys(self):
        '''
        Adds channels and their parameters
        '''
        self.soma.insert('hh')
        self.soma.gnabar_hh = 0.65
        self.soma.gkbar_hh = 0.15
        self.soma.gl_hh = 0.0001
        self.soma.el_hh = -65
        self.soma.Ra = 150
        self.soma.cm = 1
        self.soma.insert('extracellular')

        # self.axon.Ra = 50
        # self.axon.insert('hh')

    def connect2target(self, target):
        '''
        NEURON staff
        Adds presynapses
        Parameters
        ----------
        target: NEURON cell
            target neuron
        Returns
        -------
        nc: NEURON NetCon
            connection between neurons
        '''
        self.nc = h.NetCon(self.node[-1](0.5)._ref_v, target, sec=self.node[-1])
        self.nc.threshold = -20
        return self.nc

        # nc = h.NetCon(self.axon(1)._ref_v, target, sec=self.axon)
        # nc.threshold = -10
        # return nc

    def synapses(self):
        # Ингибирующие (на соме!)
        for i in range(100):
            s = h.Exp2Syn(self.soma(0.5))
            s.tau1 = 0.5
            s.tau2 = 2.8
            s.e = -80
            self.synlistinh.append(s)
        # Then in synapses() method, add logic based on type:
        # if hasattr(self, 'neuron_type') and self.neuron_type == "flexor":
        #     # Flexor-specific parameters
        for i in range(100):
            s = h.ExpSyn(self.soma(0.5))
            s.tau = 0.7
            s.e = 50  # Higher reversal potential for flexors
            self.synlistees.append(s)

            s_extra = h.ExpSyn(self.soma(0.5))
            s_extra.tau = 0.7
            s_extra.e = 50
            self.synlistex.append(s_extra)
        # else:
        #     # Extensor parameters (default)
        #     for i in range(50):
        #         s = h.ExpSyn(self.soma(0.5))
        #         s.tau = 2.0
        #         s.e = 55
        #         self.synlistees.append(s)
        #
        #         s_extra = h.ExpSyn(self.soma(0.5))
        #         s_extra.tau = 2.0
        #         s_extra.e = 55
        #         self.synlistex.append(s_extra)

    def is_art(self):
        return 0
