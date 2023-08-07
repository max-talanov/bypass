# Import Izhi model

import matplotlib.pyplot as plt
import nest
import numpy as np
import os

# from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils
# module_name, neuron_model_name = NESTCodeGeneratorUtils.generate_code_for("izhikevich_tutorial.nestml")
from pynestml.frontend.pynestml_frontend import generate_target
from pynestml.frontend.pynestml_frontend import generate_nest_target

generate_nest_target(input_path="izhimodule", target_path="/tmp/nestml_target")
nest.Install("nestmlmodule")

nest.set_verbosity("M_INFO")
nest.ResetKernel()

neuron = nest.Create("izhikevich_tutorial")
voltmeter = nest.Create("voltmeter")

voltmeter.set({"record_from": ["v", "u"]})
nest.Connect(voltmeter, neuron)

cgs = nest.Create('dc_generator')
cgs.set({"amplitude": 25.})
nest.Connect(cgs, neuron)

sr = nest.Create("spike_recorder")
nest.Connect(neuron, sr)

nest.Simulate(250.)

spike_times = nest.GetStatus(sr, keys='events')[0]['times']
print(spike_times)

fig, ax = plt.subplots(nrows=2)
ax[0].plot(voltmeter.get("events")["times"], voltmeter.get("events")["v"])
ax[1].plot(voltmeter.get("events")["times"], voltmeter.get("events")["u"])
ax[0].scatter(spike_times, 30 * np.ones_like(spike_times), marker="d", c="orange", alpha=.8, zorder=99)
for _ax in ax:
    _ax.grid(True)
ax[0].set_ylabel("v [mV]")
ax[1].set_ylabel("u")
ax[-1].set_xlabel("Time [ms]")
fig.show()
plt.show()
print("script completed ...")
