import fnmatch
import itertools
import os
import re
import sys

import h5py
import numpy as np

from bokeh.plotting import figure, output_file, save


paths = ("res/")
sys.path.append(paths)
my_path = os.path.abspath(paths)


MAX_POINTS = 10000


def natural_key(text):
    return [int(c) if c.isdigit() else c.lower() for c in re.split(r"(\d+)", text)]


def decimate(x, y, max_points=MAX_POINTS):
    n = min(len(x), len(y))

    if n == 0:
        return [], []

    x = x[:n]
    y = y[:n]

    step = max(1, n // max_points)

    return x[::step], y[::step]


def read_time():
    time_txt_path = os.path.join(my_path, "time.txt")

    if not os.path.exists(time_txt_path):
        raise FileNotFoundError(f"Не найден файл времени: {time_txt_path}")

    data_time = []

    with open(time_txt_path, "r", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                data_time.append(float(line))

    return data_time


def read_hdf5_file(file_path):
    with h5py.File(file_path, "r") as f:
        keys = sorted(list(f.keys()), key=natural_key)

        values = []
        for key in keys:
            arr = np.array(f[key], dtype=float).squeeze()
            if arr.ndim != 1:
                arr = arr.reshape(-1)
            values.extend(arr.tolist())

    return values


def read():
    volt_data = []
    data_time = read_time()

    for file in sorted(fnmatch.filter(os.listdir(my_path), "*.hdf5"), key=natural_key):
        if file == "time.hdf5":
            continue

        file_path = os.path.join(my_path, file)
        values = read_hdf5_file(file_path)

        volt_data.append((file, values))

    return volt_data, data_time


def draw(volt_data, data_time):
    results_dir = os.path.join(my_path, "results_bokeh")
    os.makedirs(results_dir, exist_ok=True)

    for name, values in volt_data:
        x, y = decimate(data_time, values)

        if len(x) == 0:
            print(f"Пропущен пустой файл: {name}")
            continue

        p = figure(
            title=name,
            x_axis_label="time (ms)",
            y_axis_label="V (mV)",
            width=1200,
            height=500,
            output_backend="webgl",
        )

        p.line(x, y, line_width=1)

        html_path = os.path.join(results_dir, name + ".html")
        output_file(html_path)
        save(p)

        print(f"Сохранено: {html_path}")


if __name__ == "__main__":
    volt_data, data_time = read()
    draw(volt_data, data_time)