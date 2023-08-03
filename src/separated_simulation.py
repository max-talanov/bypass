import nest
import nest.raster_plot
import matplotlib.pyplot as plt
import logging
import numpy as np
import pickle
import os
########################
# Flexor implementation
########################

# Functions



def get_V3_rate(phase, lo, mid, hi) -> float:
    if 5 < phase < 9:
        return hi
    elif 4 < phase < 10:
        return mid
    else:
        return lo

def identity_cut_chunk(step, hi, lo):
    ## chunk_number
    chunk_number = [0]
    if step < 2:
        chunk_number = [0]
    elif step < 3:
        chunk_number = [0, 1]
    elif step < 4:
        chunk_number = [1]
    elif step < 6:
        chunk_number = [1, 2]
    elif step < 7:
        chunk_number = [2]
    elif step < 8:
        chunk_number = [2, 3]
    elif step < 10:
        chunk_number = [3]
    return chunk_number, hi

def get_Ia_rate(step, freq_hi, freq_lo):
  if step in [2,3,6,7]: return freq_hi
  else: return freq_lo

def dump_spike_recorder(spike_recorder, name):
    if not os.path.exists('pickle_'):
        os.makedirs('pickle_')

    ts, node_ids = nest.raster_plot._from_memory(spike_recorder)
    if not len(ts):
        raise nest.kernel.NESTError("No events recorded!")
    with open(f'pickle_/{name}_ts.pkl', "wb") as handle:
        pickle.dump(ts, handle)
    with open(f'pickle_/{name}_node_ids.pkl', "wb") as handle:
        pickle.dump(node_ids, handle)

def dump_weight_recorder(weight_recorder, name):
    if not os.path.exists('pickle_'):
        os.makedirs('pickle_')

    senders = weight_recorder.events["senders"]
    targets = weight_recorder.events["targets"]
    weights = weight_recorder.events["weights"]
    times = weight_recorder.events["times"]

    with open(f'pickle_/{name}_senders.pkl', "wb") as handle:
        pickle.dump(senders, handle)
    with open(f'pickle_/{name}_targets.pkl', "wb") as handle:
        pickle.dump(targets, handle)
    with open(f'pickle_/{name}_weights.pkl', "wb") as handle:
        pickle.dump(weights, handle)
    with open(f'pickle_/{name}_times.pkl', "wb") as handle:
        pickle.dump(times, handle)



FORMAT = '%(asctime)s %(message)s'
logging.basicConfig(format=FORMAT, level=logging.INFO)
log = logging.getLogger("Cur")
###############################################################################
# Second, we set the parameters so the ``poisson_generator`` generates 1000
# spikes per second and is active from 100 to 500 ms
rate = 200.0  # generator rate in spikes/s
start = 0.0  # start of simulation relative to trial start, in ms
stop = 1000.0  # end of simulation relative to trial start, in ms

###############################################################################

trial_duration = 10.0  # trial duration, in ms
phase_duration = 100.0
simulation_hill_toe_phases = 4
num_phases = 10
num_steps = 2 #10  # 5  # number of trials to perform

## Commisural projections
v3F_num = 200
v3F_hi = 200.0  # Hz spiking rate
v3F_mid = 100.0
v3F_lo = 50.0  # Hz spiking rate

bs_num = 100

## RG
l_f_rg_num = 200 # number of rhythm generator neurons
rg_I_e = 500
rg_g_L = 10.0
rg_tau_plus = 120.0 # tau_w
rg_E_L = -58.0
rg_lambda = 5.0 # b= 100.0
rg_C_m = 200.0
rg_V_m = -58.0
rg_w_mean = 4.0 # 5.0 # Initial weight #! must be equal to 5
rg_w_std = 0.3
rg_alpha = 2.0
rg_delay = 120


## Ia projections
Ia_fibers_num = 100 # 8 #100
# [20,50,20,50,20]*Hz
Ia_fibers_freq_hi = 50#Hz
Ia_fibers_freq_lo = 10#Hz #20*Hz

