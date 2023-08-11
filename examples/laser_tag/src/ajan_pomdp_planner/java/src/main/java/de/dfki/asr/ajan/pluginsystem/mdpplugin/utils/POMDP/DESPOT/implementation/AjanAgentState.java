package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;

public class AjanAgentState extends State {

    AjanAgentState(int state_id, int scenario_id, double weight) {
        this.state_id = state_id;
        this.scenario_id = scenario_id;
        this.weight = weight;
    }

    @Override
    public String text(int state_id, double weight) {
        // TODO: Implement AjanAgentState::text using JNI
        // return to_string(state_id);
        return null;
    }
}
