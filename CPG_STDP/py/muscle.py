from neuron import h
import random

h.load_file('stdlib.hoc')  # for h.lambda_f


class muscle(object):
    '''
    muscle class with parameters:
      soma: NEURON Section (creates by topol())
      dend: NEURON Section (creates by topol())
      synlistinh: list (creates by synapses())
        list of inhibitory synapses
      synlistex: list (creates by synapses())
        list of excitatory synapses
    '''

    def __init__(self, n_synapses=100, nseg=3):
        self.all = None
        self._secs = None
        self.soma = None
        self.muscle_unit = None
        self._n_synapses = n_synapses
        self._nseg = nseg
        self.topol()
        self.subsets()
        self.geom()
        self.geom_nseg()
        self.biophys()
        self.synlistex = []
        self.synlistinh = []
        self.synapses()

    def __del__(self):
        pass

    def topol(self):
        '''
        Creates section
        '''
        self.muscle_unit = h.Section(name='muscle_unit', cell=self)
        self.soma = h.Section(name='soma', cell=self)
        self.muscle_unit.connect(self.soma(0.5))

    def subsets(self):
        '''
        NEURON staff: add only our sections (no global h.allsec() scan).
        '''
        self._secs = [self.muscle_unit, self.soma]
        self.all = h.SectionList()
        for sec in self._secs:
            self.all.append(sec)

    def geom(self):
        '''
        Adds length and diameter to sections
        '''
        self.muscle_unit.L = 3000 #3000  # microns
        self.muscle_unit.diam = 40  # microns
        self.soma.L = 3000  # microns
        self.soma.diam = 40  # microns

    def geom_nseg(self):
        '''
        Calculates numder of segments in section
        '''
        for sec in self._secs:
            sec.nseg = self._nseg  # int((sec.L/(0.1*h.lambda_f(100)) + .9)/2.)*2 + 1

    def biophys(self):
        '''
        Adds channels and their parameters
        '''
        # for sec in self.all:
        #     sec.cm = random.gauss(1, 0.01)  # cm uf/cm2 - membrane capacitance
        # # muscle_unit параметры:
        self.muscle_unit.cm = 3.6
        self.muscle_unit.insert('Ca_conc')
        self.muscle_unit.insert('pas')
        self.muscle_unit.g_pas = 0.004
        self.muscle_unit.e_pas = -70
        self.muscle_unit.Ra = 1.1
        # # каналы и токи
        # self.muscle_unit.insert('cal')  # L-тип кальциевых каналов
        # self.muscle_unit.gcalbar_cal = 0.1
        #
        # self.muscle_unit.insert('na14a')  # натриевый канал Nav1.4
        # self.muscle_unit.gbar_na14a = 0.75
        # Вставляем простые каналы в muscle_unit:
        self.muscle_unit.insert('fastchannels')
        self.muscle_unit.gnabar_fastchannels = 0.05
        self.muscle_unit.gkbar_fastchannels = 0.01

        # CaSP и fHill в muscle_unit:
        self.muscle_unit.insert('CaSP')
        self.muscle_unit.insert('fHill')
        self.muscle_unit.insert('xm')
        # self.muscle_unit.insert('extracellular')

        # self.muscle_unit.ena = 50
        # self.muscle_unit.ek = -77

        # soma параметры:
        self.soma.cm = 3.6
        self.soma.Ra = 1.1
        self.soma.insert('Ca_conc')
        self.soma.insert('fastchannels')
        self.soma.insert('kir')
        self.soma.insert('na14a')
        self.soma.insert('cal')
        self.soma.insert('K_No')
        self.soma.insert('cac1')

        self.soma.gmax_cac1 = 0.005
        self.soma.gbar_na14a = 0.75
        self.soma.gkbar_kir = 0.01
        self.soma.gnabar_fastchannels = 0.55
        self.soma.gkbar_fastchannels = 0.015
        self.soma.gl_fastchannels = 0.01
        self.soma.el_fastchannels = -70
        self.soma.gkmax_K_No = 0.02
        self.soma.gcalbar_cal = 0.1

        self.soma.ena = 55
        self.soma.ek = -80

        self.soma.insert('extracellular')

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
        nc = h.NetCon(self.muscle_unit(0.5)._ref_v, target, sec=self.muscle_unit)
        nc.threshold = 10
        return nc

    def synapses(self):
        '''
        Adds synapses
        '''

        loc = self.muscle_unit(0.5)
        ExpSyn = h.ExpSyn
        Exp2Syn = h.Exp2Syn
        syn_ex_append = self.synlistex.append
        syn_in_append = self.synlistinh.append
        for i in range(self._n_synapses):
            s = ExpSyn(loc)  # Exsitatory
            s.tau = 0.2
            s.e = 55
            syn_ex_append(s)
            s = Exp2Syn(loc)  # Inhibitory
            s.tau1 = 0.6
            s.tau2 = 2.2
            s.e = -70
            syn_in_append(s)
            # s = h.ExpSyn(self.soma(0.5))  # Exsitatory
            # s.tau = 0.2
            # s.e = 55
            # self.synlistex.append(s)
            # s = h.Exp2Syn(self.soma(0.5))  # Inhibitory
            # s.tau1 = 0.6
            # s.tau2 = 2.2
            # s.e = -70
            # self.synlistinh.append(s)

        # for i in range(100):
        #     syn = h.MGISyn(self.muscle_unit(0.5))
        #     syn.mg_increase = 0.05  # или подберите
        #     h.setpointer(self.muscle_unit(0.5)._ref_mgi, 'mgi', syn)
        #     self.synlistex.append(syn)

    def is_art(self):
        return 0
