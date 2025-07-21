# Complete Guide: Running NEURON CPG Simulation

## 1. Getting the Code from Git

```bash
# Clone the repository
git clone https://github.com/max-talanov/bypass.git

# Navigate to the project directory
cd bypass

# Navigate to the specific CPG directory
cd CPG_STDP/py
```

## 2. Setting Up Virtual Environment

### For Windows:
```bash
# Create virtual environment
python -m venv neuron_env

# Activate virtual environment
neuron_env\Scripts\activate
```

### For Linux/macOS:
```bash
# Create virtual environment
python3 -m venv neuron_env

# Activate virtual environment
source neuron_env/bin/activate
```

## 3. Installing Dependencies

### Install NEURON Simulator
```bash
# Install NEURON (this is the main requirement)
pip install neuron

# For MPI support (optional but recommended)
pip install mpi4py
```

### Install Other Required Libraries
pip install -r requirements.txt
```
## 4. Compiling NEURON Mechanisms

Before running the simulation, you need to compile the custom NEURON mechanisms:

```bash
# Navigate to the directory containing .mod files
# (This should be in the same directory as your Python script)

# Compile mechanisms
nrnivmodl 
# or 
nrnivmodl ./mod_files/

## 5. Running the Simulation

### Method 1: Without MPI (Single Process)
```bash
# Simple execution
python check_neuron.py

# Or with NEURON's Python interpreter
nrnpython check_neuron.py
```

### Method 2: With MPI (Parallel Execution)
```bash
# Run with 4 processes
mpiexec -n 4 nrnpython check_neuron.py

# Alternative MPI command
mpirun -np 4 python check_neuron.py

# On some systems you might need:
mpiexec -n 4 python check_neuron.py
```

### Method 3: Using NEURON's Special Interpreter
```bash
# Without MPI
nrniv -python check_neuron.py

# With MPI
mpiexec -n 4 nrniv -python -mpi check_neuron.py
```