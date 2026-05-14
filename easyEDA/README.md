The txt files coul be opened with 
https://www.falstad.com/circuit/circuitjs.html


The json files please use online editor:
https://easyeda.com

## Soma

	1.	Incoming input signals at 200 Hz (with different voltages) from other neurons into the soma of the neuron under consideration.
	2.	Summation (adder) of the input signals. The 22 nF capacitor (can be changed if needed) is required to emulate changes in the neuron’s membrane potential.
	3.	This part of the circuit sets the threshold voltage required to generate the neuron’s output pulse (spike).
	4.	Here the refractory period and the neuron’s output are set. It should be approximately 2 ms. Different values of the 10 nF capacitor and the 220 kΩ resistor need to be tested.
	5.	The transistor turns on during the refractory period, preventing the membrane potential from rising. The 10 kΩ resistor and 10 nF capacitor are needed to delay the signal slightly; otherwise the XOR (item 4) will not have time to form the refractory period.
	6.	From here the signal goes to the learning circuit (POST in the simulator; NEUR_OUT_1 on the schematic). NEUR_OUT_1 of one neuron (from one board) connects to NEUR_OUT_2 of another neuron (on another board) via a wire.
	7.	Neuron output.

## Synaptic delay

One can change the pulse duration by adjusting the capacitor and resistor values. Alternatively, you can change the pulse-generation mode (trigger on the rising edge vs. on the falling edge) by reversing the diode direction.
  
## Learning

	1.	PRE input — the signal is applied here after the Synaptic_Delay block.
	2.	POST input — pin NEUR_OUT_2, which receives the signal from NEUR_OUT_1 of another board (another neuron).
	3.	Operating principle:
The circuit generates an output pulse when the two signals (PRE and POST) overlap in time. At that moment, a higher-voltage pulse is applied to the memristor, changing its resistance.

At the same time, the circuit must still allow normal (weak) pulses to pass to the next soma. For this, a 20 kΩ resistor is used to bypass the transistor switch.

Details:
	•	PRE and POST overlap (learning occurs): the transistor is ON, and the PRE signal passes directly, bypassing the 20 kΩ resistor.
	•	PRE and POST do not overlap (no learning): the transistor is OFF, and the signal is attenuated by the divider (20 kΩ + 10 kΩ). The result is a lower-amplitude pulse (~300 mV), insufficient to change the memristor resistance, but sufficient to increase the membrane potential of the next neuron — the ~300 mV signal is then amplified by the op-amp stage formed by the resistor network and the memristor.

	4.	Polarity change:

	•	If PRE arrives before POST, a positive pulse is formed (memristor resistance decreases).
	•	If POST arrives before PRE, a negative pulse is formed (memristor resistance increases).

	5.	Amplitude adjustment:
The 100 kΩ and 33 kΩ resistors set the levels of the positive and negative pulses.
If you change them, you must also adjust the 20 kΩ resistor (see item 3) so that the “no-learning” signal remains around ~300 mV.

Memristor voltage divider:
The op-amp non-inverting input receives either a learning pulse (high voltage) or a normal pulse (~300 mV when there is no learning). The learning pulse changes the memristor resistance but does not affect the membrane potential of the next neuron (because that neuron is in its refractory period at that time).
	7.	Neuron output — the final output signal of the circuit.
