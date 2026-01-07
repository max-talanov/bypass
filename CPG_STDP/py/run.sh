#!/bin/bash -l
#SBATCH --cpus-per-task=1
#SBATCH --job-name=Neuron_calc
#SBATCH --output=Neuron_calculation.slurmout
#SBATCH --error=Neuron_calculation.slurmerr
#SBATCH --ntasks=50
#SBATCH --cpus-per-task=1
echo "NTASKS=$SLURM_NTASKS  CPUS_PER_TASK=$SLURM_CPUS_PER_TASK  MEM=$SLURM_MEM_PER_NODE"

srun nrniv -mpi -python main_cpg.py