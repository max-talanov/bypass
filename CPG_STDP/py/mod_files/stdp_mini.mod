NEURON {
    POINT_PROCESS STDP_mini : Definition of mechanism
    POINTER synweight : Pointer to the weight (in a NetCon object) to be adjusted.
    RANGE tauhebb, tauanti : LTP/LTD decay time constants (in ms) for the Hebbian (pre-before-post-synaptic spikes), and anti-Hebbian (post-before-pre-synaptic) cases.
    RANGE hebbwt, antiwt : Maximal adjustment (can be positive or negative) for Hebbian and anti-Hebbian cases (i.e., as inter-spike interval approaches zero).  This should be set positive for LTP and negative for LTD.
    RANGE wmax : The maximum weight for the synapse.
    RANGE softthresh : Flag turning on "soft thresholding" for the maximal adjustment parameters.
    RANGE STDPon : Flag for turning STDP adjustment on / off.
    RANGE verbose : Flag for turning off prints of weight update events for debugging.
    RANGE tlastpre, tlastpost : Remembered times for last pre- and post-synaptic spikes.
    RANGE tlasthebbelig, tlastantielig : Remembered times for Hebbian anti-Hebbian eligibility traces.
    RANGE interval : Interval between current time t and previous spike.
    RANGE deltaw : The calculated weight change.
    RANGE newweight : New calculated weight.
    RANGE skip : Flag to skip 2nd set of conditions
    RANGE gv : random gaussian
}
PARAMETER {
    tauhebb  = 17  (ms)
    tauanti  = 34  (ms)
    hebbwt = 0.01
    antiwt = -0.02
    wmax  = 15.0
    softthresh = 1
    STDPon = 1
    verbose = 2
    skip = 0
}


ASSIGNED {
    synweight
    tlastpre   (ms)
    tlastpost  (ms)
    tlasthebbelig   (ms)
    tlastantielig  (ms)
    interval    (ms)
    deltaw
    newweight
    gv
}

INITIAL {
    tlastpre = 0            : no spike yet
    tlastpost = 0           : no spike yet
    tlasthebbelig = 0      : no eligibility yet
    tlastantielig = 0  : no eligibility yet
    interval = 0
    deltaw = 0
    newweight = 0
}


FUNCTION softthreshold(rawwc) {
    if (rawwc >= 0) { softthreshold = rawwc * (1.0 - synweight / wmax) } : If the weight change is non-negative, scale by 1 - weight / wmax.
    else { softthreshold = rawwc * synweight / wmax } : Otherwise (the weight change is negative), scale by weight / wmax.
}

PROCEDURE adjustweight(wc) {
   synweight = synweight + wc : apply the synaptic modification, and then clip the weight if necessary to make sure it's between 0 and wmax.
   printf("ajustweight synweight = %f", synweight)

   if (synweight > wmax) { synweight = wmax }
   if (synweight < 0) { synweight = 0 }
}


NET_RECEIVE (w) {
    deltaw = 0.0 : Default the weight change to 0.
    skip = 0

    if (verbose > 1)  {
        printf("t=%f (BEFORE) tlaspre=%f, tlastpost=%f, flag=%f, w=%f, deltaw=%f \n",t,tlastpre, tlastpost,flag,w,deltaw) }

    : Hebbian weight update happens 1ms later to check for simultaneous spikes (otherwise bug when using mpi)
    if ((flag == -1) && (tlastpre != t-1)) {
        skip = 1 : skip the 2nd set of conditions since this was artificial net event to update weights
        deltaw = (hebbwt + gv*synweight) * exp(-interval / tauhebb) : Use the Hebbian decay to set the Hebbian weight adjustment.
        if (softthresh == 1) { deltaw = softthreshold(deltaw) } : If we have soft-thresholding on, apply it.
        adjustweight(deltaw) : Adjust the weight.
        if (verbose > 1) {
            printf("Hebbian STDP event: t = %f ms; tlastpre = %f; w = %f; deltaw = %f\n",t,tlastpre,w,deltaw)
            } : Show weight update information if debugging on.
        }

    : Ant-hebbian weight update happens 1ms later to check for simultaneous spikes (otherwise bug when using mpi)
    else if ((flag == 1) && (tlastpost != t-1)) { :update weight 1ms later to check for simultaneous spikes (otherwise bug when using mpi)
        skip = 1 : skip the 2nd set of conditions since this was artificial net event to update weights
        deltaw = (antiwt*synweight + gv*synweight)* exp(interval / tauanti) : Use the anti-Hebbian decay to set the anti-Hebbian weight adjustment.
        if (softthresh == 1) { deltaw = softthreshold(deltaw) } : If we have soft-thresholding on, apply it.
        adjustweight(deltaw) : Adjust the weight.
        if (verbose > 1) {
        printf("anti-Hebbian STDP event: t = %f ms; deltaw = %f\n",t,deltaw) } : Show weight update information if debugging on.
        }


    : If we receive a non-negative weight value, we are receiving a pre-synaptic spike (and thus need to check for an anti-Hebbian event, since the post-synaptic weight must be earlier).
    if (skip == 0) {
        if (w >= 0) {
            interval = tlastpost - t  : Get the interval; interval is negative
            if  ((tlastpost > -1) && (-interval > 1.0)) { : If we had a post-synaptic spike and a non-zero interval...
                if (STDPon == 1) { : If STDP learning is turned on...
                    if (verbose > 1) {printf("net_send(1,1)\n")}
                    net_send(1,1) : instead of updating weight directly, use net_send to check if simultaneous spike occurred (otherwise bug when using mpi)
                }
            }
            tlastpre = t : Remember the current spike time for next NET_RECEIVE.

        : Else, if we receive a negative weight value, we are receiving a post-synaptic spike (and thus need to check for a Hebbian event, since the pre-synaptic weight must be earlier).
        } else {
            interval = t - tlastpre : Get the interval; interval is positive
            if  ((tlastpre > -1) && (interval > 1.0)) { : If we had a pre-synaptic spike and a non-zero interval...
                if (STDPon == 1) { : If STDP learning is turned on...
                    if (verbose > 1) {printf("net_send(1,-1)\n")}
                    net_send(1,-1) : instead of updating weight directly, use net_send to check if simultaneous spike occurred (otherwise bug when using mpi)
                }
            }
            tlastpost = t : Remember the current spike time for next NET_RECEIVE.
        }
    }
    if (verbose > 1)  {
        printf("t=%f (AFTER) tlaspre=%f, tlastpost=%f, flag=%f, w=%f, deltaw=%f \n",t,tlastpre, tlastpost,flag,w,deltaw) }
}
