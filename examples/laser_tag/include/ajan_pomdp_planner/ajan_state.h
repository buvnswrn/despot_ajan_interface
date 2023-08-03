//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for State.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_state.h
//

#ifndef SRC_AJAN_STATE_H
#define SRC_AJAN_STATE_H

#include <despot/core/particle_belief.h>
#include <despot/core/builtin_upper_bounds.h>
#include <despot/core/builtin_policy.h>
#include <despot/core/builtin_lower_bounds.h>
#include <despot/util/floor.h>
#include <despot/util/coord.h>
#include <despot/core/mdp.h>
#include <despot/interface/pomdp.h>

namespace despot {
/* ==============================================================================
 * AjanState class
 * ==============================================================================*/

    class AjanAgentState : public despot::State {
    public:
        AjanAgentState();

        AjanAgentState(int _state_id);

        std::string text() const;
    };
}

#endif //SRC_AJAN_STATE_H
