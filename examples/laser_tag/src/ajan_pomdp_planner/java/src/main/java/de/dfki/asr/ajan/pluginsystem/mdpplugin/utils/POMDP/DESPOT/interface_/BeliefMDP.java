package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import java.util.HashMap;
import java.util.Map;

public interface BeliefMDP extends DSPOMDP{

    BeliefLowerBound CreateBeliefLowerBound(String name, long cppReferenceToPolicy);
    BeliefUpperBound CreateBeliefUpperBound(String name, long upperBoundCppReference);

    /**
     * Transition function for the belief MDP.
     */
     Belief Tau( Belief belief, int action, long obs);

    /**
     * Observation function for the belief MDP.
     */
    void Observe(Belief belief, int action, HashMap<Long, Double> obs);

    /**
     * Reward function for the belief MDP.
     */
    double StepReward(Belief belief, int action);
}
