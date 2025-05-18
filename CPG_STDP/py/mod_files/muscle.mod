TITLE Calcium dynamics and cross-bridge formation

UNITS { }

NEURON {
	SUFFIX CaSP

	::module 1::
	RANGE k1, k2, k3, k4, k5, k6, k, k5i, k6i
	RANGE Umax, Rmax, t1, t2, R, vth, U
	RANGE phi0, phi1, phi2, phi3, phi4, phi

	::module 2::
	RANGE c1, c2, c3, c4, c5
	RANGE AMinf, AMtau, SF_AM
	RANGE acm, alpha, alpha1, alpha2, alpha3, beta, gamma

	::simulation::
	RANGE spk_index, t_axon, vm, R
	USEION mg WRITE mgi VALENCE 2
	USEION cl READ cli VALENCE -1
}

PARAMETER {
	::module 1::
	k1 = 2000		: Calcium binding rate
	k2 = 4			: Release rate
	k3 = 300		: Secondary binding rate
	k4 = 3			: Removal rate
	k5i = 2e5		: Troponin binding rate
	k6i = 200		: Dissociation rate
	k = 600			: Calcium sensitivity
	SF_AM = 2.5     : Activation scaling
	Rmax = 40		: Maximum release rate
	Umax = 4000		: Uptake rate
	t1 = 3.0		: Rise time
	t2 = 20			: Decay time
	phi1 = 0.015    : Sensitivity
	phi2 = 0.8      : Baseline
	phi3 = 0.005    : Sensitivity
	phi4 = 0.7      : Baseline
	CS0 = 0.01      : Store capacity
	B0 = 0.0006		: Buffer capacity
	T0 = 0.00007 	:[M]

	::module 2::
	c1 = 0.08       : Activation threshold
	c2 = 0.12       : Activation curve steepness
	c3 = 40         : AM time constant
	c4 = -13.116
	c5 = 4.0        : Recovery rate
	alpha = 1.2     : Force scaling
	alpha1 = 4.77
	alpha2 = 400
	alpha3 = 160
	beta = 0.4      : Force decay rate
	decay = 0.002   : Additional decay rate

	::simulation::
	vth = -40
	spk_index = 0
	t_axon = 0.01
}

STATE {
	CaSR
	CaSRCS
	Ca
	CaB
	CaT
	AM
	mgi
}

ASSIGNED {
	v 	(mV)
	R
	t_shift
	R_On
	Spike_On
	k5
	k6
	AMinf
	AMtau
	cli
	spk[10000]
	xm[2]
	vm
	acm
}

BREAKPOINT { LOCAL i, tempR, f_temp
	SPK_DETECT (v, t)
	CaR (CaSR, t)

	SOLVE state METHOD cnexp

	xm[0]=xm[1]
	xm[1]=cli

	vm = (xm[1]-xm[0])/(dt*10^-3)

	::isometric and isokinetic condition::
	f_temp = AM^alpha
	mgi = f_temp/(1 + beta*f_temp)
	if (mgi > 1.0) { mgi = 1.0 }
}

DERIVATIVE state {
	rate (cli, CaT, AM, t)

	CaSR' = -k1*CS0*CaSR + (k1*CaSR+k2)*CaSRCS - R + U(Ca)
	CaSRCS' = k1*CS0*CaSR - (k1*CaSR+k2)*CaSRCS

	Ca' = - k5*T0*Ca + (k5*Ca+k6)*CaT - k3*B0*Ca + (k3*Ca+k4)*CaB + R - U(Ca)
	CaB' = k3*B0*Ca - (k3*Ca+k4)*CaB
	CaT' = k5*T0*Ca - (k5*Ca+k6)*CaT

	: Enhanced recovery with additional decay term
	AM' = (AMinf - AM)/AMtau - decay*AM
	mgi' = 0
}

PROCEDURE SPK_DETECT (v (mv), t (ms)) {
	if (Spike_On == 0 && v > vth) {
		Spike_On = 1
		spk[spk_index] = t + t_axon
		spk_index = spk_index + 1
		R_On = 1
	} else if (v < vth) {
		Spike_On = 0
	}
}

FUNCTION U (x) {
	if (x >= 0) {U = Umax*(x^2*k^2/(1+x*k+x^2*k^2))^2}
	else {U = 0}
}

FUNCTION phi (x) {
	if (x <= -8) {phi = phi1*x + phi2}
	else {phi = phi3*x + phi4}
}

PROCEDURE CaR (CaSR (M), t (ms)) { LOCAL i, tempR  ::Ca_Release::
	if (R_On == 1) {
    if (spk_index > 0){
		  tempR = tempR + CaSR*Rmax*(1-exp(-(t-spk[spk_index-1])/t1))*exp(-(t-spk[spk_index-1])/t2)
		}
		R = tempR
		tempR = 0
	}
	else {R = 0}
}

PROCEDURE rate (cli (M), CaT (M), AM (M), t(ms)) {
	k5 = phi(cli)*k5i
	k6 = k6i/(1 + SF_AM*AM)
	AMinf = 0.5*(1+tanh(((CaT/T0)-c1)/c2))
	AMtau = c3/(cosh(((CaT/T0)-c4)/(2*c5))) + 15
}

INITIAL {LOCAL i
	CaSR = 0.0015  		: Initial calcium store
	CaSRCS = 0			:[M]
	Ca = 5e-11			: Initial free calcium
	CaB = 0				:[M]
	CaT = 0				:[M]
	AM = 0				:[M]
	mgi = 0

	FROM i = 0 TO 9999 {
	spk[i] = 0
	}
	FROM i = 0 TO 1 {
	xm[i] = 0
	}
	spk_index = 0
	R_On = 0
}
