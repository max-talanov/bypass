#!/bin/bash -l
#SBATCH --job-name=Neuron_calc
#SBATCH --output=Neuron_comp.slurmout
#SBATCH --error=Neuron_comp.slurmerr
#SBATCH --nodes=1
#SBATCH --ntasks=50
#SBATCH --ntasks-per-node=50
#SBATCH --cpus-per-task=1

# Strongly recommended on HPC: ensure UTF-8 output + unbuffered python prints
export LANG=${LANG:-C.UTF-8}
export LC_ALL=${LC_ALL:-C.UTF-8}
export PYTHONIOENCODING=utf-8
export PYTHONUNBUFFERED=1

# Headless NEURON + MPI
#srun nrniv -mpi -nogui -python main_cpg.py
srun --mpi=pmix nrniv -mpi -nogui -python main_cpg.py