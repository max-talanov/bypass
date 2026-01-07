#!/bin/bash -l
#SBATCH --nodes=1
#SBATCH --ntasks=50
#SBATCH --cpus-per-task=1
#SBATCH --job-name=Neuron_calc
#SBATCH --output=Neuron_calculation.slurmout
#SBATCH --error=Neuron_calculation.slurmerr
# Use srun to launch MPI processes.
# SLURM will automatically use --ntasks=50 from SBATCH directives.
srun python3 main_cpg.py
