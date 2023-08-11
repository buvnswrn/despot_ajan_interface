package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

public abstract class State {
    public int state_id;
    public int scenario_id;
    public double weight;

    /**
     * Default State constructor
     */
    public State() {
    }

    /**
     * State constructor
     * @param _state_id id for the state
     * @param weight weight for the state
     */
    public State(int _state_id, double weight) {
        this.weight = weight;
        this.state_id = _state_id;
    }

    /**
     * State constructor (created for laser_tag example)
     * @param _state_id id for the state
     */
    public State(int _state_id) {
        this.state_id = _state_id;
    }

    /**
     * Creates a string to be displayed when state is printed
     * @param state_id id for the state
     * @param weight weight for the state
     * @return string to be displayed
     */
    public abstract String text(int state_id, double weight);
}
