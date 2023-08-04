package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;

import java.util.Vector;

/**
 * [Optional]
 * Design your custom belief by inheriting this class
 */
public abstract class Belief {
    DSPOMDP model_; // not used as of now in Java end
    History history_; // not used as of now in Java end

    public Belief(DSPOMDP model) {

    }
    /**
     * Sample states from a belief.
     * Returns a set of sampled states.
     * Implemented already in c++ end in base class
     * @param num Number of states to be sampled
     * @return vector of State pointers
     */
    protected abstract Vector<State> Sample(int num);

    /**
     * Update the belief.
     *
     * @param action The action taken in the last step
     * @param obs    The observation received in the last step
     */
    protected abstract void Update(int action, long obs);
    protected abstract String text();

    /**
     * Returns a copy of this belief
     * @return pointer to the current belief copy
     */
    protected abstract Belief MakeCopy();
}
