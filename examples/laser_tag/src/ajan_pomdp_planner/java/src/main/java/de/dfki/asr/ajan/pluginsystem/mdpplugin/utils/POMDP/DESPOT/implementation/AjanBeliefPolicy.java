package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.BeliefLowerBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ValuedAction;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.Globals;

import java.util.Vector;

public class AjanBeliefPolicy extends BeliefLowerBound {
    Vector<Vector<Double>> alpha_vectors_; // optional
    protected AjanAgent tag_model_; // optional
    long pointerToCpp;

    protected AjanBeliefPolicy(AjanAgent model) {
        tag_model_ = model;
        tag_model_.ComputeBlindAlpha(tag_model_.agentModelPointer);
    }
    AjanBeliefPolicy(AjanAgent model, long ptr) {
        tag_model_ = model;
        tag_model_.ComputeBlindAlpha(tag_model_.agentModelPointer);
        pointerToCpp = ptr;
    }
    @Override
    protected ValuedAction Value(Belief belief) {
        double bestValue = Globals.NEG_INFTY;
        int bestAction =-1;
        // TODO: Implement AjanBeliefPolicy::Value to call JNI
        /*
         * Needs to call ComputeActionValue Function of MDP. Check on how to do that.
         **/
        System.err.println("AjanBeliefPolicy.Value(Belief) Not Implemented");
        return new ValuedAction(bestAction, bestValue);
    }
    public void SetReferenceToCpp_(long ptr) {
        this.pointerToCpp = ptr;
    }
}
