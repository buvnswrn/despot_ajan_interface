package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.example;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanAgentState;

public class LaserTagState extends AjanAgentState {

    LaserTagState(int state_id, int scenario_id, double weight) {
        super(state_id,scenario_id,weight);
    }

    public LaserTagState(int s) {
        super(s);
    }

    public LaserTagState(int state_id, double weight) {
        super(state_id, weight);
    }


}
