import numpy as np
from neuron import h
from neuron.units import ms, mV
import h5py as hdf5
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')
from interneuron import interneuron
cell_1 = interneuron()
cell_2 = interneuron()

dummy = h.Section()
stdpmech = h.STDP(0, sec=dummy)

'''netstim = h.NetStim()
netstim.number = 200
netstim.interval = 10
netstim.start = 1'''

stim = h.IClamp(cell_1.soma(0.5))
stim.delay = 1
stim.dur = 59800
stim.amp = 0.5

'''
stim1 = h.IClamp(cell_2.soma(0.5))
stim1.delay = 2
stim1.dur = 59900
stim1.amp = 0.2
'''

threshold = 10
delay = 1
#print(cell_1.synlistex[0])
syn1 = h.ExpSyn(cell_1.soma(0.5))
syn = h.ExpSyn(cell_2.soma(0.5))
#nc1 = h.NetCon(netstim, syn1)
#print(syn)
'''singlesyn = h.NetCon(cell_1.synlistex[0], cell_2.synlistex[0], threshold, delay, 0.5)
presyn = h.NetCon(cell_1.synlistex[0], stdpmech, threshold, delay, 1)
pstsyn = h.NetCon(cell_2.synlistex[0], stdpmech, threshold, delay, -1)'''
singlesyn = h.NetCon(syn, syn1, threshold, delay, 1)
presyn = h.NetCon(syn1, stdpmech, threshold, delay, 1)
pstsyn = h.NetCon(syn, stdpmech, threshold, delay, -1)
h.setpointer(singlesyn._ref_weight[0],'synweight',stdpmech)

x = h.Vector().record(h._ref_t)
syn_w = h.Vector().record(singlesyn._ref_weight[0])
V_1 = h.Vector().record(cell_1.soma(0.5)._ref_v)
V_2 = h.Vector().record(cell_2.soma(0.5)._ref_v)

h.finitialize(-65 * mV)
h.continuerun(60000 * ms)

import matplotlib.pyplot as plt

f1 = plt.figure()
plt.plot(x, list(syn_w))
#plt.xlim([0,1])
plt.savefig("fig.png")

f2 = plt.figure()
plt.plot(x, list(V_1))
plt.plot(x, list(V_2), "r")
plt.savefig("fig2.png")
print('finished')
## Create cells
'''
dummy = h.Section() # Create a dummy section to put the point processes in
ncells = 2
cells = []
for c in range(ncells): cells.append(h.IntFire4(0,sec=dummy)) # Create the cells
stdpmech = h.STDP(0, sec=dummy)
h.execute('any hoc statement')

## Create synapses
threshold = 10 # Set voltage threshold
delay = 1 # Set connection delay
singlesyn = h.NetCon(cells[0],cells[1], threshold, delay, 0.5) # Create a connection between the cells
stdpmech = h.STDP(0,sec=dummy) # Create the STDP mechanism
presyn = h.NetCon(cells[0],stdpmech, threshold, delay, 1) # Feed presynaptic spikes to the STDP mechanism -- must have weight >0
pstsyn = h.NetCon(cells[1],stdpmech, threshold, delay, -1) # Feed postsynaptic spikes to the STDP mechanism -- must have weight <0
h.setpointer(singlesyn._ref_weight[0],'synweight',stdpmech) # Point the STDP mechanism to the connection weight
'''