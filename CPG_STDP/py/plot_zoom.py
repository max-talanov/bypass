import fnmatch
import os

import sys

import bokeh

import h5py

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show

sys.path.append('last_r/')
my_path = os.path.abspath('last_r/')

themes = 'light_minimal'


def read():
    volt_data = []
    data_time = []

    for file in fnmatch.filter(os.listdir(my_path), '*.hdf5'):
        with h5py.File(my_path+f'\\{file}') as f:
            name = f.filename.split('\\')[-1]
            if name == 'time.hdf5':
                time_group = list(f.keys())[0]
                data_y = list(f[time_group])
                data_time.append(data_y)
            else:
                vol_group = list(f.keys())[0]
                data_y = list(f[vol_group])
                volt_data.append((name, data_y))


    #
    with open(my_path + '/time.txt', 'r', encoding='utf-8') as fh:
        for line in fh:
            line = line.rstrip('\n\r')
            data_time.append(float(line))
    return volt_data, data_time



def draw(volt_data, data_time):

    for v in volt_data:
        figur = figure(x_axis_label='time (ms)', y_axis_label='weight')
        output_file(my_path + '/results/' + v[0] + '.html')
        figur.line(data_time[:len(v[1])], v[1], line_width=2)
        show(figur)



if __name__ == '__main__':
    volt_data, data_time = read()
    draw(volt_data, data_time)

