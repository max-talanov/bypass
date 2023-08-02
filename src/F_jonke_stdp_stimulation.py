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


def _make_plot(ts, ts1, node_ids, neurons, hist=True, hist_binwidth=5.0, grayscale=False, title=None, xlabel=None,
               color=',b'):

    """Generic plotting routine.

    Constructs a raster plot along with an optional histogram (common part in
    all routines above).

    Parameters
    ----------
    ts : list
        All timestamps
    ts1 : list
        Timestamps corresponding to node_ids
    node_ids : list
        Global ids corresponding to ts1
    neurons : list
        Node IDs of neurons to plot
    hist : bool, optional
        Display histogram
    hist_binwidth : float, optional
        Width of histogram bins
    grayscale : bool, optional
        Plot in grayscale
    title : str, optional
        Plot title
    xlabel : str, optional
        Label for x-axis
    """
    import matplotlib.pyplot as plt

    plt.figure()

    color_marker: str = color
    if grayscale:
        color_marker = ".k"
        color_bar = "gray"
    else:
        color_bar = "blue"

    color_edge = "black"

    if xlabel is None:
        xlabel = "Time (ms)"

    ylabel = "Neuron ID"

    if hist:
        ax1 = plt.axes([0.1, 0.3, 0.85, 0.6])
        plotid = plt.plot(ts1, node_ids, color_marker)
        plt.ylabel(ylabel)
        plt.xticks([])
        xlim = plt.xlim()

        plt.axes([0.1, 0.1, 0.85, 0.17])
        t_bins = np.arange(np.amin(ts), np.amax(ts), float(hist_binwidth))
        n, _ = nest.raster_plot._histogram(ts, bins=t_bins)
        num_neurons = len(np.unique(neurons))
        heights = 1000 * n / (hist_binwidth * num_neurons)

        plt.bar(t_bins, heights, width=hist_binwidth, color=color_bar, edgecolor=color_edge)
        plt.yticks([int(x) for x in np.linspace(0.0, int(max(heights) * 1.1) + 5, 4)])
        plt.ylabel("Rate (Hz)")
        plt.xlabel(xlabel)
        plt.xlim(xlim)
        plt.axes(ax1)
    else:
        plotid = plt.plot(ts1, node_ids, color_marker)
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)

    if title is None:
        plt.title("Raster plot")
    else:
        plt.title(title)

    #plt.draw()

    return plotid

def make_raster_plot(detec, **kwargs):

    ts, node_ids = nest.raster_plot._from_memory(detec)
    if not len(ts):
        raise nest.kernel.NESTError("No events recorded!")

    if "title" not in kwargs:
        kwargs["title"] = "Raster plot from device '%i'" % detec.get("global_id")

    if detec.get("time_in_steps"):
        xlabel = "Steps"
    else:
        xlabel = "Time (ms)"
    return _make_plot(ts, ts, node_ids, node_ids, xlabel=xlabel, **kwargs)


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
# make_raster_plot(l_f_v3F_neurons_sr, hist=True, hist_binwidth=100.0, title="v3F spikes")
# plt.show()

#Ia gen spikes
# make_raster_plot(l_f_Ia_fiber_generator_sr, hist=True, hist_binwidth=10.0, title="L F gen RG spikes")
# plt.show()

#Ia generator spikes
make_raster_plot(l_f_Ia_fiber_generator_sr, hist=True, hist_binwidth=5.0, title="L F Ia gen spikes", color=",m")
plt.show()

#Ia generator spikes
make_raster_plot(l_f_Ia_fiber_generator_sr, hist=True, hist_binwidth=5.0, title="L F Ia fiber spikes", color=",g")
plt.show()

#RG spikes
make_raster_plot(l_f_rg_neurons_sr, hist=True, hist_binwidth=5.0, title="L F RG spikes", color=",b")
plt.show()

#motor spikes
make_raster_plot(l_f_motor_neurons_sr, hist=True, hist_binwidth=5.0, title="L F Motor spikes", color=",r")
plt.show()

# Weights
fs = 10
lw = 0.5
#V3 weights
senders = l_f_v3F_neurons_wr.events["senders"]
targets = l_f_v3F_neurons_wr.events["targets"]
weights = l_f_v3F_neurons_wr.events["weights"]
times = l_f_v3F_neurons_wr.events["times"]

# bs2V3 weights

fig1, axA = plt.subplots(1, 1)
for i in np.arange(2, 200, 10):
    index = np.intersect1d(np.where(senders == senders[i]), np.where(targets == targets[1]))
    if not len(index) == 0:
        axA.step(times[index], weights[index], label="v3{}".format(i - 2), lw=lw)

axA.set_title("bs -> V3 weights ")
axA.set_xlabel("time [ms]", fontsize=fs)
axA.set_ylabel("weight", fontsize=fs)
axA.legend(fontsize=fs - 4)
plt.show()

# Ia 2 rg weights
senders = l_f_Ia2rg_neurons_wr.events["senders"]
targets = l_f_Ia2rg_neurons_wr.events["targets"]
weights = l_f_Ia2rg_neurons_wr.events["weights"]
times = l_f_Ia2rg_neurons_wr.events["times"]

# synaptic weights
fig2, axA = plt.subplots(1, 1)
for i in np.arange(2, 500, 10):
    index = np.intersect1d(np.where(senders == senders[i]), np.where(targets == targets[1]))
    if not len(index) == 0:
        axA.step(times[index], weights[index], label="rg{}".format(i - 2), lw=lw)

axA.set_title("Ia -> f_rg weights of synapses")
axA.set_xlabel("time [ms]", fontsize=fs)
axA.set_ylabel("weight", fontsize=fs)
axA.legend(fontsize=fs - 4)
plt.show()

log.info('Completed draw')
