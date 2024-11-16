import os
import sys

import matplotlib.pyplot as plt
from bokeh.io import output_notebook, show, output_file
import bokeh
from bokeh.plotting import figure
from bokeh.models import ColumnDataSource
from bokeh.transform import jitter
import numpy as np
import pandas as pd
import holoviews as hv
import hvplot.pandas
from sklearn.preprocessing import MinMaxScaler, StandardScaler

bokeh.sampledata.download()
directory_path = '.'
# Ensure the output is displayed in the notebook
output_notebook()


def mat_boxplot(data):
    # Массив с названиями устройств
    device_names = ["LSTM_IMDB_GPU_A100", "LSTM_IMDB_GPU_RTX_3050", "RESNET18_MNIST_GPU_A100",
                    "RESNET18_MNIST_GPU_RTX_3050", "RESNET18_MNIST_NPU_910A", "TRANSFORMER_IMDB_GPU_A100",
                    "TRANSFORMER_IMDB_GPU_RTX_3050", "TRANSFORMER_IMDB_NPU_910A"]

    # Настройка цветов для каждого бокс-плота
    colors = ['skyblue', 'lightgreen', 'lightcoral', 'lightsalmon', 'lightpink', 'lightyellow', 'lightcyan', 'lavender']
    plt.figure(figsize=(8, 6))

    # Создание бокс-плотов
    box = plt.boxplot(data, patch_artist=True)

    # Применение цветов к каждому бокс-плоту
    for patch, color in zip(box['boxes'], colors):
        patch.set_facecolor(color)

    # Настройка графика
    plt.xlabel("Устройства")
    plt.ylabel("Значения")
    plt.title("Бокс-плоты для каждого устройства")
    plt.xticks(range(1, len(data) + 1), device_names)

    # Сохранение изображения
    plt.savefig("boxplots.png", dpi=300)

    # Отображение графика
    plt.show()


def bokeh_boxplot(data, device_names, file_name):
    # Преобразуем данные для создания датафрейма
    hv.extension("bokeh")
    df = pd.DataFrame(data, index=device_names).T.melt(var_name='Device', value_name='Power Consumption (W)')

    # Создаем бокс-плот с помощью hvplot, который автоматически включает интерактивность
    boxplot = df.hvplot.box(y='Power Consumption (W)', by='Device', width=800, height=400,
                            title='Energy consumption')

    # Отображаем интерактивный график
    # Отображение графика
    # output_file('boxplot.html')
    hvplot.save(boxplot, file_name)




if __name__ == "__main__":
    # Данные по устройствам
    data = [
        [15.82764706, 15.9386445, 15.22846547, 15.46598465, 15.50529412],
        [10.91081841, 9.944245524, 10.92117647, 12.27038363, 12.45347826],
        [42.32908316, 33.41695096, 37.97474414, 34.87882729, 34.93358209],
        [67.2730064, 67.48302772, 67.62691898, 67.61004264, 67.64015991],
        [1.864712154, 2.713646055, 3.69978678, 1.705223881, 2.013006397],
        [1.241074169, 1.363248082, 1.697851662, 1.023299233, 1.512608696],
        [35.96381074, 35.10849105, 34.8401023, 33.6081681, 32.12324808],
        [1.14, 1.31, 1.41, 1.75, 1.59]
        # Добавьте больше данных, если нужно
    ]
    # data_array = np.array(data)
    #
    # # Применение нормализации
    # scaler = MinMaxScaler()
    # data_normalized = scaler.fit_transform(data_array)
    #
    # # Применение стандартизации
    # scaler = StandardScaler()
    # data_standardized = scaler.fit_transform(data_array)

    device_names = ["LSTM_A100", "LSTM_RTX_3050", "RESNET18_A100",
                    "RESNET18_RTX_3050", "RESNET18_NPU_910A", "TRANSFORMER_A100",
                    "TRANSFORMER_RTX_3050", "TRANSFORMER_NPU_910A"]

    # mat_boxplot(data)
    bokeh_boxplot(data, device_names, 'box_plot.html')
    # bokeh_boxplot(data_normalized, device_names, 'norm_box_plot.html')
    # bokeh_boxplot(data_standardized, device_names, 'stand_box_plot.html')