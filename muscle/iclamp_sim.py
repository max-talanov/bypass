import nest
import pylab
import numpy
from pynestml.frontend.pynestml_frontend import generate_nest_target

def plot_parameter(device, param_to_display, label, style='-'):
    status = nest.GetStatus(device)[0]
    events = status['events']
    times = events['times']
    pylab.plot(times, events[param_to_display], style, label=label)

# generate_nest_target(input_path="nestmlmodule", target_path="/tmp/nestml_target")
nest.Install("nestmlmodule")

nest.total_num_virtual_procs = 16 # the number of threads to be used for the simulation
nest.SetKernelStatus(dict(resolution=0.1))

## Synapses
d = 1.0
Je = 100.0 # 20.0
Ke = 20
Ia_fibers_freq_lo = 100
Ia_fibers_num = 50

Ia_g_params = {"rate": Ia_fibers_freq_lo}
gen2neuron_dict = {"rule": "all_to_all"}
syn_dict_ex = {"delay": d, "weight": Je}

l_f_Ia_fiber_generator = nest.Create("poisson_generator", Ia_fibers_num, params=Ia_g_params)

neuron = nest.Create(
    'hh_moto_5ht', params={
        #"I_e": 700.0,  # pA
        "C_m": 200.0,  # pF
        "t_ref": 0.0,
    }
)

muscle = nest.Create(
    'hh_moto_5ht_muscle', params={
        #"I_e": 700.0,  # pA
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
            "F",
            ## Debug
            "tempConvR1",
            "R",
            "CaSR",
            "Ca",
            "CaSRCS",
            "CaB",
            "CaT",
            "AM",
            "At",
            "F",
            "Fc"
        ],
        #"withtime": True,
        "interval": 0.1
    }
)

nest.Connect(multimeter, neuron)
nest.Connect(l_f_Ia_fiber_generator, neuron, gen2neuron_dict, syn_dict_ex)

nest.Connect(m_multimeter, muscle)
nest.Connect(l_f_Ia_fiber_generator, muscle, gen2neuron_dict, syn_dict_ex)

nest.Simulate(150.)

pylab.figure()
pylab.title('Nest iclamp sim')

pylab.subplot(5, 1, 1)
pylab.ylabel('Membrane Voltage')
plot_parameter(m_multimeter, 'V_m', 'V_m')
#plot_parameter(m_multimeter, 'Fc', 'Fc', 'r')
pylab.legend()

pylab.subplot(5, 1, 2)
pylab.ylabel('AM')
#pylab.yticks(numpy.arange(0.0001, 0.0010, 0.0002))
#plot_parameter(m_multimeter, 'Ca_in', 'Ca_in')
#plot_parameter(m_multimeter, 'tempConvR1', 'tempConvR1', 'k')
plot_parameter(m_multimeter, 'CaB', 'CaB', 'b')
#plot_parameter(m_multimeter, 'CaT', 'CaT', 'k')
#plot_parameter(m_multimeter, 'Ca', 'Ca', 'r')
pylab.legend()

pylab.subplot(5, 1, 3)
#pylab.ylim(0, 1)
pylab.ylabel('CaB')
# plot_parameter(m_multimeter, 'Act_h', 'h', 'r')
# plot_parameter(m_multimeter, 'Act_m', 'm', 'g')
# plot_parameter(m_multimeter, 'Inact_n', 'n', 'b')
plot_parameter(m_multimeter, 'CaSRCS', 'CaSRCS', 'k')
pylab.legend()

pylab.subplot(5, 1, 4)
#pylab.ylim(0, 1)
pylab.ylabel('CaSR')
# plot_parameter(m_multimeter, 'Act_p', 'p', 'r')
# plot_parameter(m_multimeter, 'Act_mc', 'mc', 'g')
# plot_parameter(m_multimeter, 'Act_hc', 'hc', 'b')
plot_parameter(m_multimeter, 'CaSR', 'CaSR', 'g')
# plot_parameter(m_multimeter, 'CaT', 'CaT', 'k')
pylab.legend()

pylab.subplot(5, 1, 5)
#pylab.ylim(0, 1)
pylab.ylabel('R, CaSRCS')
plot_parameter(m_multimeter, 'R', 'R', 'r')
#plot_parameter(m_multimeter, 'tempConvR1', 'tempConvR1', 'b')
pylab.legend()

pylab.show()
