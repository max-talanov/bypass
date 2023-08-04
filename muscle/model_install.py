import matplotlib.pyplot as plt
import nest
import numpy as np
import os

from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils

# generate and build code
module_name, neuron_model_name = NESTCodeGeneratorUtils.generate_code_for("__izhikevich_solution.nestml")