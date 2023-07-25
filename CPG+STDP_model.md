# The description of the model in NEST

## HH alpha Clopath model of the neuron
[HH + STDP](https://nest-simulator.readthedocs.io/en/stable/models/hh_psc_alpha_clopath.html)

[based no Traub H-H](https://nest-simulator.readthedocs.io/en/stable/models/hh_cond_exp_traub.html)
## Bursting parameters for Adaptive Exponential Integrate and Fire  
[AEIF](https://nest-simulator.readthedocs.io/en/stable/model_details/aeif_models_implementation.html#Params-(chose-a-dictionary))

## The mapping 

# Bursting
|       aeif_param2 | H-H        | Comment                                                                                                         |
|------------------:|:-----------|:----------------------------------------------------------------------------------------------------------------|
| "V_reset": -46.0, | NA         | NA                                                                                                              |
|    "V_peak": 0.0, | NA         | NA                                                                                                              |
|    "V_th": -50.0, | V_T        | Voltage offset that controls dynamics. For default parameters, V_T = -63mV results in a threshold around -50mV. |
|     "I_e": 500.0, | I_e        | External input current                                                                                          |
|      "g_L": 10.0, | g_L        | Leak conductance                                                                                                |                                                                                                                |
|   "tau_w": 120.0, | tau_syn_ex | Time constant of the excitatory synaptic exponential function.                                                  |
|     "E_L": -58.0, | E_L        | Leak reversal potential                                                                                         |
|   "Delta_T": 2.0, | NA         | Delay constant                                                                                                  |
|         "a": 2.0, | NA         | multiplication of the learning speed: dw = (a(V-E_L) - w)/tau_s                                                 |
|       "b": 100.0, | A_LTD      | weight increase step w = w + b                                                                                  |
|     "C_m": 200.0, | C_m        | Membrane  capacitance                                                                                           |
|     "V_m": -58.0, | V_m        | Initial membrane potential #! must be equal to E_L                                                              |
|       "w": 5.0,   | NA         | Initial weight #! must be equal to 5 Initial weight                                                             |

## eBrains NEST resources

[](https://www.ebrains.eu/tools/nest)
