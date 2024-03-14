import numpy as np
from neuron import h
from neuron.units import ms, mV
import h5py as hdf5

from interneuron import interneuron
from motoneuron import motoneuron
from bioaffrat import bioaffrat
from muscle import muscle

import random

h.load_file('stdrun.hoc')

pc = h.ParallelContext()

class BallAndStick:
    def __init__(self, gid):
        self._gid = gid
        self._setup_morphology()
        self._setup_biophysics()
    def _setup_morphology(self):
        self.soma = h.Section(name='soma', cell=self)
        self.dend = h.Section(name='dend', cell=self)
        self.all = [self.soma, self.dend]
        self.dend.connect(self.soma)
        self.soma.L = self.soma.diam = 12.6157
        self.dend.L = 200
        self.dend.diam = 1
    def _setup_biophysics(self):
        for sec in self.all:
            sec.Ra = 100    # Axial resistance in Ohm * cm
            sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
        self.soma.insert('hh')                                          
        for seg in self.soma:
            seg.hh.gnabar = 0.12  # Sodium conductance in S/cm2
            seg.hh.gkbar = 0.036  # Potassium conductance in S/cm2
            seg.hh.gl = 0.0003    # Leak conductance in S/cm2
            seg.hh.el = -54.3     # Reversal potential in mV
        # Insert passive current in the dendrite                       # <-- NEW
        self.dend.insert('pas')                                        # <-- NEW
        for seg in self.dend:                                          # <-- NEW
            seg.pas.g = 0.001  # Passive conductance in S/cm2          # <-- NEW
            seg.pas.e = -65    # Leak reversal potential mV            # <-- NEW
            
        # NEW: the synapse
        self.syn = h.ExpSyn(self.dend(0.5))
        self.syn.tau = 2 * ms 
    def __repr__(self):
        return 'BallAndStick[{}]'.format(self._gid)

my_cell = BallAndStick(0)
#my_cell.soma.insert(h.STDP(0, sec=h.Section()))
another_cell = BallAndStick(1)
#another_cell.syn.insert(h.STDP(0, sec=h.Segment()))

nc = h.NetCon(my_cell.soma(0.5)._ref_v, another_cell.syn, sec=my_cell.soma)


netstim = h.NetStim()
netstim.number = 1
netstim.start = 9
nc1 = h.NetCon(netstim, my_cell.syn)
nc1.weight[0] = 1

dummy = h.Section()
stdpmech = h.STDP(0, sec=my_cell.soma)

h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
stdpmech.hebbRL()

presyn = pc.gid_connect(0, stdpmech)
presyn.delay = 1
presyn.weight[0] = 1

postsyn = pc.gid_connect(1, stdpmech)
postsyn.delay = 0.5
postsyn.weight[0] = -1


stim = h.IClamp(my_cell.soma(0.5))
stim1 = h.IClamp(another_cell.soma(0.5))


stim.delay = 1
stim.dur = 250
#stim.interval = int(50)
stim.amp = 0.7

stim1.delay = 1
stim1.dur = 10
stim1.amp = 0.6

soma_v = h.Vector().record(my_cell.soma(0.5)._ref_v)
another_v = h.Vector().record(another_cell.soma(0.5)._ref_v)
t = h.Vector().record(h._ref_t)
#y = h.Vector(np.sin(np.array(list(t))))
#y.play(nc._ref_weight[0], t, True)
#nc_w = h.Vector().record(nc._ref_weight[0])
#h.setpointer(nc._ref_weight[0], 'synweight', stdpmech)
nc_w = h.Vector().record(nc._ref_weight[0])

h.finitialize(-65 * mV)
h.continuerun(500 * ms)

import matplotlib.pyplot as plt

#f = plt.figure(x_axis_label='t (ms)', y_axis_label='v (mV)')
f1 = plt.figure()
plt.plot(t, list(nc_w), "r*")
plt.savefig("fig.png")

f2 = plt.figure()
plt.plot(t, list(soma_v))
plt.plot(t, list(another_v), "r")
plt.savefig("fig2.png")
import pprint
pp = pprint.PrettyPrinter()
#pp.pprint(dir(nc._ref_weight[0]))