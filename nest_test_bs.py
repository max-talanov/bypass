# import nest
import nest.voltage_trace
import matplotlib.pyplot as plt

nest.set_verbosity("M_WARNING")
nest.ResetKernel()

###############################################################################
# Second, we create the two neurons and the recording device.

neuron_1 = nest.Create("iaf_psc_alpha")
neuron_2 = nest.Create("iaf_psc_alpha")
voltmeter = nest.Create("voltmeter")

###############################################################################
# Third, we set the external current of neuron 1.

neuron_1.I_e = 376.0

###############################################################################
# Fourth, we connect neuron 1 to neuron 2.
# Then, we connect a voltmeter to the two neurons.
# To learn more about the previous steps, please check out the
# :doc:`one neuron example <one_neuron>`.

weight = 20.0
delay = 1.0

nest.Connect(neuron_1, neuron_2, syn_spec={"weight": weight, "delay": delay})
nest.Connect(voltmeter, neuron_1)
nest.Connect(voltmeter, neuron_2)

###############################################################################
# Now we simulate the network using ``Simulate``, which takes the
# desired simulation time in milliseconds.

nest.Simulate(1000.0)

###############################################################################
# Finally, we plot the neurons' membrane potential as a function of
# time.

neuron_1.I_e = 460.0
nest.Simulate(1000.0)

nest.voltage_trace.from_device(voltmeter)
plt.show()
