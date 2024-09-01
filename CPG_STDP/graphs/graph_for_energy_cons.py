import fnmatch
import os

import sys

import bokeh
import numpy as np
from bokeh.models import ColumnDataSource, Label, LabelSet, Plot, Circle, FactorRange
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
    [0.36 * 10**(-15), 20, "ST"],
    [2.08 * 10**(-15), 20, "ST"],
    [0.29 * 10**(-15), 20, "ST"],
    [1.28 * 10**(-15), 20, "ST"],
    [98.71 * 10**(-15), 20, "ST"],
    [9 * 10**(-15), 120, "FET"],
    [93.1 * 10**(-18), 120, "FET"],
    [48 * 10**(-18), 120, "FET"],
    [230 * 10**(-15), 120, "FET"],
    [0.99 * 10**(-15), 120, "FET"],
    [0.215 * 10**(-18), 170, "QUANTUM"],
    [0.16 * 10**(-18), 170, "QUANTUM"],
    [0.036 * 10**(-15), 170, "QUANTUM"],
    [0.029 * 10**(-15), 170, "QUANTUM"],
    [250 * 10**(-18), 170, "QUANTUM"],
    [0.18 * 10**(-15), 170, "QUANTUM"],
    [75 * 10**(-18), 170, "QUANTUM"],
    [15 * 10**(-15), 120, "FET"],
    [1 * 10**(-15), 20, "ST"],
    [0.0675 * 10**(-18), 20, "ST"],
    [1.37 * 10**(-12), 70,  "BJT"],
    [2.4 * 10**(-15), 70, "BJT"],
    [39.56 * 10**(-15), 250, 'ORGANIC'],
    [10.48 * 10**(-18), 300, 'NON-VOLATILE'],
    [25 * 10**(-15), 250, 'ORGANIC'],
    [0.7 * 10**(-15), 250, 'ORGANIC'],
    [6 * 10**(-15), 250, 'ORGANIC'],
    [4.05 * 10**(-12), 250, 'ORGANIC'],
    [0.35 * 10**(-15), 250, 'ORGANIC'],
    [170 * 10**(-15), 300, 'NON-VOLATILE'],
    [3.76 * 10**(-12), 350, 'VOLATILE'],
    [4.1 * 10**(-12), 300, 'NON-VOLATILE'],
    [8.5 * 10**(-15), 300, 'NON-VOLATILE'],
    [198 * 10**(-15), 300, 'NON-VOLATILE'],
    [1.8 * 10**(-12), 300, 'NON-VOLATILE'],
    [1.15 * 10**(-12), 300, 'NON-VOLATILE'],
    [0.1 * 10**(-12), 350, 'VOLATILE'],
    [1 * 10**(-15), 350, 'VOLATILE'],
    [1.9 * 10**(-15), 350, 'VOLATILE'],
    [32.65 * 10**(-15), 350, 'VOLATILE']
]


data_x_log = [d[2] for d in data]
data_y_log = [d[0] for d in data]
# Создаем фигуру
figur = figure(width=900, x_range=sorted(set(data_x_log), key=data_x_log.index), height=400, y_axis_type="log") #x_range=data_x_log

figur.xaxis.major_label_orientation = 'horizontal'
# Добавление точек на график
figur.scatter(data_x_log, data_y_log, size=15, color=None, line_color="black", line_width=2) #legend_field='label' color='colors',, line_color="black", line_width=2

output_file('Energy.html')
show(figur)
