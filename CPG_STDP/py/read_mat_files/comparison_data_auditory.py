import numpy as np
import scipy
import bokeh
import panel as pn
from scipy.ndimage import gaussian_filter
from bokeh.io import output_notebook
from bokeh.plotting import figure, show, output_file

bokeh.sampledata.download()
output_notebook()


def show_lines(data, time, start, end, name, offset=1.0):
    p = figure(title=name,
               x_axis_label="time (ms)",
               y_axis_label="Канал",
               width=800,
               height=400)
    colors = [
        "#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd",
        "#8c564b", "#e377c2", "#7f7f7f", "#bcbd22", "#17becf",
        "#aec7e8", "#ffbb78", "#98df8a", "#ff9896", "#c5b0d5"
        # "#c49c94"
    ]

    offset = -400
    # Отображение линий по оси Y (номера каналов)
    for i, (y, color) in enumerate(zip(data, colors)):
        # Номера каналов по оси Y
        p.line(x=np.array(time[start:end]), y=np.array(y[start:end]) + i * offset, line_width=2, color=color)

    leng = len(data) - 1
    p.yaxis.ticker = [i * offset for i in range(leng)]  # Устанавливаем деления на оси Y
    p.yaxis.major_label_overrides = {i * offset: str(i + 1) for i in range(leng)}  # Устанавливаем метки

    # Настройка легенды
    p.legend.location = "top_left"
    p.legend.click_policy = "hide"

    # Отображение графика
    output_file(name + '.html')
    show(p, notebook_handle=True)


def gaussian_filter_data(arr, sigma=1.0):
    smoothed_data = gaussian_filter(arr, sigma=sigma)
    return smoothed_data


if __name__ == '__main__':
    file_path = 'files/2024-07-11_16-58-25.analysis.mat'
    mat_contents = scipy.io.loadmat(file_path)
    pn.extension('plotly')
    lfp_data = mat_contents['lfpAnalys']
    time_data = mat_contents['sounds']

    list_smooth = []
    list_lfps = [[] for _ in range(17)]
    all_list_lfps = [[[] for _ in range(17)] for _ in range(10)]
    time_1s = []
    time_5s = []
    time_10s = []
    for lfp in lfp_data:
        for i, l in enumerate(lfp):
            list_lfps[i].append(np.mean(l))
            for j, s in enumerate(l):
                all_list_lfps[j][i].append(s)

    time = []
    start = 0
    end = 0
    end_5s = 0
    for j, t in enumerate(time_data):
        if t[0] == 20.0 and start == 0:
            start = j
        if t[0] == 20000.0 and end == 0:
            end = j
        if t[0] > 6000.0 and end_5s == 0:
            end_5s = j
        time.append(t[0])

    for j in list_lfps:
        list_smooth.append(gaussian_filter_data(j, 3))

    for k, expir in enumerate(all_list_lfps):
        show_lines(expir[:16], time, start, end_5s, f'{k}_expiriment')
    # show_lines(list_lfps[:16], time, start, end, "now_data")
    show_lines(list_smooth[:16], time, start, end_5s, "smooth_data")