## Cutaneous projectons
cut_num = 100
cut_lo = 5.0  # Hz spiking rate
cut_hi = 50.0  # 200.0 # 50.0  # Hz spiking rate
cut_chunk = int(cut_num / simulation_hill_toe_phases)

## Motor neurons
l_f_motor_neurons_num = 200

## synapses
d = 1.0
Je = 100.0 # 20.0
Ke = 20

## STDP parameters
alpha_min = 0.1
alpha_max = 2.
w_min = 0.5
w_max = 100.0
w_mean = 4.0
w_std = 0.3
lambda_mean  = 5.0
lambda_std = 0.3
delay_def = 1.0

###############################################################################
# The network is set up.
nest.ResetKernel()
nest.total_num_virtual_procs = 16

v3F_g_params = {"rate": v3F_lo}
cut_g_params = {"rate": cut_lo}
Ia_g_params = {"rate": Ia_fibers_freq_lo}

## Generators
bs_generator = nest.Create("poisson_generator", bs_num, params=v3F_g_params)

### Extensor
l_e_cut_fiber_generator = nest.Create("poisson_generator", cut_num, params=cut_g_params)

### Flexor
l_f_Ia_fiber_generator = nest.Create("poisson_generator", Ia_fibers_num, params=Ia_g_params)

## Nuclei
f_rg_params = {"I_e": rg_I_e,
                    "g_L" : rg_g_L,
                    "E_L" : rg_E_L,
                    "C_m" :  rg_C_m,
                    "V_m" : rg_V_m}

### BS
bs_neurons = nest.Create("hh_psc_alpha_clopath", bs_num)
l_f_v3F_neurons = nest.Create("hh_psc_alpha_clopath", v3F_num)

### Ia and RG
l_f_Ia_fibers = nest.Create("hh_psc_alpha_clopath", Ia_fibers_num)
l_f_rg_neurons = nest.Create("hh_psc_alpha_clopath", l_f_rg_num,
                             params=f_rg_params
                             )

### Motor neurons
l_f_motor_neurons = nest.Create("hh_psc_alpha_clopath", l_f_motor_neurons_num)


###############################################################################
# The ``spike_recorder`` is created and the handle stored in `sr`.
bs_sr = nest.Create("spike_recorder")
bs_neurons_sr = nest.Create("spike_recorder")
l_f_v3F_neurons_sr = nest.Create("spike_recorder")
l_f_v3F_neurons_wr = nest.Create("weight_recorder")

l_f_Ia_fiber_generator_sr = nest.Create("spike_recorder")
l_f_Ia_fiber_sr = nest.Create("spike_recorder")
l_f_rg_neurons_sr = nest.Create("spike_recorder")

l_f_Ia2rg_neurons_wr = nest.Create("weight_recorder")
l_f_motor_neurons_sr = nest.Create("spike_recorder")

###############################################################################
# The Connect function connects the nodes so spikes from pg are collected by
# the spike_recorder
nest.Connect(bs_generator, bs_sr)
nest.Connect(bs_neurons, bs_neurons_sr)
nest.Connect(l_f_v3F_neurons, l_f_v3F_neurons_sr)
nest.Connect(l_f_Ia_fiber_generator, l_f_Ia_fiber_generator_sr)
nest.Connect(l_f_Ia_fibers, l_f_Ia_fiber_sr)
nest.Connect(l_f_rg_neurons, l_f_rg_neurons_sr)
nest.Connect(l_f_motor_neurons, l_f_motor_neurons_sr)

# Static synapses
## Generator 2 neurons
conn_dict_ex = {"rule": "fixed_indegree", "indegree": Ke}
gen2neuron_dict = {"rule": "all_to_all"}
syn_dict_ex = {"delay": d, "weight": Je}
nest.Connect(bs_generator, bs_neurons, gen2neuron_dict, syn_dict_ex)
nest.Connect(l_f_Ia_fiber_generator, l_f_Ia_fibers, gen2neuron_dict, syn_dict_ex)

