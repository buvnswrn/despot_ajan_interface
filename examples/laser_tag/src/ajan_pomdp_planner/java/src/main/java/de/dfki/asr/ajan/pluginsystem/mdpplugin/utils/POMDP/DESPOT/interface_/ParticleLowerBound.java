package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;

import java.util.Vector;
@Deprecated // Added for future use
public abstract class ParticleLowerBound {
    protected DSPOMDP agent_model;

    protected abstract ValuedAction Value(Vector<State> particles_p, History history);
}
