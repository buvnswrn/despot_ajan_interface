package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.example;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.Globals;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanAgent;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanBeliefPolicy;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ValuedAction;

public class TagBlindBeliefPolicy extends AjanBeliefPolicy {

    TagBlindBeliefPolicy(AjanAgent model) {
        super(model);
    }

    @Override
    protected ValuedAction Value(Belief belief) {
        double bestValue = Globals.NEG_INFTY;
        int bestAction =-1;
        for (int action = 0; action < tag_model_.NumActions(); action++) {
            double value = tag_model_.ComputeActionValue(belief.pointerToCpp, tag_model_.agentModelPointer, action);
            if (value > bestValue) {
                bestValue = value;
                bestAction = action;
            }
        }
        return new ValuedAction(bestAction, bestValue);
    }
}
