import os
import sys

import numpy as np
import scipy
import bokeh
import plotly.graph_objects as go
from bokeh.io import output_notebook
from bokeh.models import Span
import panel as pn
from scipy.ndimage import gaussian_filter
from scipy.stats import norm
from scipy.signal import find_peaks
from bokeh.plotting import figure, show, output_file
from bokeh.layouts import gridplot
from bokeh.transform import linear_cmap
from bokeh.models import ColumnDataSource, ColorBar, LinearColorMapper

bokeh.sampledata.download()
directory_path = '.'
sys.path.append('read_mat_files/')
my_path = os.path.abspath('read_mat_files/')
output_notebook()
import plotly.io as pio
pio.renderers.default = 'browser'


def plot_picks(lfp, time):
    x_values = np.array(time)  # Индексы для оси X
    y_values = np.array(lfp)  # Данные для оси Y

    # Найти пики в list_lfps[0]
    peak, _ = find_peaks(y_values, height=0)

    # Создание графика с использованием Bokeh
    p = figure(title="LFP Data with Peaks", x_axis_label='Time', y_axis_label='Amplitude')

    # Построение основного графика
    p.line(x_values, y_values, line_width=2, legend_label="LFP Data")

    # Добавление пиков (метки на графике)
    p.circle(x_values[peak], y_values[peak], size=10, color="red", legend_label="Peaks")

    # Добавление зеленой линии на уровне 0 (нулевая линия)
    zero_line = Span(location=0, dimension='width', line_color='green', line_dash='dashed', line_width=2)
    p.add_layout(zero_line)

    # Показ графика
    output_file('auditory.html')
    show(p)


def plot_picks_2(lfp, time):
    # Преобразование данных
    x_values = np.array(time)
    y_values = np.array(lfp)

    # Нахождение пиков
    peaks, _ = find_peaks(y_values, height=15)

    # Извлечение времени пиков
    peak_times = x_values[peaks]

    # Построение гистограммы для плотности пиков (приближение плотности)
    hist, edges = np.histogram(peak_times, bins=50, density=True)

    # Вычисление параметров для гауссовского распределения
    mu, std = norm.fit(peak_times)

    # Создание значений для гауссовского распределения
    x_gauss = np.linspace(min(peak_times), max(peak_times), 100)
    gauss_curve = norm.pdf(x_gauss, mu, std)
    gauss_curve_scaled = gauss_curve * np.max(hist) / np.max(gauss_curve)

    # Создание графика с использованием Bokeh
    p = figure(title="Peak Density and Gaussian Fit", x_axis_label='Time', y_axis_label='Density')

    # Построение гистограммы плотности пиков
    p.quad(top=hist, bottom=0, left=edges[:-1], right=edges[1:], fill_color="blue", line_color="white", alpha=0.6,
           legend_label="Density of Peaks")

    # Построение гауссовского распределения
    p.line(x_gauss, gauss_curve_scaled, line_width=2, color="red", legend_label=f"Gaussian Fit: μ={mu:.2f}, σ={std:.2f}")

    # Добавление зеленой линии на уровне 0 (нулевая линия)
    zero_line = Span(location=0, dimension='width', line_color='green', line_dash='dashed', line_width=2)
    p.add_layout(zero_line)

    # Оформление графика
    p.legend.location = "top_right"

    # Показ графика
    output_file("peak_density_gaussian.html")
    show(p)


def plot_3d(list_lfps, time):
    # Преобразование данных в numpy массив
    X = np.arange(time)
    if (len(list_lfps) == 1):
        list_lfps = np.array(list_lfps)
        channel_index = 0
        data_channel = list_lfps[channel_index]  # Значения амплитуды для выбранного канала

        # Создаем сетку координат для X
        num_time_points = data_channel.shape[0]  # Количество временных точек
        # X = np.arange(num_time_points)  # Временные точки
        Y = np.zeros(num_time_points) + channel_index  # Одна линия на уровне канала

        # Создаем Z как значения амплитуды для выбранного канала
        Z = data_channel  # Это наши значения на поверхности

        # Создание 3D Surface графика с использованием plotly
        fig = go.Figure(data=[go.Surface(z=Z[np.newaxis, :], x=X, y=Y[np.newaxis, :], colorscale='Viridis')])

        # Настройка осей
        fig.update_layout(
            title=f"3D Surface Plot of Channel {channel_index}",
            scene=dict(
                xaxis_title="Time",
                yaxis_title="Channel",
                zaxis_title="Amplitude"
            )
        )

        # Отображение с помощью panel
        pn.pane.Plotly(fig).show()
    else:
        list_lfps = np.array(list_lfps)

        # Создаем сетку координат для X и Y
        # X = np.arange(list_lfps.shape[1])  # Количество временных точек
        Y = np.arange(list_lfps.shape[0])  # Количество каналов/сигналов
        X, Y = np.meshgrid(X, Y)

        Z = list_lfps  # Это наши значения на поверхности

        # # Создание 3D Surface графика с использованием plotly
        fig = go.Figure(data=[go.Surface(z=Z, x=X, y=Y, colorscale='Viridis')])
        #
        # Настройка осей
        fig.update_layout(
            title="3D Surface Plot of LFP Data",
            scene=dict(
                xaxis_title="Time",
                yaxis_title="Channel",
                zaxis_title="Amplitude"
            )
        )

        # Отображение с помощью panel
        pn.pane.Plotly(fig).show()
    # # Настройка контуров по высоте
    # fig.update_traces(contours=dict(
    #     z=dict(show=True, usecolormap=True,
    #            highlightcolor="limegreen", project_z=True)
    # ))
    #
    # # Настройка внешнего вида графика
    # fig.update_layout(title='3D Surface Plot of LFP Data', autosize=False,
    #                   scene_camera_eye=dict(x=1.87, y=0.88, z=-0.64),
    #                   width=500, height=500,
    #                   margin=dict(l=65, r=50, b=65, t=90),
    #                   scene=dict(
    #                       xaxis_title="Time",
    #                       yaxis_title="Channel",
    #                       zaxis_title="Amplitude"
    #                   )
    #                   )
    #
    # # Отображение с помощью panel
    # pn.pane.Plotly(fig).show()


