package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;

import java.util.Vector;

/**
 * [Optional]
 * Design your custom belief by inheriting this class
 */
public abstract class Belief {
    public DSPOMDP model_; // not used as of now in Java end
    public History history_; // not used as of now in Java end
    public long beliefPtr;

    public Belief(DSPOMDP model) {
        this.model_ = model;
    }
    public Belief(long beliefPtr) {
        this.beliefPtr = beliefPtr;
    }

    /**
     * Sample states from a belief.
     * Returns a set of sampled states.
     * Implemented already in c++ end in base class
     * @param num Number of states to be sampled
     * @return vector of State pointers
     */
    protected native Vector<State> Sample_(long ptr, int num);
    protected Vector<State> Sample(int num){
        return Sample_(beliefPtr,num);
    }

    /**
     * Update the belief.
     *
     * @param action The action taken in the last step
     * @param obs    The observation received in the last step
     */
    protected native void Update_(long ptr, int action, long obs);
    protected void Update(int action, long obs) {
        Update_(beliefPtr, action, obs);
    }
//    protected abstract String text();

    /**
     * Returns a copy of this belief
     * @return pointer to the current belief copy
     */
    protected native Belief MakeCopy_(long ptr);
    protected Belief MakeCopy() {
        return MakeCopy_(beliefPtr);
    }
}
