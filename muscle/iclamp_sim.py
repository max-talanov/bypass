import nest
import pylab
import numpy
from pynestml.frontend.pynestml_frontend import generate_nest_target

def plot_parameter(device, param_to_display, label, style='-'):
    status = nest.GetStatus(device)[0]
    events = status['events']
    times = events['times']
    pylab.plot(times, events[param_to_display], style, label=label)


generate_nest_target(input_path="nestmlmodule", target_path="/tmp/nestml_target")
nest.Install("nestmlmodule")
nest.SetKernelStatus(dict(resolution=0.1))

neuron = nest.Create(
    'hh_moto_5ht', params={
        "I_e": 700.0,  # pA
        "C_m": 200.0,  # pF
        "t_ref": 0.0,
    }
)

muscle = nest.Create(
    'hh_moto_5ht_muscle', params={
        "I_e": 700.0,  # pA
        "C_m": 200.0,  # pF
        "t_ref": 0.0,
    }
)

multimeter = nest.Create(
    'multimeter',
    params={
        "record_from": [
            "V_m",
            "Ca_in",
            "Act_m",
            "Act_h",
            "Inact_n",
            "Act_p",
            "Act_mc",
            "Act_hc",
        ],
        #"withtime": True,
        "interval": 0.1
    }
)

m_multimeter = nest.Create(
    'multimeter',
    params={
        "record_from": [
            "V_m",
            "Ca_in",
            "Act_m",
            "Act_h",
            "Inact_n",
            "Act_p",
            "Act_mc",
            "Act_hc",
            "Ca",
            "CaT",
            "At",
            "Fc",
            "F"
        ],
        #"withtime": True,
        "interval": 0.1
    }
)


nest.Connect(m_multimeter, muscle)
nest.Simulate(150.)

pylab.figure()
pylab.title('Nest iclamp sim')

pylab.subplot(5, 1, 1)
pylab.ylabel('Membrane Voltage')
plot_parameter(m_multimeter, 'V_m', 'V_m')
pylab.legend()

pylab.subplot(5, 1, 2)
pylab.ylabel('Ca inside')
pylab.yticks(numpy.arange(0.0001, 0.0010, 0.0002))
plot_parameter(m_multimeter, 'Ca_in', 'Ca_in')
pylab.legend()

pylab.subplot(5, 1, 3)
pylab.ylim(0, 1)
pylab.ylabel('h, m, n particles')
plot_parameter(m_multimeter, 'Act_h', 'h', 'r')
plot_parameter(m_multimeter, 'Act_m', 'm', 'g')
plot_parameter(m_multimeter, 'Inact_n', 'n', 'b')
pylab.legend()

pylab.subplot(5, 1, 4)
pylab.ylim(0, 1)
pylab.ylabel('p, mc, hc particles')
plot_parameter(m_multimeter, 'Act_p', 'p', 'r')
plot_parameter(m_multimeter, 'Act_mc', 'mc', 'g')
plot_parameter(m_multimeter, 'Act_hc', 'hc', 'b')
pylab.legend()

pylab.subplot(5, 1, 5)
#pylab.ylim(0, 1)
pylab.ylabel('Ca, CaT, At, Fc, F')
plot_parameter(m_multimeter, 'Ca', 'Ca', 'r')
plot_parameter(m_multimeter, 'CaT', 'CaT', 'g')
plot_parameter(m_multimeter, 'At', 'At', 'b')
pylab.legend()

pylab.show()
