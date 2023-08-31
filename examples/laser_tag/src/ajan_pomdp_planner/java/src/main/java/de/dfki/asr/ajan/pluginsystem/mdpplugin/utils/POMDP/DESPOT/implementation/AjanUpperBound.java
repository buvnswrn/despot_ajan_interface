package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.BeliefUpperBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ParticleUpperBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import jdk.jshell.spi.ExecutionControl;

import java.util.Vector;

public class AjanUpperBound extends ParticleUpperBound implements BeliefUpperBound {

    public long pointerToCpp;
    public AjanUpperBound(long cppReference){
        pointerToCpp = cppReference;
    }
    @Override
    protected double Value(State s) {
        // TODO: Implement AjanParticleUpperBound::Value Function for Particle to call JNI.
        // Return precomputed value_[state.state_id];
        return 0.0;
    }

    @Override
    public double Value(Belief belief) {
        // TODO: Implement AjanParticleUpperBound::Value Function for Belief to call JNI.
        double value = 0;
        /*
         * Loop through the particles and for each particle (aka. state) sum up the value
         by multiplying current value with pre_computed value_[state.state_id]. Refer paper Guess:Eq.15.
         **/
        return value;
    }

    @Override
    public double Value(Vector<State> particles, History history) throws ExecutionControl.NotImplementedException {
        return 0;
    }

    public void SetReferenceToCpp_(long ptr) {
        this.pointerToCpp = ptr;
    }
}
