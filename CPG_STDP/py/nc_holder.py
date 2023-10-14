from neuron import h
import numpy as np
from get_weights import time_sim

class NC_holder:
    def __init__(self):
        self.excitatory_netcons = None
        self.inhibitory_netcons = None

    def add_excitatory_netcons(self, obj):
        self.excitatory_netcons = obj

    def add_inhibitory_netcons(self, obj):
        self.inhibitory_netcons = obj

    def record_excitatory_netcons(self):
        weight_vec = []
        for netcon in self.excitatory_netcons:
            vec = h.Vector(np.zeros(int(time_sim / 0.025 + 1), dtype=np.float32))
            vec.record(netcon._ref_weight[0])
            weight_vec.append(vec)
        return weight_vec

    def record_inhibitory_netcons(self):
        weight_vec = []
        for netcon in self.inhibitory_netcons:
            vec = h.Vector(np.zeros(int(time_sim / 0.025 + 1), dtype=np.float32))
            vec.record(netcon._ref_weight[0])
            weight_vec.append(vec)
        return weight_vec

    def get_weights(self, type):
        exoutfile = open("exweights_AAAAAAA.txt", 'w')
        inhoutfile = open("inhweights_AAAAAAA.txt", 'w')
        for i in self.excitatory_netcons:
            exoutfile.write(str(float(i.weight[0])) + '\n')

        for i in self.inhibitory_netcons:
            inhoutfile.write(str(float(i.weight[0])) + '\n')

        exoutfile.close()
        inhoutfile.close()
