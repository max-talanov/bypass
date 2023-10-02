import os

import h5py
import matplotlib.pyplot as plt
import numpy as np

def show_all(path):
    for entry in os.scandir(path):
        if not entry.name.endswith('.hdf5'):
            continue
        _show_one(entry.path, entry.name)
def _show_one(path, name):
    with h5py.File(path, 'r') as file:
        all = []
        for i in file:
            all.extend(np.array(file[i]))
        all = np.array(all)
        plt.plot(all)
        plt.title(name)
        plt.show()

show_all(r'./res/')