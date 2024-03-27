import ast
import csv
import fnmatch
import os

import sys

import bokeh

import h5py
import numpy as np

bokeh.sampledata.download()

from bokeh.plotting import figure, output_file, show

sys.path.append('../../')
my_path = os.path.abspath('')

themes = 'light_minimal'
directory_path = './res_calc_spike/res/'


def read_ik_ina():
    volt_data = {}
    data_time = []
    ina = {}
    ik = {}
    il = {}

    for file in fnmatch.filter(os.listdir(directory_path), '' + '*.hdf5'):
        file_path = os.path.join(directory_path, file)
        try:
            with h5py.File(file_path) as f:
                name = file
                all_data = []
                for i in f:
                    all_data.extend(np.array(f[i]))
                all_data = np.array(all_data)
                if name == 'time.hdf5':
                    data_time.append(all_data)
                else:
                    name_1 = name.split('_')[-1]
                    name = file.split('_')[:-2]
                    name = ("_").join(name)
                    if name_1 == 'ina.hdf5':
                        ina[name] = all_data
                    elif name_1 == 'ik.hdf5':
                        ik[name] = all_data
                    elif name_1 == 'il.hdf5':
                        il[name] = all_data
                    elif name_1 == 'voltage.hdf5':
                        volt_data[name] = all_data

        except Exception as e:
            # Если возникает ошибка при открытии файла, выводим сообщение об ошибке
            print(f"Error opening {file}: {e}")

    return volt_data, data_time, ina, ik, il


def read():
    volt_data = {}
    data_time = []
    names = set()
    names_2 = set()
    directory_path = './res/'
    for file in fnmatch.filter(os.listdir(directory_path), '' + '*.hdf5'):
        file_path = os.path.join(directory_path, file)
        try:
            with h5py.File(file_path) as f:
                name = file
                if name == 'time.hdf5':
                    name = file
                else:
                    name = file.split('_')[:-2]
                    name = ("_").join(name)
                    if name in names:
                        if name in names_2:
                            continue
                        else:
                            names_2.add(name)
                    else:
                        names.add(name)
                all_data = []
                for i in f:
                    all_data.extend(np.array(f[i]))
                all_data = np.array(all_data)
                if name == 'time.hdf5':
                    data_time.append(all_data)
                else:
                    volt_data[name] = all_data
        except Exception as e:
            # Если возникает ошибка при открытии файла, выводим сообщение об ошибке
            print(f"Error opening {file}: {e}")

    return volt_data, data_time


def read_csv(volt_data, data_time, ina, ik, il):
    names = set()
    with open(f'{directory_path}data.csv', 'r', newline='') as csvfile:
        reader = csv.reader(csvfile)

        for i, row in enumerate(reader):
            if i == 0:
                continue
            if len(list(row[5])) != 0:
                name = f'{row[0]}_{row[1]}'
                if name in names:
                    continue
                else:
                    names.add(name)

                figur = figure(x_axis_label='time (ms)', y_axis_label='V (mV)')
                output_file(directory_path + 'results/' + name + '_calc_spike.html')
                figur.line(data_time[0], volt_data.get(name), line_width=2, legend_label=f'{row[1]}')
                figur.line(data_time[0], ina.get(name), line_width=2, color='red', legend_label=f'ina')
                figur.line(data_time[0], ik.get(name), line_width=2, color='green', legend_label=f'ik')
                figur.line(data_time[0], il.get(name), line_width=2, line_color="#f46d43", legend_label=f'il')

                # if len(row[5]) != 0:
                # x_points = [round(x, 5) for x in ast.literal_eval(row[7])]
                # data = [round(y, 5) for y in data_time[0]]
                # y_points = [list(volt_data.get(name))[data.index(x)] for x in x_points]
                # colors = ["red", "green"]
                # weight = float(row[2])
                # e_syn = float(row[3])
                #
                # for x, y in zip(x_points, y_points):
                #     amperage = weight * (e_syn - y)
                #     power = amperage * (-y)
                #     figur.circle(x, y, size=10, color=colors[0], legend_label=f'P = {power} aW')

                show(figur)


def calk_energy(volt_data, data_time, ina, ik, il):
    '''
    Calculate energy
    Parameters
    ----------
    volt_data - mV
    data_time - mS
    ina - mA/cm^2
    ik - mA/cm^2
    il - mA/cm^2

    Returns
    -------
    e = mV*mS*mA/cm^2
    '''
    name = 'Ia_aff_E_Ia_E'
    energy_s = 0
    i = 0
    t_start = 0
    t_finish = 0
    for v, t, i_ina, i_ik, i_il in zip (volt_data[name], data_time[0], ina[name], ik[name], il[name]):
        if v < -60 and i == 1:
            t_finish = t
            print(f'time: {t}')
            break
        if v > -60:
            if i == 0:
                t_start = t
                print(f'time: {t}')
            i = 1
            tok = i_ina + i_ik + i_il
            energy = abs(tok * v)
            energy_s += energy
    e = (t_finish - t_start) * energy_s

    print(e)





if __name__ == '__main__':
    volt_data, data_time, ina, ik, il = read_ik_ina()
    # read_csv(volt_data, data_time, ina, ik, il)
    calk_energy(volt_data, data_time, ina, ik, il)
