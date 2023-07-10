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
        plot(firing_times_steps[step], neuron_ids_steps[step], 'b,')
        savefig(f'plots/{file_name}_{step}.png')
        close()


def get_normalized_step(ids, times, i):
    step_out_ids, step_out_times = np.asarray(ids[i]), np.asarray(times[i])
    step_out_ids -= np.min(step_out_ids)
    step_out_times -= np.min(step_out_times)
    step_out_ids = step_out_ids / np.max(step_out_ids)
    step_out_times = step_out_times / np.max(step_out_times)

    return step_out_times, step_out_ids


def spikes_on_diagonal(ids, times, eps=0.1):
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

def test_correlation(inputs, outputs):
    in_ids, in_times = inputs
    out_ids, out_times = outputs

    absolute = []
    shared = []
    rg_spikes = []
    for i in range(len(in_ids)):
        norm_in = get_normalized_step(in_ids, in_times, i)
        norm_out = get_normalized_step(out_ids, out_times, i)

        cut_spikes, _ = spikes_on_diagonal(*norm_in)
        rg_neurons_diagonal_spikes, rg_neurons_diagonal_spikes_share = spikes_on_diagonal(*norm_out)

        absolute.append(rg_neurons_diagonal_spikes / cut_spikes)
        shared.append(rg_neurons_diagonal_spikes_share / cut_spikes)
        rg_spikes.append(len(norm_out[0]) / cut_spikes)

    absolute = gaussian_filter1d(absolute, sigma=10)
    shared = gaussian_filter1d(shared, sigma=10)
    rg_spikes = gaussian_filter1d(rg_spikes, sigma=10)

    return absolute, shared, rg_spikes


def main():
    inputs = divide_in_steps(
        *merge_spikes('pickle_/121/l_e_cut_spikes0.pickle', 'pickle_/121/l_e_cut_spikes1.pickle'))
    outputs = divide_in_steps(
        *merge_spikes('pickle_/121/l_e_rg_neurons_spikes0.pickle', 'pickle_/121/l_e_rg_neurons_spikes1.pickle'))

    inputs60 = divide_in_steps(
        *merge_spikes('pickle_/l_e_cut_spikes.pickle'))
    outputs60 = divide_in_steps(
        *merge_spikes('pickle_/l_e_rg_neurons_spikes.pickle'))

    absolute, shared, rg_spikes = test_correlation(inputs, outputs)

    weights, times = read_weights('pickle_/121/l_e_cut2rg_weigts1.pickle')
    weights = np.mean(weights, axis=1)
    weights = gaussian_filter1d(weights, sigma=200)

    figure, axis = subplots(2, 2)

    axis[0, 0].plot(range(len(absolute)), absolute)
    axis[0, 0].set_title("rg_neurons_diagonal_spikes / cut_spikes")
    axis[1, 0].plot(range(len(shared)), shared)
    axis[1, 0].set_title("rg_neurons_diagonal_spikes / rg_neurons_spikes / cut_spikes")
    axis[0, 1].plot(range(len(rg_spikes)), rg_spikes)
    axis[0, 1].set_title("rg_neurons_spikes / cut_spikes")
    axis[1, 1].plot(times, weights)
    axis[1, 1].set_title("weights")

    show()

    generate_plots(*inputs, plots_n=3, file_name='outputs')

if __name__ == '__main__':
    main()
