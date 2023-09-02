package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.*;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.Belief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.DSPOMDP;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;

import java.util.Vector;

public class AjanBelief extends ParticleBelief {

    AjanBelief(Vector<State> particles, DSPOMDP model, Belief prior) {
        super(particles, model, prior, false);
        // TODO: Implement AjanBelief::AjanBelief to call using JNI
    }

    public AjanBelief() {
        super();
    }

    public AjanBelief(long beliefPtr, AjanAgent model, History history, Vector<State> particles)
    {
        super(beliefPtr,model, history,particles);
    }

    @Override
    protected void Update(int action, long obs) {
        // TODO: Implement AjanBelief::Update using JNI
        // WARN: Be careful here (as this affects performance)

        /* call Tau using JNI
         1. Free the particles from the particle belief -> Seems like a typical step
         2. get the updated particles -> Seems like a typical step
         3. Always DESPOT has the history and in Java end We do not have any sort of History to do anything,
         so it's better to do all history related functions here in C++ and not Java.-> Reconsider later
         4. See the AjanAgent::Tau Function
         5. Functional Equivalence: See whether in Tau we can use multiple JNI calls
         to update a single particle instead of copying and sending all of them.
         6. In Java, assign obj=null; System.gc(); to garbage collect the variables.
         */
    }
}
