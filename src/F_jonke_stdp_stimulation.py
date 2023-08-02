import nest
import nest.raster_plot
import matplotlib.pyplot as plt
import logging
import numpy as np

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

trial_duration = 1000.0  # trial duration, in ms
phase_duration = 100.0
simulation_hill_toe_phases = 4
num_phases = 10
num_steps = 10  # 5  # number of trials to perform

## Commisural projections
v3F_num = 200
v3F_hi = 200.0  # Hz spiking rate
v3F_mid = 100.0
v3F_lo = 50.0  # Hz spiking rate

bs_num = 100

l_f_rg_num = 200 # number of rhythm generator neurons

## Ia projections
Ia_fibers_num = 100 # 8 #100
# [20,50,20,50,20]*Hz
Ia_fibers_freq_hi = 50#Hz
Ia_fibers_freq_lo = 10#Hz #20*Hz
Ia_I_e = 500
Ia_g_L = 10.0
Ia_tau_plus = 120.0 # tau_w
Ia_E_L = -58.0
Ia_lambda = 1.0 # b= 100.0
Ia_C_m = 200.0
Ia_V_m = -58.0
Ia_w_mean = 5.0 # Initial weight #! must be equal to 5 Initial weight
Ia_alpha = 2.0
Ia_delay = 120

## Cutaneous projectons
cut_num = 100
cut_lo = 5.0  # Hz spiking rate
cut_hi = 50.0  # 200.0 # 50.0  # Hz spiking rate
cut_chunk = int(cut_num / simulation_hill_toe_phases)

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
nest.total_num_virtual_procs = 15

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
Ia_fibers_params = {"I_e": Ia_I_e,
                    "g_L" : Ia_g_L,
                    "E_L" : Ia_E_L,
                    "C_m" :  Ia_C_m,
                    "V_m" : Ia_V_m}

## hh_psc_alpha_clopath

bs_neurons = nest.Create("hh_psc_alpha_clopath", bs_num)
l_f_v3F_neurons = nest.Create("hh_psc_alpha_clopath", v3F_num)
l_f_rg_neurons = nest.Create("hh_psc_alpha_clopath", l_f_rg_num)
l_f_Ia_fibers = nest.Create("hh_psc_alpha_clopath", Ia_fibers_num,
                            params=Ia_fibers_params
                            )

###############################################################################
# The ``spike_recorder`` is created and the handle stored in `sr`.
bs_sr = nest.Create("spike_recorder")
bs_neurons_sr = nest.Create("spike_recorder")
l_f_v3F_neurons_sr = nest.Create("spike_recorder")
l_f_v3F_neurons_wr = nest.Create("weight_recorder")
l_f_rg_neurons_sr = nest.Create("spike_recorder")
l_f_Ia_fiber_generator_sr = nest.Create("spike_recorder")
l_f_Ia2rg_neurons_wr = nest.Create("weight_recorder")

###############################################################################
# The Connect function connects the nodes so spikes from pg are collected by
# the spike_recorder
nest.Connect(bs_generator, bs_sr)
nest.Connect(bs_neurons, bs_neurons_sr)
nest.Connect(l_f_v3F_neurons, l_f_v3F_neurons_sr)
nest.Connect(l_f_Ia_fiber_generator, l_f_Ia_fiber_generator_sr)
nest.Connect(l_f_rg_neurons, l_f_rg_neurons_sr)

# Generator w neurons
conn_dict_ex = {"rule": "fixed_indegree", "indegree": Ke}
gen2neuron_dict = {"rule": "all_to_all"}
syn_dict_ex = {"delay": d, "weight": Je}
nest.Connect(bs_generator, bs_neurons, gen2neuron_dict, syn_dict_ex)
nest.Connect(l_f_Ia_fiber_generator, l_f_Ia_fibers, gen2neuron_dict, syn_dict_ex)

## STDP synapses setup
### V3
neuron2neuron_stdp_dict = {"rule": "all_to_all"}

nest.CopyModel("jonke_synapse", "V3_stdp_synapse_rec",
               {"weight_recorder": l_f_v3F_neurons_wr[0],
                "Wmax": w_max,
                "lambda": lambda_mean })
V3_syn_stdp_dict = {"synapse_model": "V3_stdp_synapse_rec",
                    "weight": nest.random.lognormal(mean=w_mean, std=w_std),
                    "delay": delay_def
                    }
nest.Connect(bs_neurons, l_f_v3F_neurons, neuron2neuron_stdp_dict, V3_syn_stdp_dict)

### Ia
nest.CopyModel("jonke_synapse", "Ia_stdp_synapse_rec",
               {"weight_recorder": l_f_Ia2rg_neurons_wr[0],
                "Wmax": w_max,
                "lambda": Ia_lambda,
                #"alpha": Ia_alpha,
                #"tau_plus" : Ia_tau_plus,
                })
Ia_syn_stdp_dict = {"synapse_model": "Ia_stdp_synapse_rec",
                    "weight": nest.random.lognormal(mean=Ia_w_mean, std=w_std),
                    "delay": delay_def
                    }
nest.Connect(l_f_Ia_fibers, l_f_rg_neurons, neuron2neuron_stdp_dict, Ia_syn_stdp_dict)

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
###############################################################################
# Now we plot the result, including a histogram using the ``nest.raster_plot``
# function. Note: The histogram will show spikes seemingly located before
# 100 ms into each trial. This is due to sub-optimal automatic placement of
# histogram bin borders.

#nest.raster_plot.from_device(bs_sr, hist=True, hist_binwidth=100.0, title="brainstem generator spikes")
#plt.show()

# nest.raster_plot.from_device(bs_neurons_sr, hist=True, hist_binwidth=100.0, title="brainstem spikes")
# plt.show()

#V3 spikes
nest.raster_plot.from_device(l_f_v3F_neurons_sr, hist=True, hist_binwidth=100.0, title="v3F spikes")
plt.show()


#Ia spikes
nest.raster_plot.from_device(l_f_Ia_fiber_generator_sr, hist=True, hist_binwidth=100.0, title="L F gen RG spikes")
plt.show()

#Ia spikes
nest.raster_plot.from_device(l_f_rg_neurons_sr, hist=True, hist_binwidth=100.0, title="L F RG spikes")
plt.show()

# plot results
fs = 22
lw = 2.5
#V3 weights
# senders = l_f_v3F_neurons_wr.events["senders"]
# targets = l_f_v3F_neurons_wr.events["targets"]
# weights = l_f_v3F_neurons_wr.events["weights"]
# times = l_f_v3F_neurons_wr.events["times"]
senders = l_f_Ia2rg_neurons_wr.events["senders"]
targets = l_f_Ia2rg_neurons_wr.events["targets"]
weights = l_f_Ia2rg_neurons_wr.events["weights"]
times = l_f_Ia2rg_neurons_wr.events["times"]

# synaptic weights
fig2, axA = plt.subplots(1, 1)
for i in np.arange(2, 200, 10):
    index = np.intersect1d(np.where(senders == senders[i]), np.where(targets == targets[1]))
    if not len(index) == 0:
        axA.step(times[index], weights[index], label="pg_{}".format(i - 2), lw=lw)

axA.set_title("Synaptic weights of synapses")
axA.set_xlabel("time [ms]", fontsize=fs)
axA.set_ylabel("weight", fontsize=fs)
axA.legend(fontsize=fs - 4)
plt.show()


log.info('Completed draw')
