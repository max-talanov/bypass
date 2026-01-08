from neuron import h
import os
import numpy as np
import h5py as hdf5
import logging
import random
import re

# -----------------------------------------------------------------------------
# MPI / ParallelContext
# -----------------------------------------------------------------------------
# IMPORTANT: Do not silently fall back to (rank=0, nhost=1) in MPI runs.
# That leads to mismatched gid ownership and errors like:
#   "gid=X has not been set on rank Y".
def check_mpi_status():
    # Always initialize MPI (safe if already initialized)
    # If Slurm requested multiple tasks, MPI must initialize successfully.
    _expected_tasks = int(os.environ.get("SLURM_NTASKS", "1"))

    try:
        h.nrnmpi_init()  # safe even if already initialized
    except Exception as e:
        if _expected_tasks > 1:
            raise RuntimeError(f"MPI init failed but SLURM_NTASKS={_expected_tasks}") from e
        # Serial run: OK to continue

    pc = h.ParallelContext()
    rank = int(pc.id())
    nhost = int(pc.nhost())

    if rank == 0:
        print("MPI Status:")
        print(f"  Number of hosts: {nhost}")

    # No silent fallback: if nhost==1, you're not running MPI the way you think
    return pc, rank, nhost

pc, rank, nhost = check_mpi_status()

# -----------------------------------------------------------------------------
# Logging (rank-safe)
# -----------------------------------------------------------------------------
# Shared file logging from 50 ranks on GPFS/Lustre will kill performance and can
# also trigger strange failures. Use one file per rank.
LOG_LEVEL = os.environ.get("CPG_LOGLEVEL", "WARNING").upper()
_level = getattr(logging, LOG_LEVEL, logging.WARNING)
os.makedirs("logs", exist_ok=True)
logging.basicConfig(
    filename=f"logs/logs_rank{rank:03d}.log",
    filemode="w",
    format="%(asctime)s %(name)s %(levelname)s %(message)s",
    datefmt="%H:%M:%S",
    level=_level,
)

_formatter = logging.Formatter(
    fmt="%(asctime)s %(name)s %(levelname)s %(message)s",
    datefmt="%H:%M:%S",
)

# Dedicated loggers used by utils_cpg.py
logger_addgener = logging.getLogger("addgener")
logger_addgener.propagate = False
logger_genconnect = logging.getLogger("genconnect")
logger_genconnect.propagate = False

if rank == 0:
    h_add = logging.FileHandler(f"logs/addgener_rank{rank:03d}.log", mode="w")
    h_add.setFormatter(_formatter)
    logger_addgener.addHandler(h_add)
    logger_addgener.setLevel(_level)

    h_conn = logging.FileHandler(f"logs/genconnect_rank{rank:03d}.log", mode="w")
    h_conn.setFormatter(_formatter)
    logger_genconnect.addHandler(h_conn)
    logger_genconnect.setLevel(_level)
else:
    # Avoid emitting from non-zero ranks
    logger_addgener.addHandler(logging.NullHandler())
    logger_genconnect.addHandler(logging.NullHandler())

# -----------------------------------------------------------------------------
# NEURON standard runtime (headless-friendly)
# -----------------------------------------------------------------------------
# Do NOT load GUI files on compute nodes.
h.load_file("stdrun.hoc")

# -----------------------------------------------------------------------------
# Simulation parameters (keep your original values here)
# -----------------------------------------------------------------------------
os.makedirs("res_stdp", exist_ok=True)
file_name = 'res_stdp'

w_rec_dt = 10  # recording step in ms
rec_dt = 0.1  # recording step in ms
N = 5         # set to 50 for production
speed = 100
bs_fr = 100
versions = 1
CV_number = 6
k = 0.017
CV_0_len = 12
extra_layers = 0

# Steps
step_number = 1  # set to 120 for your goal

# Derived timings
one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
# Your original formula had *2 and +30; keeping it as-is
time_sim = (one_step_time * step_number + 30) * 2

# Indices used in main script when iterating groups (tuple: (gids, name))
k_nrns = 0
k_name = 1

# NOTE: GIDs are generated in utils_cpg.get_gid(); that module keeps its own
# counter. Do not rely on this variable elsewhere.
