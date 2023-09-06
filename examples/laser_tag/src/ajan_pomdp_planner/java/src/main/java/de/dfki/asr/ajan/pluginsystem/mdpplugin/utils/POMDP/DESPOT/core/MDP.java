package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ValuedAction;

import java.util.Vector;

public abstract class MDP {

    protected abstract int NumStates();
    protected abstract int NumActions();
    protected abstract Vector<State> TransitionProbability(int s, int a);
    protected abstract double Reward(int s, int a);

    protected native Vector<ValuedAction> ComputeOptimalPoliciesUsingVIAndReturnPolicy(long agentPtr);
    public native double ComputeActionValue(long beliefPtr, long modelPtr, int action);
    protected native Vector<ValuedAction> policy(long agentPtr);
    protected native void   ComputeOptimalPolicyUsingVI(long agentPtr);

}
