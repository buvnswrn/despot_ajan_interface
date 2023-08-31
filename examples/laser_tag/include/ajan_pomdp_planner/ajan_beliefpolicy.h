//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Belief Policy.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_blind_beliefpolicy.h
//

#ifndef SRC_AJAN_BELIEFPOLICY_H
#define SRC_AJAN_BELIEFPOLICY_H

#include "ajan_particleupperbound.h"
#include "ajan_upperbound.h"
#include "ajan_policy.h"
#include "ajan_state.h"
#include "ajan_belief.h"
#include <despot/solver/pomcp.h>
#include <despot/util/floor.h>
#include <despot/util/coord.h>
#include <cmath>
#include "ajan_agent.h"
#include <queue>

namespace despot {
/* ==============================================================================
* AjanBeliefPolicy class
* ==============================================================================*/

    class AjanBeliefPolicy : public despot::BeliefLowerBound {
    private:
        std::vector<std::vector<double> > alpha_vectors_; // optional
        const despot::AjanAgent *tag_model_; // optional

    public:
        AjanBeliefPolicy(const despot::AjanAgent *model) ;
        despot::ValuedAction Value(const despot::Belief *belief) const;

        jobject javaReferenceObject;
    };
}

#endif //SRC_AJAN_BELIEFPOLICY_H
