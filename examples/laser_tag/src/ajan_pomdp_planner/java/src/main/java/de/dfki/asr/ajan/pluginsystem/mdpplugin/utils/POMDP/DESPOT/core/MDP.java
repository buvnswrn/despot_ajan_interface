package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;

import java.util.Vector;

public interface MDP {

    int NumStates();
    int NumActions();
    Vector<State> TransitionProbability(int s, int a);
    double Reward(int s, int a);


}
