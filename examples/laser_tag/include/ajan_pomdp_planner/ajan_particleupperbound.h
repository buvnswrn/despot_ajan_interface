//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Particle UpperBound.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_sp_particleupperbound.h
//

#ifndef SRC_AJAN_PARTICLEUPPERBOUND_H
#define SRC_AJAN_PARTICLEUPPERBOUND_H

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
* AjanParticleUpperBound class
* ==============================================================================*/
    class AjanParticleUpperBound: public despot::ParticleUpperBound { // Shortest path
    protected:
        const despot::AjanAgent *tag_model_;
        std::vector<double> value_;
    public:
        AjanParticleUpperBound(const despot::AjanAgent *model);

        double Value(const despot::State &s) const;
    };
}
#endif //SRC_AJAN_PARTICLEUPPERBOUND_H
