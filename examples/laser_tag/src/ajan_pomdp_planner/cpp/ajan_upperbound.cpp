//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for DESPOT Tree Upperbound.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_manhattan_upperbound.cpp
//

#include "ajan_upperbound.h"


namespace despot {
/* ==============================================================================
* AjanUpperBound class
* ==============================================================================*/
    AjanUpperBound::AjanUpperBound(const AjanAgent *model):
    tag_model_(model) {
        // TODO: Implement AjanUpperBound constructor to call JNI
        /**
         * For all States, PreCompute the distance between the rob and opp in value_[state_id]
        **/

    }

    double AjanUpperBound::Value(const despot::State &s) const {
        // Return precomputed value_[state.state_id];
        jobject javaState = AjanHelper::toJavaState(s);
        return AjanHelper::getEnv()->CallDoubleMethod(javaReferenceObject,
                                                      AjanHelper::getEnv()->GetMethodID(
                                                              AjanHelper::getUpperBoundClass(),
                                                              Value_.c_str(),
                                                              Value_State_Double_Sig.c_str()),
                                                              javaState);
    }

    double AjanUpperBound::Value(const despot::Belief *belief) const {
        double value = 0;
        /**
         * Loop through the particles and for each particle (aka. state) sum up the value
            by multiplying current value with pre_computed value_[state.state_id]. Refer paper Guess:Eq.15.
        **/
        jobject javaBelief = AjanHelper::toJavaAjanBelief(belief, nullptr);
        return AjanHelper::getEnv()->CallDoubleMethod(javaReferenceObject,AjanHelper::getMethodID(AJAN_UPPER_BOUND,Value_),javaBelief);
    }
}