package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

public abstract class ParticleLowerBound {
    DSPOMDP model;

    protected abstract ValuedAction Value(Belief belief);
}
