package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;
import jdk.jshell.spi.ExecutionControl;

import java.util.Vector;

public interface ScenarioUpperBound {
    /**
     * Returns a upper bound for the maximum total discounted reward
     * on a set of weighted scenarios. The horizon is infinite.
     *
     * @param particles States in the head of scenarios.
//     * @param streams Random numbers attached to the scenarios.
     * @param history Current action-observation history.
     */
    double Value(Vector<State> particles, History history) throws ExecutionControl.NotImplementedException;
}
