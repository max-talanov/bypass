#!/bin/bash -l
#SBATCH --job-name=Neuron_calc
#SBATCH --output=Neuron_calculation.slurmout
#SBATCH --error=Neuron_calculation.slurmerr
#SBATCH --nodes=1
#SBATCH --ntasks=2
#SBATCH --priority=1000
#SBATCH --nice=100

#echo "activate env"
srun -python check_neuron.py

