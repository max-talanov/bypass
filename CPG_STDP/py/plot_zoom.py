import fnmatch
import os
import re

import h5py
import matplotlib.pyplot as plt
import numpy as np


DATA_DIR = "res_19_05"

MAX_POINTS = 10000

X_TICKS_FROM = 0
X_TICKS_TO = 7000
X_TICK_STEP = 1000
X_LIMIT_LEFT = -50
X_LIMIT_RIGHT = 7300


def natural_key(text):
    return [int(c) if c.isdigit() else c.lower() for c in re.split(r"(\d+)", text)]


def short_name(filename):
    name = filename.replace(".hdf5", "")
    name = name.replace("_sp_100_CVs_6_bs_100_right", "")
    name = name.replace("_sp_100_CVs_6_bs_100_left", "")
    return name


def get_side(filename):
    if filename.endswith("_right.hdf5"):
        return "right"
    if filename.endswith("_left.hdf5"):
        return "left"
    return None


def read_time(data_dir):
    time_path = os.path.join(data_dir, "time.txt")

    if not os.path.exists(time_path):
        raise FileNotFoundError(f"Не найден файл времени: {time_path}")

    time = np.loadtxt(time_path, dtype=float).reshape(-1)

    if len(time) > 0 and time[-1] < 100:
        time = time * 1000

    return time


def read_hdf5_file(file_path):

    arrays = []

    with h5py.File(file_path, "r") as f:
        keys = sorted(list(f.keys()), key=natural_key)

        for key in keys:
            arr = np.array(f[key], dtype=float).squeeze().reshape(-1)
            arrays.append(arr)

    if len(arrays) == 0:
        return np.array([])

    return np.concatenate(arrays)


def get_first_time_block(values, time_len):
    if len(values) == 0:
        return np.array([])

    return values[:time_len]


def decimate(x, y, max_points=MAX_POINTS):
    n = min(len(x), len(y))

    if n == 0:
        return np.array([]), np.array([])

    x = x[:n]
    y = y[:n]

    step = max(1, n // max_points)

    return x[::step], y[::step]


def read_all_signals(data_dir):
    time = read_time(data_dir)

    signals = {
        "right": [],
        "left": [],
    }

    files = sorted(
        fnmatch.filter(os.listdir(data_dir), "*.hdf5"),
        key=natural_key
    )

    for filename in files:
        if filename == "time.hdf5":
            continue

        side = get_side(filename)

        if side is None:
            continue

        file_path = os.path.join(data_dir, filename)
        values = read_hdf5_file(file_path)

        y = get_first_time_block(values, len(time))
        n = min(len(time), len(y))

        if n == 0:
            print(f"Пропущен пустой файл: {filename}")
            continue

        x = time[:n]
        y = y[:n]

        signals[side].append({
            "filename": filename,
            "name": short_name(filename),
            "x": x,
            "y": y,
        })

        print(
            f"{filename}: side={side}, "
            f"time={len(time)}, values={len(values)}, used={n}"
        )

    return signals, time


def setup_x_axis(ax):
    ax.set_xticks(np.arange(X_TICKS_FROM, X_TICKS_TO + 1, X_TICK_STEP))
    ax.set_xlim(X_LIMIT_LEFT, X_LIMIT_RIGHT)
    ax.grid(True, alpha=0.25)


def draw_single_plots(signals, results_dir):
    for side, side_signals in signals.items():
        side_dir = os.path.join(results_dir, side)
        os.makedirs(side_dir, exist_ok=True)

        for item in side_signals:
            filename = item["filename"]
            x = item["x"]
            y = item["y"]

            x_plot, y_plot = decimate(x, y)

            plt.figure(figsize=(15, 4))
            plt.plot(x_plot, y_plot, linewidth=1)

            plt.title(filename)
            plt.xlabel("time (ms)")
            plt.ylabel("value")

            ax = plt.gca()
            setup_x_axis(ax)

            png_name = filename.replace(".hdf5", ".png")
            png_path = os.path.join(side_dir, png_name)

            plt.savefig(png_path, dpi=150, bbox_inches="tight")
            plt.close()

            print(f"Сохранено отдельное фото: {png_path}")


def draw_overview_for_side(side, side_signals, results_dir):
    if len(side_signals) == 0:
        print(f"Нет данных для {side}")
        return

    n = len(side_signals)

    fig_height = max(10, n * 0.32)

    fig, ax = plt.subplots(figsize=(16, fig_height))

    color_cycle = plt.rcParams["axes.prop_cycle"].by_key()["color"]

    yticks = []
    ylabels = []

    for i, item in enumerate(side_signals):
        x = item["x"]
        y = item["y"]

        x_plot, y_plot = decimate(x, y)

        y_min = np.nanmin(y_plot)
        y_max = np.nanmax(y_plot)

        if y_max > y_min:
            y_norm = (y_plot - y_min) / (y_max - y_min)
        else:
            y_norm = np.zeros_like(y_plot)

        offset = n - 1 - i
        amplitude = 0.75

        y_overview = offset + y_norm * amplitude

        color = color_cycle[i % len(color_cycle)]

        ax.plot(
            x_plot,
            y_overview,
            linewidth=0.8,
            color=color
        )

        yticks.append(offset + amplitude / 2)
        ylabels.append(item["name"])

    ax.set_yticks(yticks)
    ax.set_yticklabels(ylabels, fontsize=7)

    ax.set_xlabel("t (ms)")
    ax.set_title(f"Full overview — {side} leg, n={n}")

    setup_x_axis(ax)

    ax.set_ylim(-0.5, n + 0.5)

    overview_path = os.path.join(results_dir, f"overview_{side}.png")

    plt.savefig(overview_path, dpi=200, bbox_inches="tight")
    plt.close()

    print(f"Сохранено overview: {overview_path}")


def draw_overviews(signals, results_dir):
    draw_overview_for_side("right", signals["right"], results_dir)
    draw_overview_for_side("left", signals["left"], results_dir)


def main():
    data_dir = os.path.abspath(DATA_DIR)
    results_dir = os.path.join(data_dir, "results_matplotlib")
    os.makedirs(results_dir, exist_ok=True)

    print(f"Папка с данными: {data_dir}")
    print(f"Папка результатов: {results_dir}")

    signals, time = read_all_signals(data_dir)

    print(f"time.txt: {len(time)} точек")
    if len(time) > 0:
        print(f"Диапазон времени: {time[0]} .. {time[-1]} ms")

    print(f"right signals: {len(signals['right'])}")
    print(f"left signals: {len(signals['left'])}")

    draw_single_plots(signals, results_dir)
    draw_overviews(signals, results_dir)


if __name__ == "__main__":
    main()