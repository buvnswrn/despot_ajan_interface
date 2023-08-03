//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Belief LowerBound Policy. [Optional Class]
// See: examples/laser_tag/include/unified_pomdp_planner/tag_blind_beliefpolicy.cpp
//

#include "ajan_beliefpolicy.h"
using namespace despot;
/**
 * TODO: Check for using a Flag to use default methods since this is an Optional Class to implement
  **/
namespace despot {
    AjanBeliefPolicy::AjanBeliefPolicy(const despot::AjanAgent *model) :
    BeliefLowerBound(model),
    tag_model_(model){
        // TODO: Implement AjanBeliefPolicy constructor to call JNI and ask for Policy
    }

    despot::ValuedAction AjanBeliefPolicy::Value(const despot::Belief *belief) const {
        double bestValue = despot::Globals::NEG_INFTY;
        int bestAction = -1;
        // TODO: Implement AjanBeliefPolicy::Value to call JNI
        /**
         * Needs to call ComputeActionValue Function of MDP. Check on how to do that.
        **/
        return despot::ValuedAction(bestAction, bestValue);
    }
}