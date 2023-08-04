package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;
import jdk.jshell.spi.ExecutionControl;

import java.util.Vector;

/**
 * [Optional]
 * Interface for an algorithm computing a lower bound for the maximum total
 * discounted reward over obtainable by a policy on a set of weighted scenarios.
 * The horizon is infinite. The first action that need to be followed to obtain
 * the bound is also returned.
 */
public class ScenarioLowerBound {
    protected DSPOMDP model_;
//    ScenarioLowerBound(const DSPOMDP* model/*, Belief* belief = NULL*/);
//    virtual ~ScenarioLowerBound(){};
//
//	const DSPOMDP* model(){return model_;};
//
//    virtual void Init(const RandomStreams& streams);
//
//    virtual void Learn(VNode* tree);
//    virtual void Reset();

    /**
     * Returns a lower bound for the maximum total discounted reward obtainable
     * by a policy on a set of weighted scenarios. The horizon is infinite. The
     * first action that need to be followed to obtain the bound is also
     * returned.
     *
     * @param particles States in the head of scenarios.
//     * @param streams Random numbers attached to the scenarios.
     * @param history Current action-observation history.
     * @return (a, v), where v is the lower bound and a is the first action needed
     * to obtain the lower bound.
     */
    ValuedAction Value(Vector<State> particles, History history) throws ExecutionControl.NotImplementedException {
        throw new ExecutionControl.NotImplementedException("Value(Vector<State> particles, History history) is not Implemented in Java. Refer C++: despot/src/interface/lower_bound.cpp");
    }
}
