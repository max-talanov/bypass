from neuron import h, gui
import random

import random


class interneuron(object):
    '''
    Interneuron class with parameters:
      delay: bool
        Does it have 5ht receptors?
        -Yes: True
        -No: False
      soma: NEURON Section (creates by topol())
      dend: NEURON Section (creates by topol())
      axon: NEURON Section (creates by topol())
      synlistinh: list (creates by synapses())
        list of inhibitory synapses
      synlistex: list (creates by synapses())
        list of excitatory synapses
      synlistees: list (creates by synapses())
        list of excitatory synapses for connection with generators
      x, y, z: int
        3D coordinates (isn't used)
      diffs: list
        list of diffusion mechanisms (NEURON staff)
      recs: list
        list of receptors mechanisms (NEURON staff)
    '''

    def __init__(self, serotonin_mode=False, bursting_mode=False):
        self.all = None
        self.dend = None
        self.axon = None
        self.soma = None
        self.serotonin = serotonin_mode
        self.bursting = bursting_mode
        self.diffs = []
        self.recs = []
        self.topol()
        self.subsets()
        self.geom()
        # self.geom_nseg()
        self.biophys()
        self.synlistinh = []
        self.synlistex = []
        self.synlistees = []
        '''STDP'''
        self.synlistexstdp = []
        self.synlistinhstdp = []
        self.synapses()
        self.x = self.y = self.z = 0.

        def __del__(self):
            # print 'delete ', self
            pass

    def topol(self):
        '''
        Creates sections soma, dend, axon and connects them
        if it's delay creates section dend[]: array
        '''
        self.soma = h.Section(name='soma', cell=self)
        self.axon = h.Section(name='axon', cell=self)
        self.dend = [h.Section(name='dend[%d]' % i) for i in range(random.randint(5, 10))]
        for sec in self.dend:
            sec.connect(self.soma(0.5))
        self.axon.connect(self.soma(1))

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
        self.soma.L = self.soma.diam = random.randint(5, 15)  # microns
        self.axon.L = 150  # microns
        self.axon.diam = 1  # microns
        for sec in self.dend:
            sec.L = 200  # microns
            sec.diam = random.gauss(1, 0.1)  # microns

    def geom_nseg(self):
        '''
        Calculates numder of segments in section
        '''
        for sec in self.all:
            sec.nseg = int((sec.L / (0.1 * h.lambda_f(100)) + .9) / 2.) * 2 + 1

    def biophys(self):
        '''
        Adds channels and their parameters
        if delay is True, adds 5ht receptors
        if bursting is True, adds bursting to soma
        '''
        for sec in self.all:
            sec.cm = random.gauss(1, 0.01)  # cm uf/cm2 - membrane capacitance

        self.soma.Ra = 100  # Ra ohm cm - membrane resistance
        self.soma.insert('fastchannels')
        self.soma.gnabar_fastchannels = 0.3
        self.soma.gkbar_fastchannels = 0.06
        self.soma.gl_fastchannels = 0.002
        self.soma.el_fastchannels = -60
        self.soma.insert('extracellular')  # adds extracellular mechanism for recording extracellular potential
        if self.bursting:
            # Bursting properties of RG-F0 and RG-FE ph A4 interneurons were provided by INaP
            # add slow NaP channels
            # TODO g_NaP = 0.75(±0.0375) mS/cm2
            self.soma.insert('nap')
            self.soma.gbar_nap = 3.0e-3
        # else:
        #     self.soma.insert('nap')
        #     self.soma.gbar_nap = 1.0e-3

        for sec in self.dend:
            sec.Ra = 100  # Ra ohm cm - membrane resistance

        for sec in self.dend:
            if self.serotonin:
                sec.insert('fastchannels')
                sec.gnabar_fastchannels = 0.35
                sec.gkbar_fastchannels = 0.09
                sec.gl_fastchannels = 0.001
                self.add_5HTreceptors(sec, 10, 5)
            else:
                sec.insert('pas')
                sec.g_pas = 0.0002
                sec.e_pas = -70

        if self.serotonin:
            self.add_5HTreceptors(self.soma, 10, 5)

        self.axon.Ra = 50
        self.axon.insert('hh')

    def add_5HTreceptors(self, compartment, time, g):
        '''
        Adds 5HT receptors
        Parameters
        ----------
        compartment: section of NEURON cell
        part of neuron
        x: int
        x - coordinate of serotonin application
        time: int (ms)
        time of serotonin application
        g: float
        receptor conductance
        '''
        diff = h.slow_5HT(compartment(0.5))
        diff.h = random.uniform(10, 2500)
        diff.tx1 = time + 0 + (diff.h / 50) * 10  # 00
        diff.c0cleft = 3
        diff.a = 0.1
        rec = h.r5ht3a(compartment(0.5))
        rec.gmax = g
        h.setpointer(diff._ref_serotonin, 'serotonin', rec)
        self.diffs.append(diff)
        self.recs.append(rec)

    def position(self, x, y, z):
        '''
        NEURON staff
        Adds 3D position
        '''
        self.soma.push()
        for i in range(h.n3d()):
            h.pt3dchange(i, x - self.x + h.x3d(i), y - self.y + h.y3d(i), z - self.z + h.z3d(i), h.diam3d(i))
        self.x = x
        self.y = y
        self.z = z
        h.pop_section()

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
        nc = h.NetCon(self.axon(1)._ref_v, target, sec=self.axon)
        nc.threshold = -20
        return nc

    def synapses(self):
        '''
        Adds static and stdp synapses
        '''
        for sec in self.dend:
            for i in range(50):
                '''Somatic'''
                s = h.ExpSyn(self.soma(0.5))  # Excitatory
                s.tau = 0.8
                s.e = 50
                self.synlistex.append(s)
                s = h.Exp2Syn(self.soma(0.5))  # Inhibitory
                s.tau1 = 0.5
                s.tau2 = 2.8
                s.e = -70
                self.synlistinh.append(s)
                '''Dendritic'''
                s = h.ExpSyn(sec(0.5))  # Excitatory
                s.tau = 0.8
                s.e = 50
                self.synlistex.append(s)
                s = h.Exp2Syn(sec(0.5))  # Inhibitory
                s.tau1 = 0.7
                s.tau2 = 2.8
                s.e = -70
                self.synlistinh.append(s)

                '''STDP'''
                '''Somatic'''
                s = h.ExpSyn(self.soma(0.5))  # Excitatory
                s.tau = 1.3
                s.e = 55
                self.synlistexstdp.append(s)
                s = h.Exp2Syn(self.soma(0.5))  # Inhibitory
                s.tau1 = 0.5
                s.tau2 = 2.8
                s.e = -70
                self.synlistinhstdp.append(s)
                '''Dendritic'''
                s = h.ExpSyn(sec(0.5))  # Excitatory
                s.tau = 1.3
                s.e = 55
                self.synlistexstdp.append(s)
                s = h.Exp2Syn(sec(0.8))  # Inhibitory
                s.tau1 = 0.5
                s.tau2 = 2.8
                s.e = -70
                self.synlistinhstdp.append(s)


def is_art(self):
    return 0
