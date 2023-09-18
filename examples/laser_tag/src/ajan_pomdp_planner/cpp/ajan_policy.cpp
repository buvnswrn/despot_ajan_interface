//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Agent Policy.
// See: examples/laser_tag/include/unified_pomdp_planner/unified_laser_tag.cpp
//

#include "ajan_policy.h"

using namespace despot;
namespace despot {

    AjanPolicy::AjanPolicy(const despot::DSPOMDP *model, despot::ParticleLowerBound *bound) :
                DefaultPolicy(model, bound),
                tag_model_(dynamic_cast<const despot::AjanAgent *>(model)) {
            javaReferenceObject = AjanHelper::getEnv()->NewObject(AjanHelper::getPolicyClass(),
                                                                 AjanHelper::getMethodID(
                                                                         AJAN_POLICY,
                                                                         Init_),
                                                                         reinterpret_cast<jlong>(this));
//            floor_ = tag_model_->floor(); // have to be changed
//        cout<<"ISIDE TAGSHRPolciy"<<endl;
        }

        despot::ACT_TYPE AjanPolicy::Action(const std::vector<despot::State *> &particles, despot::RandomStreams &streams,
                                        despot::History &history) const {
        /**
         * 1. See whether RandomStreams are important or not.
         * 2. Do not pass RandomStreams to JNI \n
         * LOGIC (Laser_Tag): \n
         * 1. If history is empty then take a random move \n
         * 2. Compute rob position \n
         * 3. Compute opp position \n
         * 4. Compute their manhattan distance \n
         * 5. If we just saw an opponent then TAG \n
         * 6. Don't double back and don't go into walls. If one direction is not opposite to history.LastAction \n
         *  and current rob coordinate + Compass::DIRECTIONS(current direction) is Inside the floor \n
         *  (floor.Inside), then add direction to actions variable. \n
         * 7. Have to double back: if there are no actions, then if all four directions are inside the floor, \n
         *  then add directions to actions. \n
         * 8. Robot may be trapped by the obstacles : If still the actions are zero, then return 0 -> Indicating North. \n
         * 9. Else, choose a random action from the computed variables. \n
         */
        jobject javaParticlesObject = AjanHelper::toJavaAgentStateVector(particles, false);
        jobject javaHistoryObject = AjanHelper::toJavaHistory(history);
        return AjanHelper::getEnv()->CallIntMethod(javaReferenceObject,
                                               AjanHelper::getMethodID(AJAN_POLICY,Action_),
                                                           javaParticlesObject, javaHistoryObject);
    }
}