def plot_bokeh_3d(list_lfps, time, start, end, sigma=1.5):
    # Параметры
    n_channels = len(list_lfps)
    time_bins = np.linspace(np.min(time), np.max(time), 100)  # Разбиение времени на 100 интервалов

    # Матрица для хранения данных плотности (ось X - время, ось Y - каналы, Z - амплитуды)
    #density_matrix = np.zeros((len(time_bins), n_channels))
    density_matrix = np.zeros((n_channels, len(time_bins)))

    # Обработка каждого канала
    for channel in range(n_channels):
        # Данные для текущего канала
        channel_data = np.array(list_lfps[channel][start: end])

        # Нахождение пиков
        peaks, _ = find_peaks(channel_data, height=0)

        # Извлечение времени и амплитуд пиков
        peak_times = np.array(time)[peaks]
        peak_amplitudes = channel_data[peaks]

        # Сглаживание и распределение по bins
        for i, peak_time in enumerate(peak_times):
            # Нахождение соответствующего bin для времени
            # time_idx = np.digitize(peak_time, time_bins) - 1
            time_idx = np.digitize(peak_time, time_bins) - 1
            if 0 <= time_idx < len(time_bins):  # Проверка индекса
                #density_matrix[time_idx, channel] += peak_amplitudes[i]
                density_matrix[channel, time_idx] += peak_amplitudes[i]

    density_matrix_smooth = gaussian_filter(density_matrix, sigma=sigma)
    # Создание сетки для графика
    # X, Y = np.meshgrid( np.arange(1, n_channels + 1), time_bins) #time_binds
    X, Y = np.meshgrid( time_bins, np.arange(1, n_channels + 1))
    # Построение 3D-графика с плотностью
    fig = go.Figure(data=[go.Surface(z=density_matrix_smooth, x=X, y=Y, colorscale='Viridis')])
    pio.write_html(fig, file='3d_peak_density.html', auto_open=True)

    # Настройка осей
    fig.update_layout(
        title="3D Peak Density across Channels",
        scene=dict(
            xaxis_title='Time',
            yaxis_title='Channel',
            zaxis_title='Amplitude',
            # zaxis=dict(nticks=5),
            # yaxis=dict(range=[0, 2000])
        )
    )

    # Показ графика
    fig.show()

if __name__ == '__main__':
    # Путь к вашему .mat файлу
    file_path = 'files/2024-07-11_16-58-25.analysis.mat'

    # Чтение .mat файла
    mat_contents = scipy.io.loadmat(file_path)
    # Инициализация panel для вывода в Jupyter Notebook
    pn.extension('plotly')
    # Извлечение данных
    lfp_data = mat_contents['lfpAnalys']
    time_data = mat_contents['sounds']

    list_lfps = [[] for _ in range(17)]
    time_1s = []
    time_5s = []
    time_10s = []
    for lfp in lfp_data:
        for i, l in enumerate(lfp):
            list_lfps[i].append(np.mean(l))

    start_1, start_5, start_10 = 0, 0, 0
    for i, t in enumerate(time_data):
        if 500 < t[0] < 1300: #10ms
            if len(time_1s) == 0:
                start_1 = i
            time_1s.append(t[0])
        elif 18000 < t[0] < 27000: #25ms
            if len(time_5s) == 0:
                start_5 = i
            time_5s.append(t[0])
        elif 45000 < t[0] < 55000: #50ms
            if len(time_10s) == 0:
                start_10 = i
            time_10s.append(t[0])
        elif t[0] > 1400:
            break

    # plot_picks(list_lfps[10][start_1:start_1 + len(time_1s)], time_1s)
    # plot_picks_2(list_lfps[10][start_1:start_1 + len(time_1s)], time_1s)
    plot_bokeh_3d(list_lfps[:15], time_1s, start_1, start_1 + len(time_1s), 4)
    # plot_picks(list_lfps[10][start_5:start_5 + len(time_5s)], time_5s)
    # plot_picks_2(list_lfps[10][start_5:start_5 + len(time_5s)], time_5s)
    # plot_bokeh_3d(list_lfps[:15], time_5s, start_5, start_5 + len(time_5s), 4)
    # plot_picks(list_lfps[10][start_10:start_10 + len(time_10s)], time_10s)
    # plot_picks_2(list_lfps[10][start_10:start_10 + len(time_10s)], time_10s)
    # plot_bokeh_3d(list_lfps[:15], time_10s, start_10, start_10 + len(time_10s), 4)
    # plot_picks_2(list_lfps[2][start_10:start_10 + len(time_10s)], time_10s)
    # plot_bokeh_3d(list_lfps, time_10s, start_10, start_10 + len(time_10s))
    # plot_3d(list_lfps[:10], time)
