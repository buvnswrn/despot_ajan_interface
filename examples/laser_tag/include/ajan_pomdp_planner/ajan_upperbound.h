//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for DESPOT Tree Upperbound.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_manhattan_upperbound.h
//

#ifndef SRC_AJAN_UPPERBOUND_H
#define SRC_AJAN_UPPERBOUND_H

#include "ajan_policy.h"
#include "ajan_state.h"
#include "ajan_belief.h"
#include <despot/solver/pomcp.h>
#include <despot/util/floor.h>
#include <despot/util/coord.h>
#include <cmath>
#include "ajan_agent.h"
#include <queue>
#include "ajan_jni_method_globals.h"
namespace despot {
/* ==============================================================================
* AjanUpperBound class
* ==============================================================================*/

    class AjanUpperBound : public despot::ParticleUpperBound, public despot::BeliefUpperBound {
    protected:
        const DSPOMDP *tag_model_;
        std::vector<double> value_;
    public:
        AjanUpperBound(const DSPOMDP *model);
//        AjanUpperBound();

        using ParticleUpperBound::Value;

        double Value(const despot::State &s) const ;

        using BeliefUpperBound::Value;

        double Value(const despot::Belief *belief) const ;

        jobject javaReferenceObject;
    };

}
#endif //SRC_AJAN_UPPERBOUND_H
