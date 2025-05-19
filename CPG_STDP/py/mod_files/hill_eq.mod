TITLE Modified Hill-Mashima muscle model

UNITS {}

NEURON {
    SUFFIX fHill
    RANGE a0, b0, c0, d0
	RANGE p0, g1, g2, g3
	RANGE Kse, A, Fc, F
	RANGE xm_init, xm, xce_init, xce
	USEION mg READ mgi VALENCE 2
	USEION cl READ cli VALENCE -1
}

PARAMETER {
	a0 = 2.0		:[N]
	b0 = 24.35		:[mm*s-1]
	c0 = -7.4		:[N]
	d0 = 30.3		:[mm*s-1]
	p0 = 90			:[N]
	g1 = -8			:[mm]
	g2 = 3			:[mm]
	xm_init = -5	:[mm]
	xce_init = -5	:[mm]
	Kse = 3.0		:[mm-1]
}

STATE {
	A
	xce
	xm
}

ASSIGNED {
	F
	Fc
	mgi
	cli
}

BREAKPOINT { LOCAL d_xm, d_xce, d_se
	A = mgi
	xm = cli

	if (t < 0.1 || (t > 299.95 && t < 300.0) || (t > 599.95 && t < 600.0) || (t > 699.95 && t < 700.0)) {
		printf("Hill: t=%.1f, A=%.4f, F=%.4f\n", t, A, F)
	}

	SOLVE state_hill METHOD cnexp

	F = p0*Kse*xse(xm, xce)
}

DERIVATIVE state_hill {
	Fc = p0*g(xm)*A
	xce' = dxdt (F, Fc)
}

FUNCTION xse (x, y) { LOCAL d_xm, d_xce, d_se
	d_xm = xm - xm_init
	d_xce = xce - xce_init
	d_se = d_xm - d_xce
    if (d_se <= 0) {
        xse = 0
    } else {
        xse = d_se
    }
}

FUNCTION g (x) {
	:: More dynamic response curve with sharper peak at optimal length
	:: Add small constant to prevent complete zero output
	g = (1.2 * exp(-1.2*((x-g1)/g2)^2)) + 0.05
}

FUNCTION dxdt (x, xc) {LOCAL gain_length
	if (x <= xc) {
		:: Speed up contraction for more responsive behavior
		dxdt = (10^-3)*(-b0*(xc-x))/(x+a0*xc/p0)
	} else {
		gain_length = (-d0*(xc-x))/(2*xc-x+c0*xc/p0)
		:: Make sure extension is always at a reasonable rate
		if (gain_length <= 0) {
			dxdt = (10^-3)*50
		} else if (gain_length > 1000) {
			dxdt = (10^-3)*50
		} else {
			dxdt = (10^-3)*gain_length
		}
	}
}

INITIAL {
	A = 0
	xm = xm_init
	xce = xce_init
	F=1e-5
}
