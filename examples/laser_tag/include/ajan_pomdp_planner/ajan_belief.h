//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Beliefs.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_belief.h
//

#ifndef SRC_AJAN_BELIEF_H
#define SRC_AJAN_BELIEF_H
#include "ajan_agent.h"

namespace despot {
/* ==============================================================================
* AjanBelief class
* ==============================================================================*/

    class AjanBelief : public despot::ParticleBelief {
    const despot::AjanAgent *tag_model_;
public:
        [[maybe_unused]] [[maybe_unused]] AjanBelief(std::vector<despot::State *> particles, const despot::AjanAgent *model, Belief *prior =
    nullptr);

    void Update(despot::ACT_TYPE action, despot::OBS_TYPE obs) override;
    };

}

#endif //SRC_AJAN_BELIEF_H
