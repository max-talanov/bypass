The txt files coul be opened with 
https://www.falstad.com/circuit/circuitjs.html


The json files please use online editor:
https://easyeda.com

##Soma

	1.	Incoming input signals at 200 Hz (with different voltages) from other neurons into the soma of the neuron under consideration.
	2.	Summation (adder) of the input signals. The 22 nF capacitor (can be changed if needed) is required to emulate changes in the neuron’s membrane potential.
	3.	This part of the circuit sets the threshold voltage required to generate the neuron’s output pulse (spike).
	4.	Here the refractory period and the neuron’s output are set. It should be approximately 2 ms. Different values of the 10 nF capacitor and the 220 kΩ resistor need to be tested.
	5.	The transistor turns on during the refractory period, preventing the membrane potential from rising. The 10 kΩ resistor and 10 nF capacitor are needed to delay the signal slightly; otherwise the XOR (item 4) will not have time to form the refractory period.
	6.	From here the signal goes to the learning circuit (POST in the simulator; NEUR_OUT_1 on the schematic). NEUR_OUT_1 of one neuron (from one board) connects to NEUR_OUT_2 of another neuron (on another board) via a wire.
	7.	Neuron output.


  
