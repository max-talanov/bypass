import nest
import matplotlib.pyplot as plt
import numpy as np

from src.F_jonke_stdp_stimulation import make_raster_plot

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

bs_sr = nest.Create("spike_recorder", params={"record_to": "ascii", "label": "bs_sr"})
bs_neurons_sr = nest.Create("spike_recorder")
l_f_v3F_neurons_sr = nest.Create("spike_recorder")
l_f_v3F_neurons_wr = nest.Create("weight_recorder")
l_f_Ia_fiber_generator_sr = nest.Create("spike_recorder")
l_f_Ia_fiber_sr = nest.Create("spike_recorder")
l_f_rg_neurons_sr = nest.Create("spike_recorder")
l_f_Ia2rg_neurons_wr = nest.Create("weight_recorder")
l_f_motor_neurons_sr = nest.Create("spike_recorder")

nest.SetStatus(bs_sr, {"from_file": "bs_sr.dat"})
nest.SetStatus(bs_neurons_sr, {"from_file": "bs_neurons_sr.dat"})
nest.SetStatus(l_f_v3F_neurons_sr, {"from_file": "l_f_v3F_neurons_sr.dat"})
nest.SetStatus(l_f_v3F_neurons_wr, {"from_file": "l_f_v3F_neurons_wr.dat"})
nest.SetStatus(l_f_Ia_fiber_generator_sr, {"from_file": "l_f_Ia_fiber_generator_sr.dat"})
nest.SetStatus(l_f_Ia_fiber_sr, {"from_file": "l_f_Ia_fiber_sr.dat"})
nest.SetStatus(l_f_rg_neurons_sr, {"from_file": "l_f_rg_neurons_sr.dat"})
nest.SetStatus(l_f_Ia2rg_neurons_wr, {"from_file": "l_f_Ia2rg_neurons_wr.dat"})
nest.SetStatus(l_f_motor_neurons_sr, {"from_file": "l_f_motor_neurons_sr.dat"})

"""


time_intervals = [(0.0, 100.0), (100.0, 200.0), (200.0, 300.0)]  # Customize as needed

# Save spike data to multiple files
for i, (start_time, end_time) in enumerate(time_intervals):
    file_name = f"spike_data_{i}.dat"
    nest.SetStatus(l_f_v3F_neurons_sr, {"to_file": file_name, "start": start_time, "stop": end_time})

"""


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
make_raster_plot(l_f_Ia_fiber_generator_sr, hist=False, hist_binwidth=5.0, title="L F Ia gen spikes", color=",m")
plt.show()

#Ia generator spikes
make_raster_plot(l_f_Ia_fiber_generator_sr, hist=False, hist_binwidth=5.0, title="L F Ia fiber spikes", color=",g")
plt.show()

#RG spikes
make_raster_plot(l_f_rg_neurons_sr, hist=False, hist_binwidth=5.0, title="L F RG spikes", color=",b")
plt.show()

#motor spikes
make_raster_plot(l_f_motor_neurons_sr, hist=False, hist_binwidth=5.0, title="L F Motor spikes", color=",r")
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
