TITLE Muscle length variation

NEURON {
	POINT_PROCESS xm
	RANGE amp, cli
	USEION cl WRITE cli VALENCE -1
}

UNITS {
	(nA) = (nanoamp)
}

PARAMETER {
	amp = -8	::mm
}

ASSIGNED {
    cli (nA)
}

BREAKPOINT {
	cli = amp
	if (t < 0.1 || (t > 199.95 && t < 200.0) || (t > 399.95 && t < 400.0) || (t > 599.95 && t < 600.0)) {
		printf("XM: t=%.1f ms, amp=%.4f, cli=%.4f\n", t, amp, cli)
	}
}

INITIAL {
    printf("XM INITIAL: amp=%.4f\n", amp)
}
