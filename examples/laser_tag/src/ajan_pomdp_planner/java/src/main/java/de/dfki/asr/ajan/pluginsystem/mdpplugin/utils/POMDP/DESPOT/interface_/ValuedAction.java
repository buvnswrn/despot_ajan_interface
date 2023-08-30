package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

public class ValuedAction {
    public int action;
    double value;

    public ValuedAction(int action, double _value) {
        this.action = action;
        this.value = _value;
    }

    public ValuedAction() {
        action = -1;
        value = 0;
    }
}
