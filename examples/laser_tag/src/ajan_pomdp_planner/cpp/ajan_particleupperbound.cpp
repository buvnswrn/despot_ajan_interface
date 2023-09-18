//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Particle UpperBound and Belief UpperBound.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_sp_particleupperbound.h
//

#include "ajan_particleupperbound.h"
namespace despot {
using namespace despot;

    AjanParticleUpperBound::AjanParticleUpperBound(const DSPOMDP *model):
    tag_model_(model) { // Changed from AjanAgent to DSPOMDP and it works well
        // TODO: Implement AjanParticleUpperBound constructor to call JNI
        // store the distance between rob and opponent in value_[state.state_id]
        /**
         * This is implementing both particle and belief upperbound. So, try to separate them.
        **/
    }

    double AjanParticleUpperBound::Value(const despot::State &s) const {
        // TODO: Implement AjanParticleUpperBound::Value Function for Particle to call JNI.
        // Return precomputed value_[state.state_id];
        jobject javaState = AjanHelper::toJavaState(s);
        return AjanHelper::getEnv()->CallDoubleMethod(javaReferenceObject, AjanHelper::getMethodID(AJAN_PARTICLE_UPPER_BOUND,Value_), javaState);
    }

}