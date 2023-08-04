package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

public interface BeliefUpperBound {

    /**
     * Returns a upper bound for the maximum total discounted reward
     * on a general representation of a belief. The horizon is infinite.
     *
     * @param belief The belief to be evaluated
     */
    double Value(Belief belief);
}
