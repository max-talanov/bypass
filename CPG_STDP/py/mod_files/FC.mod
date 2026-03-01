TITLE Fast Na K channels
:
: Equations modified from (Traub et al., 1994)

INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}

NEURON {
	SUFFIX fastchannels
	USEION na READ ena WRITE ina
	USEION k READ ek WRITE ik
	NONSPECIFIC_CURRENT il
	RANGE gnabar, gkbar, vtraub, gl, el
	RANGE m_inf, h_inf, n_inf, m, h, n
	RANGE tau_m, tau_h, tau_n
}


UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
}

PARAMETER {
	gnabar	= 0.3 	(mho/cm2)
	gkbar	= 0.05 	(mho/cm2)
	gl = 0.0003 (S/cm2)
	el = -70 (mV)

	ena	= 50	(mV)
	ek	= -90	(mV)
	celsius = 36    (degC)
	dt              (ms)
	v               (mV)
	V_adj = -63 		(mV)
	V_mem           (mV)
}

STATE {
	m h n
}

ASSIGNED {
	ina	(mA/cm2)
	ik	(mA/cm2)
	il	(mA/cm2)
	m_inf
	h_inf
	n_inf
	tau_m
	tau_h
	tau_n
	tadj
}


BREAKPOINT {
	SOLVE states METHOD cnexp
	ina = gnabar * m*m*m*h * (v - ena)
	ik  = gkbar * n*n*n*n * (v - ek)
	il = gl * (v - el)
}


DERIVATIVE states {
	evaluate_fct(v)
	m' = (m_inf - m) / tau_m
	h' = (h_inf - h) / tau_h
	n' = (n_inf - n) / tau_n
}

UNITSOFF
INITIAL {
	m = 0
	h = 0
	n = 0
}

PROCEDURE evaluate_fct(v(mV)) { LOCAL a,b, v13, v40, v17, v15, v10

	V_mem = v - V_adj
	v13 = 13 - V_mem
	v40 = V_mem - 40
	v17 = 17 - V_mem
	v15 = 15 - V_mem
	v10 = 10 - V_mem

	a = 0.32 * v13 / ( exp(v13/4) - 1)
	b = 0.28 * v40 / ( exp(v40/5) - 1)
	tau_m = 1 / (a + b)
	m_inf = a / (a + b)

	a = 0.128 * exp(v17/18)
	b = 4 / ( 1 + exp(-v40/5) )
	tau_h = 1 / (a + b)
	h_inf = a / (a + b)

	a = 0.032 * v15 / ( exp(v15/5) - 1)
	b = 0.5 * exp(v10/40)
	tau_n = 1 / (a + b)
	n_inf = a / (a + b)
}

UNITSON
