package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;

import java.util.Vector;

public abstract class DefaultPolicy extends ScenarioLowerBound {

    /**
     * Returns an action based on the weighted scenarios and the history
     *
     * @param particles States in the head of the scenarios
//     * @param streams   Random streams attached to the scenarios
     * @param history   The current action-observation history
     */
    protected abstract int Action(Vector<State> particles, History history);
}
