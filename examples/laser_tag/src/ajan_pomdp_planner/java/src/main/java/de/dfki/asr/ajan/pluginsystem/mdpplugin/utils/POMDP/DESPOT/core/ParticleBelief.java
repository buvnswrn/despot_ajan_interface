package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanAgent;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.DSPOMDP;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.StateIndexer;

import java.util.Vector;

public abstract class ParticleBelief extends Belief {

    protected Vector<State> particles_;
    int num_particles_; // not used as of now in Java end
    Belief prior_; // not used as of now in Java end
    boolean split_; // not used as of now in Java end
    Vector<State> initial_particles_; // not used as of now in Java end
	StateIndexer state_indexer_; // not used as of now in Java end

    protected ParticleBelief(Vector<State> particles, DSPOMDP model, Belief prior, boolean split) {
        super(model);
        split = true;
    }

    public ParticleBelief() {
        super(0);
    }

//    @Override
//    protected String text() {
//        return null;
//    }
}