## Neurons 2 neurons
nest.Connect(l_f_rg_neurons, l_f_motor_neurons, gen2neuron_dict, syn_dict_ex)

## STDP synapses setup
### V3
neuron2neuron_stdp_dict = {"rule": "all_to_all"}

nest.CopyModel("jonke_synapse", "V3_stdp_synapse_rec",
               {"weight_recorder": l_f_v3F_neurons_wr[0],
                "Wmax": w_max,
                "lambda": lambda_mean
                })
V3_syn_stdp_dict = {"synapse_model": "V3_stdp_synapse_rec",
                    "weight": nest.random.lognormal(mean=w_mean, std=w_std),
                    "delay": delay_def
                    }
nest.Connect(bs_neurons, l_f_v3F_neurons, neuron2neuron_stdp_dict, V3_syn_stdp_dict)

### Ia
nest.CopyModel("jonke_synapse", "Ia_stdp_synapse_rec",
               {"weight_recorder": l_f_Ia2rg_neurons_wr[0],
                "Wmax": w_max,
                "lambda": rg_lambda,
                #"alpha": Ia_alpha,
                })
nrn_model = "pp_cond_exp_mc_urbanczik"
syns = nest.GetDefaults(nrn_model)["receptor_types"]
Ia_syn_stdp_dict = {"synapse_model": "Ia_stdp_synapse_rec",
                    "weight": nest.random.lognormal(mean=rg_w_mean, std=w_std),
                    "delay": delay_def,
                    # "receptor_type": syns["dendritic_exc"] ## for pp_cond_exp_mc_urbanczik
                    }
l_f_Ia2rg = nest.Connect(l_f_Ia_fibers, l_f_rg_neurons, neuron2neuron_stdp_dict, Ia_syn_stdp_dict)
log.debug(str(l_f_Ia2rg))
###############################################################################
# Before each trial, we set the ``origin`` of the ``poisson_generator`` to the
# current simulation time. This automatically sets the start and stop time of
# the ``poisson_generator`` to the specified times with respect to the origin.
# The simulation is then carried out for the specified time in trial_duration.

log.info('Simulation started ...')
for n in range(num_steps):
    log.info("Step = " + str(n))
    for ph in range(num_phases):
        bs_generator.origin = nest.biological_time
        ### V3 rate
        rate = get_V3_rate(ph, v3F_lo, v3F_mid, v3F_hi)
        log.debug("Rate = " + str(rate))
        bs_generator.rate = rate
        ### Ia rate
        Ia_rate = get_Ia_rate(ph, Ia_fibers_freq_lo, Ia_fibers_freq_hi)
        log.debug("Rate = " + str(Ia_rate))
        l_f_Ia_fiber_generator.rate = Ia_rate
        ### Cut fibers
        l_e_cut_fiber_generator[:].rate = cut_lo
        cut_chunk_number, cut_freq = identity_cut_chunk(ph, cut_hi, cut_lo)
        for chn in cut_chunk_number:
            ## log.info(str(chn*cut_chank) + ": " + str((chn+1)*cut_chank-1))
            l_e_cut_fiber_generator[chn * cut_chunk:(chn + 1) * cut_chunk - 1].rate = cut_freq
        nest.Simulate(phase_duration)

log.info('Simulation completed ...')

dump_spike_recorder(l_f_Ia_fiber_generator_sr, 'l_f_Ia_fiber_generator_sr')
dump_spike_recorder(l_f_Ia_fiber_sr, 'l_f_Ia_fiber_sr')
dump_spike_recorder(l_f_rg_neurons_sr, 'l_f_rg_neurons_sr')
dump_spike_recorder(l_f_motor_neurons_sr, 'l_f_motor_neurons_sr')
dump_weight_recorder(l_f_v3F_neurons_wr, 'l_f_v3F_neurons_wr')
dump_weight_recorder(l_f_Ia2rg_neurons_wr, 'l_f_Ia2rg_neurons_wr')




