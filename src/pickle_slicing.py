import pickle
import os
import numpy as np

def _slice(a, n):
    return [a[i:i + len(a) // n] for i in range(0, len(a), len(a) // n)]

def dump(a, name, sampling_rate, n):
    a = a[::sampling_rate]
    a = _slice(a, n)
    for i, s in enumerate(a):
        with open(f'out/pickle_/{name}_{i}.pkl', "wb") as handle:
            pickle.dump(s, handle)

def load(name):
    a = []
    for entry in os.scandir('out/pickle_'):
        if entry.name.startswith(name):
            with open(f'{entry.path}', "rb") as handle:
                a.extend(pickle.load(handle))
    return np.asarray(a)