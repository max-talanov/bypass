import os
import h5py
import matplotlib.pyplot as plt
import numpy as np


def show_one(ax, path, name):
    with h5py.File(path, 'r') as file:
        all_data = []
        for i in file:
            all_data.extend(np.array(file[i]))
        all_data = np.array(all_data)

        ax.plot(all_data)
        ax.set_title(name)


def show_all(path, file_names=None):
    file_entries = [entry for entry in os.scandir(path) if file_names is None or entry.name in file_names]
    num_files = len(file_entries)
    rows = int(np.ceil(np.sqrt(num_files)))
    cols = int(np.ceil(num_files / rows))

    # fig = plt.figure()
    fig, axs = plt.subplots(rows, cols, figsize=(12, 8))
    axs = axs.ravel()

    for i, entry in enumerate(file_entries):
        show_one(axs[i], entry.path, entry.name)

    for i in range(num_files, rows * cols):
        fig.delaxes(axs[i])

    plt.tight_layout()
    plt.show()


show_all(r'./res_m/')
# show_all(r'./res_m')
#show_all(r'./res/', ['new_rat4_BS_aff_E_speed_50_layers_21_eeshz_100', 'new_rat4_BS_aff_F_speed_50_layers_21_eeshz_100'])
