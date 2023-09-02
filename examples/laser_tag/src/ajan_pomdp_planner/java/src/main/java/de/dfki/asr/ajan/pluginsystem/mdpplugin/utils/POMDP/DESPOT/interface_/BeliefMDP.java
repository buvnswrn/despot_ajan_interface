package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanBelief;

import java.util.HashMap;

public interface BeliefMDP extends DSPOMDP{

    BeliefLowerBound CreateBeliefLowerBound(String name, long cppReferenceToPolicy);
    BeliefUpperBound CreateBeliefUpperBound(String name, long upperBoundCppReference);

    /**
     * Transition function for the belief MDP.
     */
     AjanBelief Tau(AjanBelief belief, int action, long obs);

    /**
     * Observation function for the belief MDP.
     */
    void Observe(AjanBelief belief, int action, HashMap<Long, Double> obs);

    /**
     * Reward function for the belief MDP.
     */
    double StepReward(AjanBelief belief, int action);
}
