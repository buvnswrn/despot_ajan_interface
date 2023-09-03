package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ParticleLowerBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ValuedAction;

import java.util.Vector;
@Deprecated // Added for future use and reduce JNI Errors
public class AjanParticleLowerBound extends ParticleLowerBound {

    AjanParticleLowerBound(AjanAgent model){
        this.agent_model = model;
    }
    @Override
    protected ValuedAction Value(Vector<State> particles_p, History history) {
        return null;
    }
}
