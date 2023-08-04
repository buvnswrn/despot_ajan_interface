package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;
import jdk.jshell.spi.ExecutionControl;

import java.util.Vector;

public abstract class ParticleUpperBound implements ScenarioUpperBound {

    /**
     * Returns a upper bound for the maximum total discounted reward
     * starting from a non-determinized particle. The horizon is infinite.
     *
     * @param state The particle (a sampled state) to be evaluated
     */
    protected abstract double Value(final State state);

    /**
     * Evaluate a set of scenarios purely using the particles
     * Returns a upper bound for the maximum total discounted reward
     * on a set of non-determinized particles. The horizon is infinite.
     *
     * @param particles States in the head of scenarios.
//     * @param streams Random numbers attached to the scenarios.
     * @param history Current action-observation history.
     */
    public double Value(final Vector<State> particles, History history) throws ExecutionControl.NotImplementedException {
        throw new ExecutionControl.NotImplementedException("Value(final Vector<State> particles, History history) is not Implemented in Java. Refer C++: despot/src/interface/upper_bound.cpp");
    };
}
