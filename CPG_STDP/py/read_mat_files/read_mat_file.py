from collections import OrderedDict

import numpy as np
import scipy.io
import matplotlib.pyplot as plt
from bokeh.plotting import figure, show




# # Пример доступа к данным
# if 'hd' in mat_contents:
#     data = mat_contents['hd'][0][0][45]
#     print("Data from the mat file:", data)
# else:
#     print("Key 'data' not found in the mat file.")
#
#
# # Пример доступа к данным
# if 'spks' in mat_contents:
#     data = mat_contents['spks'][0][1][0]
#     print("Data from the mat file:", data)
# else:
#     print("Key 'data' not found in the mat file.")

# if 'lfp' in mat_contents:
#     data = mat_contents['lfp'][0]
#     print("Data from the mat file:", data)
# else:
#     print("Key 'data' not found in the mat file.")
#




def plot_lfp(lfp, matplotlib=False, bokeh=False):

    '''
        plot lfp graph
        Args:
    		lfp: dictionary with keys and values
    		matplotlib (bool): choose lib
    		bokeh (bool): choose lib
    	Returns:
    		dict: dictionary with keys and values
        '''
    const = 300
    colors = ['black', 'navy', 'darkslateblue', 'indigo', 'purple', 'darkorchid', 'firebrick', 'indianred',
              'palevioletred', 'lightcoral', 'salmon', 'sandybrown', 'lightsalmon', 'orange', 'gold', 'yellow','yellowgreen']
    data = {}
    for key, value in lfp.items():
        new_key = int(key.split("/")[-1])
        data[new_key] = value

    sorted_keys = sorted(data.keys(), reverse=True)
    ordered_data = OrderedDict()
    for index, key in enumerate(sorted_keys):
        ordered_data[index] = data[key]

    if matplotlib:
        fig, ax = plt.subplots()

        for key, data in ordered_data.items():
            xticks = np.linspace(0, 50, len(data))
            ax.plot(xticks, data + key * const, lw=1.5, color=colors[key])

        ax.set_yticks(np.arange(16) * const)
        ax.set_yticklabels(np.arange(16))

        plt.xlabel('Time (ms)')
        plt.ylabel('Sensors № (mV)')
        plt.show()

    if bokeh:
        p = figure(x_axis_label='Time (ms)', y_axis_label='Sensors')
        # p.yaxis.major_label_text_font_size = '0pt'

        x_values = np.linspace(0, 50, num=2001)

        for key in ordered_data:
            # xticks = np.arange(len(data[key]))
            xticks = x_values
            y_offset = key * 3000
            # plot the curve
            p.line(xticks, np.array(ordered_data[key]) + y_offset, line_width=2, color=colors[key])
        show(p)

    return ordered_data


if __name__ == '__main__':
    # Путь к вашему .mat файлу
    file_path = 'files/2024-07-11_16-58-25.analysis.mat'

    # Чтение .mat файла
    mat_contents = scipy.io.loadmat(file_path)

    # Вывод ключей файла
    print("Keys in the mat file:", mat_contents.keys())

    for key in mat_contents.keys():
        with open(f"files/2024-07-11_16-58_{key}.txt", 'w') as f:
            f.write(str(mat_contents[key]))

    # Извлечение данных
    lfp_data = mat_contents['lfpAnalys']
    spks_data = mat_contents['parAnalys']

    # Визуализация данных нейрональной активности для всех нейронов
    fig, axs = plt.subplots(lfp_data.shape[0], 1, figsize=(12, 2 * lfp_data.shape[0]), sharex=True)

    for neuron_index in range(lfp_data.shape[0]):
        neuron_lfp = lfp_data[neuron_index]
        neuron_spk = spks_data[neuron_index][0][0]  # Извлечение временных меток спайков

        # Создание временной шкалы для LFP данных
        time_lfp = np.linspace(0, len(neuron_lfp), num=len(neuron_lfp))

        axs[neuron_index].plot(time_lfp, neuron_lfp, label=f'Neuron {neuron_index + 1} LFP')

        # Добавление спайков
        spike_times = [int(time) for sublist in neuron_spk for time in sublist if int(time) < len(neuron_lfp)]
        spike_values = [neuron_lfp[int(time)] for time in spike_times if int(time) < len(neuron_lfp)]

        # Убедимся, что размеры массивов совпадают
        if len(spike_times) == len(spike_values):
            axs[neuron_index].scatter(spike_times, spike_values, color='red',
                                      label=f'Neuron {neuron_index + 1} Spikes')

        axs[neuron_index].set_ylabel('LFP Amplitude')
        axs[neuron_index].legend(loc='upper right')

    # Настройка осей и заголовка
    plt.xlabel('Time')
    fig.suptitle('Neuronal Activity (LFP) with Spike Times for All Neurons')
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.show()