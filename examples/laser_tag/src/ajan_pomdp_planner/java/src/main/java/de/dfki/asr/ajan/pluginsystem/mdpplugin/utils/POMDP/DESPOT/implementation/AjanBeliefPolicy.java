package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.BeliefLowerBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ValuedAction;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.Globals;

import java.util.Vector;

public class AjanBeliefPolicy extends BeliefLowerBound {
    Vector<Vector<Double>> alpha_vectors_; // optional
    AjanAgent tag_model_; // optional
    long pointerToCpp;

    AjanBeliefPolicy(AjanAgent model) {
        tag_model_ = model;
        // TODO: Implement AjanBeliefPolicy constructor to call JNI and ask for Policy
    }
    AjanBeliefPolicy(AjanAgent model, long ptr) {
        tag_model_ = model;
        pointerToCpp = ptr;
        // TODO: Implement AjanBeliefPolicy constructor to call JNI and ask for Policy
    }
    @Override
    protected ValuedAction Value(Belief belief) {
        double bestValue = Globals.NEG_INFTY;
        int bestAction =-1;
        // TODO: Implement AjanBeliefPolicy::Value to call JNI
        /*
         * Needs to call ComputeActionValue Function of MDP. Check on how to do that.
         **/
        return new ValuedAction(bestAction, bestValue);
    }
    public void SetReferenceToCpp_(long ptr) {
        this.pointerToCpp = ptr;
    }
}
