from neuron import h
import os
import numpy as np
import h5py as hdf5
import logging
import random
import re

h.load_file("stdgui.hoc")
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')


# paralleling NEURON stuff
def check_mpi_status():
    try:
        pc = h.ParallelContext()
        rank = int(pc.id())
        nhost = int(pc.nhost())
        return pc, rank, nhost
    except Exception as e:
        pc = h.ParallelContext()
        return pc, 0, 1


# Initialize MPI first
pc, rank, nhost = check_mpi_status()

# Results directory
file_name = 'res_alina_50_stdp'
os.makedirs(file_name, exist_ok=True)

# Logging setup
log_format = '%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s'
log_datefmt = '%H:%M:%S'
formatter = logging.Formatter(fmt=log_format, datefmt=log_datefmt)

root_logger = logging.getLogger()
root_logger.setLevel(logging.DEBUG)

# remove old handlers to avoid duplicate logs
for handler in root_logger.handlers[:]:
    root_logger.removeHandler(handler)

main_log_path = f'./{file_name}/simulation_rank{rank}.log'

file_handler = logging.FileHandler(main_log_path, mode='w')
file_handler.setFormatter(formatter)
root_logger.addHandler(file_handler)

stream_handler = logging.StreamHandler()
stream_handler.setFormatter(formatter)
root_logger.addHandler(stream_handler)

logging.info("Logging initialized")
logging.info(f"MPI Status: rank={rank}, nhost={nhost}")
logging.info(f"Main log path: {main_log_path}")

# --- отдельные логгеры для addgener и genconnect ---

logger_addgener = logging.getLogger("addgener")
logger_addgener.setLevel(logging.DEBUG)
logger_addgener.propagate = False

for handler in logger_addgener.handlers[:]:
    logger_addgener.removeHandler(handler)

addgener_log_path = f'./{file_name}/addgener_rank{rank}.log'
handler_add = logging.FileHandler(addgener_log_path, mode="w")
handler_add.setFormatter(formatter)
logger_addgener.addHandler(handler_add)

logger_genconnect = logging.getLogger("genconnect")
logger_genconnect.setLevel(logging.DEBUG)
logger_genconnect.propagate = False

for handler in logger_genconnect.handlers[:]:
    logger_genconnect.removeHandler(handler)

genconnect_log_path = f'./{file_name}/genconnect_rank{rank}.log'
handler_conn = logging.FileHandler(genconnect_log_path, mode="w")
handler_conn.setFormatter(formatter)
logger_genconnect.addHandler(handler_conn)

logging.info(f"addgener log path: {addgener_log_path}")
logging.info(f"genconnect log path: {genconnect_log_path}")

N = 5
speed = 100
bs_fr = 100  # 40 # frequency of brainstem inputs
versions = 1
CV_number = 6
k = 0.017  # CV weights multiplier to take into account air and toe stepping
CV_0_len = 12  # 125 # Duration of the CV generator with no sensory inputs
extra_layers = 0  # 1 + layers

step_number = 6  # quick test #50 # 70 max that works # 100 weights are not recorded # 50 #15 #10

one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = (one_step_time * step_number + 30) * 2

k_nrns = 0
k_name = 1

global_gid = 0
