//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for State.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_state.cpp
//

#include "ajan_state.h"

namespace despot {
/* ==============================================================================
 * AjanAgentState class
 * ==============================================================================*/
    AjanAgentState::AjanAgentState() = default;

    AjanAgentState::AjanAgentState(int _state_id) {
        state_id = _state_id;
    }

    std::string AjanAgentState::text() const {
        return to_string(state_id);
    }
}