import fnmatch
import os

import sys

import bokeh
import numpy as np
from bokeh.models import ColumnDataSource, Label, LabelSet
import math
from bokeh.io import export_png

import h5py

bokeh.sampledata.download()
directory_path = '.'

from bokeh.plotting import figure, output_file, show

sys.path.append('res_weight/')
my_path = os.path.abspath('res_weight/')

themes = 'light_minimal'
# Исходные данные
data = [
    [26000, 28, 'TrueNorth'],
    [23000, 14, 'Loihi'],
    [400, 130, 'Mosaic'],
    [2000, 20000, 'PANI'],
    [100, 50, 'Bio neurons'],
    [31657429.80, 8, 'NVidia RTX 3080 (ResNet101)'],
    [34625313.84, 8, 'NVidia RTX 3090 (ResNet101)'],
    [7062258.58, 8, 'NVidia RTX 3080 (LSTM)'],
    [7650780.13, 8, 'NVidia RTX 3090 (LSTM)'],
    [113863064.82, 7, 'AMD Ryzen 5 4500U (ResNet50)'],
    [6059936607.16, 7, 'AMD Ryzen 5 4500U (Custom Transformer)']
]

data_2 = [
    [26000, 28, 'TrueNorth'],
    [23000, 14, 'Loihi'],
    [400, 130, 'Mosaic'],
    [2000, 20000, 'PANI'],
    [100, 50, 'Bio neurons'],
    [113863064.82, 7, 'AMD Ryzen 5 4500U (ResNet50)'],
    [6059936607.16, 7, 'AMD Ryzen 5 4500U (Custom Transformer)']
]

# data_x_log = [math.log(d[1]) for d in data]
# data_y_log = [math.log(d[0]) for d in data]
# data_label = [d[2] for d in data]

data_x_log = [d[1] for d in data]
data_y_log = [d[0] for d in data]
data_label = [d[2] for d in data]

data_x_log_2 = [d[1] for d in data_2]
data_y_log_2 = [d[0] for d in data_2]
colors = ['#8B0000', '#FF0000', '#FF4500', '#FF8C00', '#FFD700', '#191970',
          '#0000FF', '#4B0082', '#1E90FF', '#87CEFA', '#00CED1']

# Создаем фигуру
figur = figure(width=900, height=400, y_axis_label='Energy per synaptic event [fJ]',
               y_axis_type="log",
               x_axis_type="log",
               x_axis_label='Technology [nm]')

# Настройка стилей осей и меток
figur.xaxis.axis_label_text_font_style = "bold"
figur.yaxis.axis_label_text_font_style = "bold"
figur.xaxis.major_label_text_font_style = "bold"
figur.yaxis.major_label_text_font_style = "bold"

# Источник данных
source = ColumnDataSource(data=dict(
    x=data_x_log,
    y=data_y_log,
    label=data_label,
    colors=colors  # Добавляем цвета в ColumnDataSource
))

# Добавление точек на график
figur.scatter('x', 'y', color='colors', size=10, source=source, legend_field='label') #legend_field='label'

data_label_2 = [
    '(28; 26000)',
    '(14; 23000)',
    '(130; 400)',
    '(20000; 2000)',
    '(50; 100)',
    '(8; 31,657,429.80)',
    '(8; 34,625,313.84)',
    '(8; 7,062,258.58)',
    '(8; 7,650,780.13)',
    '(7; 113,863,064.82)',
    '(7; 6,059,936,607.16)',
]
data_label_3 = [
    '(28; 26000)',
    '(14; 23000)',
    '(130; 400)',
    '(20000; 2000)',
    '(50; 100)',
    '(7; 113,863,064.82)',
    '(7; 6,059,936,607.16)',
]
# data_label_3 = [f"({(d[1]):.2f}, {(d[0]):.2f})" for d in data_2]
x_off = [5, 5, 5, -10, 5, 5, 5, 5, 5, 25, 25]
y_off = [8, 8, 8, -18, 8, -18, 8, -18, 8, 8, -18]

x_off_2 = [5, 5, 5, -10, 5, 25, 25]
y_off_2 = [8, 8, 8, -18, 8, 8, -18]

source_2 = ColumnDataSource(data=dict(
    x=data_x_log,
    y=data_y_log,
    label=data_label_2,
    x_offset=x_off,
    y_offset=y_off,
))

source_3 = ColumnDataSource(data=dict(
    x=data_x_log_2,
    y=data_y_log_2,
    label=data_label_3,
    x_offset=x_off_2,
    y_offset=y_off_2,
))
# Создание и добавление меток с координатами к точкам
# labels = LabelSet(x='x', y='y', text='labels', level='glyph',
#                   x_offset=5, y_offset=5, source=source_2, render_mode='canvas')
labels = LabelSet(x='x', y='y', text='label',
                  x_offset='x_offset', y_offset='y_offset', text_font_size="8pt", text_color="black",
                  source=source_2, text_align='center',
                  text_font_style="bold"
                  )
figur.add_layout(labels)

# Настройка и отображение легенды
figur.legend.label_text_font_style = "bold"

output_file('Energy_per_synaptic_event.html')
show(figur)
