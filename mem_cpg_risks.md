# The mem_cpg project ricks 

|    Risk | Severeness	     | Comment                                                                                                         |
|---------------:|:-----------------------|:----------------------------------------------------------------------------------------------------------------|
| V_reset: -46.0 | NA                     | NA                                                                                                              |
|    V_peak: 0.0 | g_K,g_Na               | g_K,g_Kv1,g_Kv3[nS] Potassium peak conductance; g_Na[nS] Sodium peak conductance                                |
|    V_th: -50.0 | V_T                    | Voltage offset that controls dynamics. For default parameters, V_T = -63mV results in a threshold around -50mV. |
|     I_e: 500.0 | I_e                    | External input current                                                                                          |
|      g_L: 10.0 | g_L                    | Leak conductance                                                                                                |                                                                                                                |
|   tau_w: 120.0 | tau_plus: jonke        | Time constant for w; Time constant of STDP window, potentiation in ms                                                                                           |
|     E_L: -58.0 | E_L                    | Leak reversal potential                                                                                         |
|   Delta_T: 2.0 | tau_syn_ex, tau_syn_in | Synaptic delay; Rise time of the excitatory/inhibitory synaptic alpha function                                  |
|         a: 2.0 | alpha: jonke           | a - multiplier of the learning speed: dw = (a(V-E_L) - w)/tau_s; alpha - Determine shape of depression term     |
|       b: 100.0 | lambda                 | weight increase step w = w + b                                                                                  |
|     C_m: 200.0 | C_m                    | Membrane  capacitance                                                                                           |
|     V_m: -58.0 | V_m                    | Initial membrane potential #! must be equal to E_L                                                              |
|         w: 5.0 | weight: jonke          | Initial weight #! must be equal to 5 Initial weight                                                             |
