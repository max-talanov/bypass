import os
import re

import h5py
import numpy as np
import matplotlib.pyplot as plt


BASE_DIR = os.path.dirname(os.path.abspath(__file__))
RES_DIR = os.path.join(BASE_DIR, "res")
OUT_DIR = os.path.join(RES_DIR, "images_manual")

os.makedirs(OUT_DIR, exist_ok=True)


def natural_key(text):
    return [int(c) if c.isdigit() else c.lower() for c in re.split(r'(\d+)', text)]


def read_time():
    time_path = os.path.join(RES_DIR, "time.txt")
    if not os.path.exists(time_path):
        raise FileNotFoundError(f"Не найден файл времени: {time_path}")

    with open(time_path, "r", encoding="utf-8") as f:
        return np.array([float(line.strip()) for line in f if line.strip()], dtype=float)


def read_concat_hdf5(file_path):
    """
    Читает все датасеты из hdf5 и склеивает их подряд:
    step_0 + step_1 + step_2 + ...
    """
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Не найден файл: {file_path}")

    with h5py.File(file_path, "r") as f:
        keys = sorted(list(f.keys()), key=natural_key)

        if not keys:
            raise ValueError(f"В файле нет датасетов: {file_path}")

        arrays = []
        for key in keys:
            arr = np.array(f[key], dtype=float).squeeze()
            if arr.ndim != 1:
                arr = arr.reshape(-1)
            arrays.append(arr)

    full_signal = np.concatenate(arrays)
    return full_signal


def make_concat_time(base_time, n_steps):
    """
    Если один step имеет свою временную сетку base_time,
    то строим общую ось времени для склеенного сигнала
    """
    if len(base_time) < 2:
        return np.arange(len(base_time) * n_steps)

    dt = base_time[1] - base_time[0]
    step_duration = len(base_time) * dt

    parts = []
    for i in range(n_steps):
        parts.append(base_time + i * step_duration)

    return np.concatenate(parts)


def read_num_steps(file_path):
    with h5py.File(file_path, "r") as f:
        return len(f.keys())


def plot_pair(time, e_file, f_file, title, ylabel="V (mV)", out_name="result.png", use_real_time=False):
    e_path = os.path.join(RES_DIR, e_file)
    f_path = os.path.join(RES_DIR, f_file)

    y_e = read_concat_hdf5(e_path)
    y_f = read_concat_hdf5(f_path)

    if use_real_time:
        n_steps_e = read_num_steps(e_path)
        n_steps_f = read_num_steps(f_path)

        x_e = make_concat_time(time, n_steps_e)
        x_f = make_concat_time(time, n_steps_f)
    else:
        x_e = np.arange(len(y_e))
        x_f = np.arange(len(y_f))

    print("E file:", e_file, "len =", len(y_e))
    print("F file:", f_file, "len =", len(y_f))
    print("Base time len:", len(time))

    fig, axes = plt.subplots(2, 1, figsize=(14, 8), sharex=False)

    axes[0].plot(x_e, y_e, linewidth=1.0)
    axes[0].set_title(e_file, fontsize=11)
    axes[0].set_ylabel(ylabel)
    axes[0].grid(True, alpha=0.3)

    axes[1].plot(x_f, y_f, linewidth=1.0)
    axes[1].set_title(f_file, fontsize=11)
    axes[1].set_ylabel(ylabel)
    axes[1].grid(True, alpha=0.3)

    if use_real_time:
        axes[1].set_xlabel("time (ms)")
    else:
        axes[1].set_xlabel("sample index")

    fig.suptitle(title, fontsize=14)
    fig.tight_layout(rect=[0, 0, 1, 0.97])

    out_path = os.path.join(OUT_DIR, out_name)
    fig.savefig(out_path, dpi=200)
    plt.show()
    plt.close(fig)

    print(f"График сохранён: {out_path}")


def main():
    print("RES_DIR:", RES_DIR)
    print("FILES IN RES:", os.listdir(RES_DIR))

    time = read_time()

    plot_pair(
        time,
        "muscle_E_sp_100_CVs_6_bs_100_left.hdf5",
        "muscle_F_sp_100_CVs_6_bs_100_left.hdf5",
        "HDF5 signals",
        ylabel="Value",
        out_name="figure_muscle_left_concat.png",
        use_real_time=False
    )


if __name__ == "__main__":
    main()