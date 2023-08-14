package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ParticleUpperBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;

import java.util.Vector;

public class AjanParticleUpperBound extends ParticleUpperBound {
    public AjanAgent agent_model;
    public Vector<Double> value_;

    AjanParticleUpperBound(AjanAgent model) {
        agent_model = model;
        // TODO: Implement AjanParticleUpperBound constructor to call JNI
        // store the distance between rob and opponent in value_[state.state_id]
        /*
         * This is implementing both particle and belief upperbound. So, try to separate them.
         **/
    }
    AjanParticleUpperBound(long cppPointer){

    }
    @Override
    protected double Value(State state) {
        // TODO: Implement AjanParticleUpperBound::Value Function for Particle to call JNI.
        // Return precomputed value_[state.state_id];
        return 0.0;
    }

}
