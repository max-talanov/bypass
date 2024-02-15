import numpy as np
from neuron import h
import h5py as hdf5

from interneuron import interneuron

def connectcells(pre, post, weight, delay = 1, inhtype = False, N = 50, threshold = 10):
    ''' Connects with excitatory synapses
      Parameters
      ----------
      pre: list
          list of presynase neurons gids
      post: list
          list of postsynapse neurons gids
      weight: float
          weight of synapse
          used with Gaussself.Ian distribution
      delay: int
          synaptic delay
          used with Gaussself.Ian distribution
      nsyn: int
          numder of synapses
      inhtype: bool
          is this connection inhibitory?
      N: int
          number of synapses
      stdptype: bool
           is connection stdp?
      threshold: int
            voltage thershold
    '''
    nsyn = random.randint(N-15, N)
    for post_gid in post:
        if pc.gid_exists(post_gid):
            for j in range(nsyn):
                src_gid = random.randint(pre[0], pre[-1])
                target = pc.gid2cell(post_gid)
                if inhtype:
                    syn = target.synlistinhstdp[j]
                    nc = pc.gid_connect(src_gid, syn)
                    nc.delay = delay
                    pc.threshold(src_gid, threshold)
                    """Create STDP synapses"""
                    dummy = h.Section()  # Create a dummy section to put the point processes in
                    stdpmech = h.STDP(0, sec=dummy)  # Create the STDP mechanism
                    # TODO check target, threshold,
                    presyn = pc.gid_connect(src_gid,
                                            stdpmech)  # threshold, delay, 1)  # Feed presynaptic spikes to the STDP mechanism -- must have weight >0
                    presyn.delay = delay
                    presyn.weight = 1
                    pstsyn = pc.gid_connect(post_gid,
                                            stdpmech)  # threshold, delay, -1)  # Feed postsynaptic spikes to the STDP mechanism -- must have weight <0
                    pstsyn.delay = delay
                    pstsyn.weight = -1
                    pc.threshold(post_gid, threshold)
                    h.setpointer(nc._ref_weight[0], 'synweight',
                                 stdpmech)  # Point the STDP mechanism to the connection weight
                    inhstdpnclist.append(nc)
                else:
                    syn = target.synlistex[j]
                    nc = pc.gid_connect(src_gid, syn)
                    nc.delay = delay
                    pc.threshold(src_gid, threshold)
                    """Create STDP synapses"""
                    dummy = h.Section()  # Create a dummy section to put the point processes in
                    stdpmech = h.STDP(0, sec=dummy)  # Create the STDP mechanism
                    # TODO check target, threshold,
                    presyn = pc.gid_connect(src_gid,
                                            stdpmech)  # threshold, delay, 1)  # Feed presynaptic spikes to the STDP mechanism -- must have weight >0
                    presyn.delay = delay
                    presyn.weight[0] = 1
                    pstsyn = pc.gid_connect(post_gid,
                                            stdpmech)  # threshold, delay, -1)  # Feed postsynaptic spikes to the STDP mechanism -- must have weight <0
                    pstsyn.delay = delay
                    pstsyn.weight[0] = -1
                    pc.threshold(post_gid, threshold)
                    h.setpointer(nc._ref_weight[0], 'synweight',
                                 stdpmech)  # Point the STDP mechanism to the connection weight
                    exstdpnclist.append(nc)
                        # nc.weight[0] = random.gauss(weight, weight / 6) # str

                # if mode == 'STR':
                #     nc.weight[0] = 0 # str
                # else:
                nc.weight[0] = random.gauss(weight, weight / 5)
                nc.delay = random.gauss(delay, delay / 5)


neuron1 = interneuron()
neuron2 = interneuron()
dummy = h.Section()
stdpmech = h.STDP(0, dummy)
nc = h.NetCon(neuron1, neuron2, )