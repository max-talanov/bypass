import pickle

import nest
def dump(spike_recorder, name):
    ts, node_ids = nest.raster_plot._from_memory(spike_recorder)
    if not len(ts):
        raise nest.kernel.NESTError("No events recorded!")
    with open(f'{name}_ts', "wb") as handle:
        pickle.dump(ts, handle)
    with open(f'{name}_node_ids', "wb") as handle:
        pickle.dump(node_ids, handle)

def load(name):
    with open(f'{name}_ts', "rb") as handle:
        ts = pickle.load(handle)
    with open(f'{name}_node_ids', "rb") as handle:
        node_ids = pickle.load(handle)
    return ts, node_ids