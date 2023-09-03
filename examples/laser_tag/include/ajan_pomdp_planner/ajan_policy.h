//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Agent Policy.
// See: examples/laser_tag/include/unified_pomdp_planner/unified_laser_tag.h
//

#include "ajan_agent.h"
#include "ajan_helper.h"
#ifndef SRC_AJAN_POLICY_H
#define SRC_AJAN_POLICY_H

/* ==============================================================================
* TagSHRPolicy class
* ==============================================================================*/
namespace despot {
    using namespace despot;

    class AjanPolicy : public despot::DefaultPolicy {
        const DSPOMDP *tag_model_;
        despot::Floor floor_;
        jobject javaReferenceObject;

    public:
        AjanPolicy(const despot::DSPOMDP *model, despot::ParticleLowerBound *bound);

        despot::ACT_TYPE Action(const std::vector<despot::State *> &particles, despot::RandomStreams &streams,
                                despot::History &history) const;
        jobject javaReferenceObject;
    };

}
#endif //SRC_AJAN_POLICY_H
