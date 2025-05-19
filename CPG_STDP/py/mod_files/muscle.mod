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
	k1 = 3000		: M-1*ms-1 (fast binding)
	k2 = 2.0		: ms-1 (faster unbinding for oscillations)
	k3 = 1000		: M-1*ms-1 (increased force generation)
	k4 = 1.5		: ms-1 (faster decay for oscillations)
	k5i = 8e5		: M-1*ms-1 (increased for stronger response)
	k6i = 200		: ms-1 (faster recovery for oscillations)
	k = 1200		: M-1 (increased for higher levels)
	SF_AM = 0.8		: Reduced damping significantly
	Rmax = 30		: ms-1 (increased response)
	Umax = 8000		: M-1*ms-1 (increased activation)
	t1 = 25			: ms (faster rise)
	t2 = 175		: ms (faster decay)
	phi1 = 0.08
	phi2 = 2.0
	phi3 = 0.04
	phi4 = 1.5
	CS0 = 0.1		:[M] (increased significantly)
	B0 = 0.001	:[M] (increased buffer)
	T0 = 0.00005	:[M] (lowered threshold)

	::module 2::
	c1 = 0.08
	c2 = 0.05
	c3 = 120.0		: Faster timing
	c4 = -10.0		: Adjusted threshold
	c5 = 8.0		: Sharper response
	alpha = 4
	alpha1 = 6.0
	alpha2 = 600
	alpha3 = 250
	beta = 0.8
	gamma = 0.004

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

BREAKPOINT { LOCAL i, tempR

	SPK_DETECT (v, t)
	CaR (CaSR, t)

	SOLVE state METHOD cnexp

	xm[0]=xm[1]
	xm[1]=cli

	vm = (xm[1]-xm[0])/(dt*10^-3)

	::isometric and isokinetic condition::
	mgi = 15.0 * (AM^alpha)/(1 + 0.1*AM*AM)  : Increased scaling and reduced damping
	if (mgi > 7.0) { mgi = 7.0 }
}

DERIVATIVE state {
	rate(cli, CaT, AM, t)

	CaSR' = -k1*CS0*CaSR + (k1*CaSR+k2)*CaSRCS - R + U(Ca)
	CaSRCS' = k1*CS0*CaSR - (k1*CaSR+k2)*CaSRCS

	Ca' = -k5*T0*Ca + (k5*Ca+k6)*CaT - k3*B0*Ca + (k3*Ca+k4)*CaB + R - U(Ca)
	CaB' = k3*B0*Ca - (k3*Ca+k4)*CaB
	CaT' = k5*T0*Ca - (k5*Ca+k6)*CaT

	AM' = (2.0*(AMinf - AM)/AMtau) - (0.5*AM*AM) + 0.1*(1 - AM)  : Fixed syntax for differential equation
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
	else if (x >= 8) {phi = phi3*x + phi4}
	else {phi = phi1*x*cos(x/4) + phi2}
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
	AMinf = 1.2*(1+tanh(((CaT/T0)-c1)/c2))/(1 + 0.05*AM*AM)
	AMtau = c3/(cosh(((CaT/T0)-c4)/(2*c5))) + 15
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
}