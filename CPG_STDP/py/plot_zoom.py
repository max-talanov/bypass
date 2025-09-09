import fnmatch
import itertools
import os

import sys

import bokeh

import h5py
import numpy as np

# bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show
from bokeh.io import export_png

paths = '2025-09-08/'
sys.path.append(paths)
my_path = os.path.abspath(paths)

themes = 'light_minimal'


def read():
    volt_data = []
    data_time = []

    for file in fnmatch.filter(os.listdir(my_path), '*.hdf5'):
        with h5py.File(my_path + f'/{file}') as f:
            name = f.filename.split('/')[-1]
            if name == 'time.hdf5':
                time_group = list(f.keys())[0]
                data_y = list(f[time_group])
                data_time.append(data_y)
            else:
                vol_group = [list(val) for val in f.values()]
                flat_list = list(itertools.chain.from_iterable(vol_group))
                volt_data.append((name, flat_list[1:]))

    #
    with open(my_path + '/time.txt', 'r', encoding='utf-8') as fh:
        for line in fh:
            line = line.rstrip('\n\r')
            data_time.append(float(line))
    return volt_data, data_time


def draw(volt_data, data_time):
    # Создаем папки если их нет
    results_dir = os.path.join(my_path, 'results')
    images_dir = os.path.join(my_path, 'images')

    os.makedirs(results_dir, exist_ok=True)
    os.makedirs(images_dir, exist_ok=True)

    for v in volt_data:
        figur = figure(x_axis_label='time (ms)', y_axis_label='V (mV)')

        # Сохраняем HTML
        output_file(os.path.join(results_dir, v[0] + '.html'))
        figur.line(data_time[:len(v[1])], v[1], line_width=2)
        show(figur)

        # Сохраняем PNG
        filename_without_ext = os.path.splitext(v[0])[0]
        png_path = os.path.join(images_dir, filename_without_ext + '.png')
        export_png(figur, filename=png_path)


if __name__ == '__main__':
    volt_data, data_time = read()
    draw(volt_data, data_time)