# The Bursting mapping from AEIF -> HH + Jonke

## HH neuron
1. [HH alpha clopath](https://nest-simulator.readthedocs.io/en/stable/models/hh_psc_alpha_clopath.html)
1. [Traub H-H](https://nest-simulator.readthedocs.io/en/stable/models/hh_cond_exp_traub.html)
2. [hh_psc_alpha_gap](https://nest-simulator.readthedocs.io/en/stable/models/hh_psc_alpha_gap.html)

## Jonke synapse
1. [jonke_synapse](https://nest-simulator.readthedocs.io/en/stable/models/jonke_synapse.html)

## Bursting parameters for Adaptive Exponential Integrate and Fire  
[AEIF](https://nest-simulator.readthedocs.io/en/stable/model_details/aeif_models_implementation.html#Params-(chose-a-dictionary))

## The mapping
Bursting aeif-param2 -> hh_psc-alpha + jonke_synapse

|       aeif_param2 | hh_psc_alpha | Comment                                                                                                         |
|------------------:|:-------------|:----------------------------------------------------------------------------------------------------------------|
| "V_reset": -46.0, | NA           | NA                                                                                                              |
|    "V_peak": 0.0, | g_K,g_Na     | g_K,g_Kv1,g_Kv3[nS] Potassium peak conductance; g_Na[nS] Sodium peak conductance                                |
|    "V_th": -50.0, | V_T          | Voltage offset that controls dynamics. For default parameters, V_T = -63mV results in a threshold around -50mV. |
|     "I_e": 500.0, | I_e          | External input current                                                                                          |
|      "g_L": 10.0, | g_L          | Leak conductance                                                                                                |                                                                                                                |
|   "tau_w": 120.0, | tau_syn_ex   | Time constant of the excitatory synaptic exponential function.                                                  |
|     "E_L": -58.0, | E_L          | Leak reversal potential                                                                                         |
|   "Delta_T": 2.0, | NA           | Delay constant                                                                                                  |
|         "a": 2.0, | alpha: jonke | a - multiplier of the learning speed: dw = (a(V-E_L) - w)/tau_s; alpha - Determine shape of depression term     |
|       "b": 100.0, | A_LTD        | weight increase step w = w + b                                                                                  |
|     "C_m": 200.0, | C_m          | Membrane  capacitance                                                                                           |
|     "V_m": -58.0, | V_m          | Initial membrane potential #! must be equal to E_L                                                              |
|       "w": 5.0,   | NA           | Initial weight #! must be equal to 5 Initial weight                                                             |
