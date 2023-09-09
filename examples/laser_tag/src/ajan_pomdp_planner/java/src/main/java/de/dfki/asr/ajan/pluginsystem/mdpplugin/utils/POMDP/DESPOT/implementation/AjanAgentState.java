package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;

public class AjanAgentState extends State {

    public AjanAgentState(int state_id, int scenario_id, double weight) {
        System.out.println("Creating State Object");
        this.state_id = state_id;
        this.scenario_id = scenario_id;
        this.weight = weight;
    }

    public AjanAgentState(int s) {
        super(s);
    }

    public AjanAgentState(int state_id, double weight) {
        super(state_id, weight);
    }

    @Override
    public String text(int state_id, double weight) {
        // TODO: Implement AjanAgentState::text using JNI
        // return to_string(state_id);
        return null;
    }
}
