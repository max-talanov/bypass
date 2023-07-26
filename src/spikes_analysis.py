from brian2 import *
import pickle
from scipy.ndimage import gaussian_filter1d


def read_spikes(file_name):
    with open(file_name, 'rb') as m_f:
        m_mon = pickle.load(m_f)
        firing_times = m_mon["t"] / second
        neuron_ids = m_mon["i"]
        return neuron_ids, firing_times


def read_weights(file_name):
    with open(file_name, 'rb') as m_f:
        m_mon = pickle.load(m_f)
        times = m_mon["t"] / second
        weights = m_mon["s"]
        return weights, times


def merge_spikes(*paths):
    ids = []
    times = []
    for path in paths:
        file_ids, file_times = read_spikes(path)
        ids.extend(file_ids)
        times.extend(file_times)
    return ids, times


def divide_in_steps(neuron_ids, firing_times):
    i = -1
    neuron_ids_steps = []
    firing_times_steps = []
    for neuron_id, firing_time in zip(neuron_ids, firing_times):
        if int(firing_time) > i:
            i = int(firing_time)
            neuron_ids_steps.append([])
            firing_times_steps.append([])
        neuron_ids_steps[i].append(neuron_id)
        firing_times_steps[i].append(firing_time)
    return neuron_ids_steps, firing_times_steps


def generate_plots(neuron_ids_steps, firing_times_steps, file_name, plots_n):
    steps_to_plot = np.linspace(0, len(neuron_ids_steps) - 1, plots_n).astype(int)
    for step in steps_to_plot:
        plot(firing_times_steps[step], neuron_ids_steps[step], 'g,')
        savefig(f'plots/{file_name}_{step}.png')
        close()

def generate_on_top(rg_spikes, muscle_spikes, file_name, plots_n):
    rg_ids_steps, rg_times_steps = rg_spikes
    muscle_ids_steps, muscle_times_steps = muscle_spikes

    steps_to_plot = np.linspace(0, len(rg_ids_steps) - 1, plots_n).astype(int)
    for step in steps_to_plot:
        plot(muscle_times_steps[step], muscle_ids_steps[step], 'b,')
        plot(rg_times_steps[step], rg_ids_steps[step], 'g,')
        savefig(f'plots/{file_name}_{step}.png')
        close()

def get_normalized_step(ids, times, i):
    step_out_ids, step_out_times = np.asarray(ids[i]), np.asarray(times[i])
    step_out_ids -= np.min(step_out_ids)
    step_out_times -= np.min(step_out_times)
    step_out_ids = step_out_ids / np.max(step_out_ids)
    step_out_times = step_out_times / np.max(step_out_times)

    return step_out_times, step_out_ids


def spikes_on_diagonal(ids, times, eps=0.01):
    diagonal_spikes = 0
    for id, time in zip(ids, times):
        if id < 0.25 + eps and time < 0.3 + eps:
            diagonal_spikes += 1
            continue
        if id < 0.5 + eps and 0.2 - eps < time < 0.6 + eps:
            diagonal_spikes += 1
            continue
        if id < 0.75 + eps and 0.4 - eps < time < 0.8 + eps:
            diagonal_spikes += 1
            continue
        if time > 0.75 - eps:
            diagonal_spikes += 1

    diagonal_spikes_share = diagonal_spikes / len(ids)
    return diagonal_spikes, diagonal_spikes_share

def test_correlation(cut_inputs, muscle_inputs, outputs):
    muscle_in_ids, muscle_in_times = muscle_inputs
    cut_in_ids, cut_in_times = cut_inputs
    rg_out_ids, rg_out_times = outputs

    absolute = []
    shared = []
    rg_spikes = []
    cut = []
    muscle = []
    for i in range(len(cut_in_ids)):
        norm_cut_in = get_normalized_step(cut_in_ids, cut_in_times, i)
        norm_muscle_in = get_normalized_step(muscle_in_ids, muscle_in_times, i)
        norm_rg_out = get_normalized_step(rg_out_ids, rg_out_times, i)
        rg_neurons_diagonal_spikes, rg_neurons_diagonal_spikes_share = spikes_on_diagonal(*norm_rg_out)
        absolute.append(rg_neurons_diagonal_spikes)
        shared.append(rg_neurons_diagonal_spikes_share)
        rg_spikes.append(len(norm_rg_out[0]))
        cut.append(len(norm_cut_in[0]))
        muscle.append(len(norm_muscle_in[0]))


    absolute = gaussian_filter1d(absolute, sigma=10)
    shared = gaussian_filter1d(shared, sigma=10)
    rg_spikes = gaussian_filter1d(rg_spikes, sigma=10)

    return absolute, shared, rg_spikes, cut, muscle

def main():
    folder = 'F3'
    muscle_spikes = divide_in_steps(
        *merge_spikes(f'pickle_/{folder}/l_f_muscle_spikes.pickle'))
    rg_spikes = divide_in_steps(
        *merge_spikes(f'pickle_/{folder}/l_f_rg_neurons_spikes.pickle'))
    # muscle_spikes = divide_in_steps(
    #     *merge_spikes('pickle_/F0/long_runl_f_muscle_spikes.pickle'))
    # muscle_spikes = divide_in_steps(
    #     *merge_spikes('pickle_/F0/long_runl_f_muscle_spikes.pickle'))
    # cut_inputs = divide_in_steps(
    #     *merge_spikes('pickle_/cut10dapre01/l_e_cut_spikes (8).pickle'))
    # rg_outputs = divide_in_steps(
    #     *merge_spikes('pickle_/cut10dapre01/l_e_rg_neurons_spikes (7).pickle'))

    # absolute, shared, rg_spikes, cut, muscle = test_correlation(cut_inputs, muscle_inputs, rg_outputs)

    weights, times = read_weights(f'pickle_/{folder}/l_f_muscle2rg_weigts.pickle')
    weights = np.mean(weights, axis=1)
    weights = gaussian_filter1d(weights, sigma=200)
    plot(times, weights)
    show()

    # figure, axis = subplots(2, 2)
    #
    # axis[0, 0].plot(range(len(muscle_spikes)), muscle_spikes)
    # axis[0, 0].set_title("muscle_spikes")
    #
    # axis[1, 0].plot(range(len(muscle_spikes)), muscle_spikes)
    # axis[1, 0].set_title("muscle_spikes")
    #
    # axis[0, 1].plot(range(len(rg_spikes)), rg_spikes)
    # axis[0, 1].set_title("rg_spikes")
    #
    # axis[1, 1].plot(range(len(rg_spikes), rg_spikes))
    # axis[1, 1].set_title("rg_spikes")
    #
    # show()

    generate_on_top(rg_spikes, muscle_spikes, plots_n=6, file_name='rg_spikes')
    # generate_plots(*rg_spikes, plots_n=6, file_name='rg_spikes')
    # generate_plots(*muscle_spikes, plots_n=6, file_name='muscle_spikes')

if __name__ == '__main__':
    main()
