TITLE Chloride setter as DENSITY mechanism

NEURON {
    SUFFIX xm
    USEION cl WRITE cli VALENCE -1
    RANGE amp
}

PARAMETER {
    amp = -8 (mm)
}

ASSIGNED {
    cli (mM)
}

BREAKPOINT {
    cli = amp
}
