from neuron import h
import os
import numpy as np
import h5py as hdf5
import logging
import random
import re

logging.basicConfig(filename='logs_new_new_2.log',
                    filemode='w',
                    format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s',
                    datefmt='%H:%M:%S',
                    level=logging.DEBUG)
logging.info("let's get it started")

h.load_file("stdgui.hoc")
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')

# paralleling NEURON stuff
def check_mpi_status():
    try:
        # h.nrnmpi_init()
        pc = h.ParallelContext()
        rank = int(pc.id())
        nhost = int(pc.nhost())

        print(f"MPI Status:")
        print(f"  Rank: {rank}")
        print(f"  Number of hosts: {nhost}")
        print(f"  MPI initialized: {h.nrnmpi_is_initialized()}")

        return pc, rank, nhost
    except Exception as e:
        print(f"MPI Error: {e}")
        # Fallback to single process
        pc = h.ParallelContext()
        return pc, 0, 1

# Initialize MPI properly
pc, rank, nhost = check_mpi_status()
file_name = 'res_alina_50_stdp'

N = 2
speed = 100
bs_fr = 100  # 40 # frequency of brainstem inputs
versions = 1
CV_number = 6
k = 0.017  # CV weights multiplier to take into account air and toe stepping
CV_0_len = 12  # 125 # Duration of the CV generator with no sensory inputs
extra_layers = 0  # 1 + layers

step_number =  50 #15 #10

one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = one_step_time * step_number + 30

k_nrns = 0
k_name = 1

global_gid = 0
