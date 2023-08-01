//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Belief Policy.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_blind_beliefpolicy.h
//

#ifndef SRC_AJAN_BELIEFPOLICY_H
#define SRC_AJAN_BELIEFPOLICY_H

#include <despot/solver/pomcp.h>
#include <despot/util/floor.h>
#include <despot/util/coord.h>
#include <cmath>
#include <queue>
#include "ajan_agent.h"

namespace despot {
    class AjanBeliefPolicy : public despot::BeliefLowerBound {
    public:
        AjanBeliefPolicy(const despot::AjanAgent *model) ;
        despot::ValuedAction Value(const despot::Belief *belief) const;
    };
}

#endif //SRC_AJAN_BELIEFPOLICY_H
