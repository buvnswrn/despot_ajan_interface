package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

public abstract class BeliefLowerBound {
    DSPOMDP model_;
    DSPOMDP model() { return model_;}
    // virtual void Learn(VNode* tree);

    /**
     * Returns a lower bound for the maximum total discounted reward obtainable
     * by a policy on a general belief representation. The horizon is infinite.
     * The first action that need to be followed to obtain the bound is also returned.
     * @param belief The current belief to be evaluated.
     */
    protected abstract ValuedAction Value(Belief belief);
}
