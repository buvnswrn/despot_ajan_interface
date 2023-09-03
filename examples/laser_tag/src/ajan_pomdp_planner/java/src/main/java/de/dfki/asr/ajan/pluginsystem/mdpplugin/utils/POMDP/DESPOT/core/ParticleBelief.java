package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanAgent;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.DSPOMDP;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.StateIndexer;

import java.util.Vector;

public abstract class ParticleBelief extends Belief {

    public Vector<State> particles_; // May be have a pointer here to access when required
    public long particlesPointerToCpp;
    int num_particles_; // not used as of now in Java end
    Belief prior_; // not used as of now in Java end
    boolean split_; // not used as of now in Java end
    Vector<State> initial_particles_; // not used as of now in Java end
	StateIndexer state_indexer_; // not used as of now in Java end

    protected ParticleBelief(Vector<State> particles, DSPOMDP model, Belief prior, boolean split) {
        super(model);
        split_ = split;
    }

    public ParticleBelief() {
        super(0);
    }

    public ParticleBelief(long beliefPtr, AjanAgent model, History history, Vector<State> particles) {
        super(beliefPtr, model, history);
        particles_= particles;
    }

    public Vector<State> particles() {
        if(particles_ == null ){
            updateParticles();
        }
        return particles_;
    }
    private void updateParticles() {
        if (particlesPointerToCpp != 0){
            particles_ = getParticles(particlesPointerToCpp);
        } else {
            System.err.println("Particle cpp address not available");
        }
    }

    native Vector<State> getParticles(long particlesPointer);

//    @Override
//    protected String text() {
//        return null;
//    }
}
