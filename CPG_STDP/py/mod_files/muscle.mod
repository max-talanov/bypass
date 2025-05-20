TITLE Calcium dynamics and cross-bridge formation

UNITS { }

NEURON {
	SUFFIX CaSP

	::module 1::
	RANGE k1, k2, k3, k4, k5, k6, k, k5i, k6i
	RANGE Umax, Rmax, t1, t2, R, vth, U
	RANGE phi0, phi1, phi2, phi3, phi4, phi
	RANGE first_on, first_off

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
	k1 = 3000		: M-1*ms-1
	k2 = 3			: ms-1
	k3 = 400		: M-1*ms-1
	k4 = 1			: ms-1
	k5i = 4e5		: M-1*ms-1
	k6i = 120		: Faster dissociation
	k = 850			: M-1
	SF_AM = 0.3		: Further reduced feedback to increase Ca retention
	Rmax = 200		: Further increased release
	Umax = 5000
	t1 = 4			: Faster rise for better response
	t2 = 250		: Much slower decay for 600ms cycle
	phi1 = 0.03
	phi2 = 1.23
	phi3 = 0.01
	phi4 = 1.08
	CS0 = 0.2		:[M]
	B0 = 0.00043	:[M]
	T0 = 0.00002 	:[M]

	::module 2::
	c1 = 0.0005		: Even lower threshold for earlier activation
	c2 = 0.006		: Steeper transition curve
	c3 = 25			: Faster time constant
	c4 = -10
	c5 = 4
	alpha = 4.5     
	alpha1 = 4.77
	alpha2 = 400
	alpha3 = 160
	beta = 0.47
	gamma = 0.001
	recovery_rate = 0.008  : Active recovery rate when no spikes

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
	first_on
	first_off
}

BREAKPOINT { LOCAL i, tempR, time_since_last_spike

	SPK_DETECT (v, t)
	CaR (CaSR, t)

	SOLVE state METHOD cnexp

	xm[0]=xm[1]
	xm[1]=cli

	vm = (xm[1]-xm[0])/(dt*10^-3)

	:: Calculate time since last spike for force decay
	time_since_last_spike = 1e9 :: Large default value
	if (spk_index > 0) {
		time_since_last_spike = t - spk[spk_index-1]
	}

	::isometric and isokinetic condition::
	:: Add time-dependent decay after spike ends
	if (R_On == 0 && time_since_last_spike > 50) {
		mgi = AM^alpha * (1 + 0.2*exp(-0.1*cli*cli)) * exp(-0.002*(time_since_last_spike-50))
	} else {
		mgi = AM^alpha * (1 + 0.2*exp(-0.1*cli*cli))
	}
	
	if (t < 0.1 || (t > 199.95 && t < 200.0) || (t > 399.95 && t < 400.0) || (t > 599.95 && t < 600.0)) {
		printf("Muscle: t=%.1f ms, mgi=%.4f, cli=%.4f, AM=%.4f, time_since_spike=%.1f\n", t, mgi, cli, AM, time_since_last_spike)
	}
}

DERIVATIVE state {
	rate (cli, CaT, AM, t)

	CaSR' = -k1*CS0*CaSR + (k1*CaSR+k2)*CaSRCS - R + U(Ca)
	CaSRCS' = k1*CS0*CaSR - (k1*CaSR+k2)*CaSRCS

	:: Use conditional expressions rather than if statements
	:: Add active recovery mechanism
	Ca' = - k5*T0*Ca + (k5*Ca+k6)*CaT - k3*B0*Ca + (k3*Ca+k4)*CaB + (R_On*R) - U(Ca) - ((1-R_On)*recovery_rate*Ca)
	
	CaB' = k3*B0*Ca - (k3*Ca+k4)*CaB
	CaT' = k5*T0*Ca - (k5*Ca+k6)*CaT

	:: More aggressive AM decay using conditional expressions
	AM' = (AMinf - AM)/AMtau - ((1-R_On)*(CaT/T0 <= c1)*recovery_rate*AM)
	
	mgi' = 0
}

PROCEDURE SPK_DETECT (v (mv), t (ms)) {
	if (Spike_On == 0 && v > vth) {
	  Spike_On = 1
	  spk[spk_index] = t + t_axon
	  spk_index = spk_index + 1
	  R_On = 1
	  
	  :if (first_on) {
	   : printf("First spike - Time %g ms: R_On set to 1\n", t)
	    :first_on = 0
	  :}
	} else if (v < vth) {
	  if (Spike_On == 1) {
	    Spike_On = 0
	    R_On = 0
	    
	    :if (first_off) {
	      :printf("First spike end - Time %g ms: R_On set to 0\n", t)
	      :first_off = 0
	    :}
	    
	    :if (t > 595 && t < 605) {
	      :printf("Near end of spiking at %g ms: R_On set to 0\n", t)
	    :}
	  }
	}
	
	:if (t > 699 && t < 701) {
	  :printf("Check at 700 ms: R_On = %g, Spike_On = %g\n", R_On, Spike_On)
	:}
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
	else {
		R = 0
		:: Print debugging for spike-end transitions around 600ms
		if (t > 595.9 && t < 605.0 && spk_index > 0) {
			printf("Spike end at t=%.1f ms: R=0, last spike at %.1f ms\n", t, spk[spk_index-1])
		}
	}
}

PROCEDURE rate (cli (M), CaT (M), AM (M), t(ms)) {
	k5 = phi(cli)*k5i
	k6 = k6i/(1 + SF_AM*AM)
	AMinf = 0.5*(1+tanh(((CaT/T0)-c1)/c2))
	AMtau = c3/(cosh(((CaT/T0)-c4)/(2*c5)))
}

INITIAL {LOCAL i
	CaSR = 0.0025  		:[M]
	CaSRCS = 0			:[M]
	Ca = 1e-10			:[M]
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
	first_on = 1
	first_off = 1
}