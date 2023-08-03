//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Agent POMDP Model.
// See: examples/laser_tag/include/unified_pomdp_planner/unified_laser_tag.cpp
//

#include "ajan_agent.h"

using namespace std;
namespace despot {
/* ==============================================================================
 * AjanAgent class : Similar to UnifiedLaserTag class
 * ==============================================================================*/

    AjanAgent::AjanAgent() {
        // TODO: Implement AjanAgent constructor to call JNI
        // read the Benchmark map
        // run init function
    }

    //region MDP Functions

    int AjanAgent::NumStates() const {
        // TODO: Implement AjanAgent::NumStates to call JNI
        // Return number of cells
        return 0;
    }

    int AjanAgent::NumActions() const {
        // TODO: Implement AjanAgent::NumStates to call JNI
        // Return number of actions
        return 0;
    }

    const std::vector<State> &AjanAgent::TransitionProbability(int s, ACT_TYPE a) const {
        // TODO: Implement AjanAgent::TransitionProbability to call JNI
        // return transition_probabilities_[s][a];
        return vector<State>();
    }

    double AjanAgent::Reward(int s, ACT_TYPE a) const {
        // TODO: Implement AjanAgent::TransitionProbability to call JNI
        // If action is tag, and tagged -> tag reward else - tag reward else reward  = -1 (longer it takes, lower is the reward)
        return 0;
    }
    //endregion

    //region BeliefMDP
    BeliefLowerBound *AjanAgent::CreateBeliefLowerBound(std::string name) const {
        // TODO: Implement AjanAgent::CreateBeliefLowerBound to call JNI
        // OPTIMIZE: Check how to use built-in bounds
        /**
         * Use some built-in bound - TrivialBeliefLowerBound
        **/
        return BeliefMDP::CreateBeliefLowerBound(name);
    }

    BeliefUpperBound *AjanAgent::CreateBeliefUpperBound(std::string name) const {
        // TODO: Implement AjanAgent::CreateBeliefUpperBound to call JNI
        // OPTIMIZE: Check how to use built-in bounds
        /**
         * Use some built-in bound - MDPUpperBound, TrivialBeliefUpperBound, LookaheadUpperBound (Scenario Upperbound)
        **/
        return BeliefMDP::CreateBeliefUpperBound(name);
    }

    Belief *AjanAgent::Tau(const Belief *belief, ACT_TYPE action, OBS_TYPE obs) const {
        // TODO: Implement AjanAgent::Tau to call JNI
        // WARN: See how to manipulate belief and history particles efficiently
        /**
         * Calculates the sum of current weight * next weight * observation probability given state and action.
         * Updates the particles and creates new belief
         */
        return nullptr;
    }

    void AjanAgent::Observe(const Belief *belief, ACT_TYPE action, map<OBS_TYPE, double> &obss) const {
        // TODO: Implement AjanAgent::Observe to call JNI
        // Not real implementation here just "too many observations" print message
    }

    double AjanAgent::StepReward(const Belief *belief, ACT_TYPE action) const {
        // TODO: Implement AjanAgent::StepReward to call JNI
        // WARN: Careful about the history manipulation
        // Calculate the cumulative reward until here according to the actions given.
        return 0;
    }

    //endregion

    //region StateIndexer
        // inline functions
    int AjanAgent::GetIndex(const State* state) const {
        // TODO: Implement AjanAgent::GetIndex to call JNI
        //return state->state_id;
        return 0;
    }
    const State* AjanAgent::GetState(int index) const {
        // TODO: Implement AjanAgent::GetState to call JNI
        //return states_[index];
        return nullptr;
    }

    //endregion

    //region StatePolicy
    int AjanAgent::GetAction(const State &tagstate) const {
        // TODO: Implement AjanAgent::GetAction to call JNI
        // return default_action_[GetIndex(state)]
        return 0;
    }
    //endregion

    //region MMAPInferencer
    const State *AjanAgent::GetMMAP(const vector<State *> &particles) const {
        // TODO: Implement AjanAgent::GetMMAP to call JNI
        /**
         * 1. Calculate most likely rob and opp position coordinate
         * 2. Calculate the indices of both robots to state index
         * 3. return the state variable stored for the particular index
         */
        return nullptr;
    }
    //endregion

    //region POMDP
    bool AjanAgent::Step(State &state, double random_num, ACT_TYPE action, double &reward) const {
        //TODO: Implement AjanAgent::Step function to call JNI
        /**
         * 1. Compute the reward after calculating the distance of rob and opp \n
         * 2. Compute the sum of weight for random_num of next states and get the state_id of state that has greater weight than the calculated sum \n
         * 3. Assign the given state to be the calculated state_id \n
         * 4. return terminal=true if the tag is done.
         */
        return DSPOMDP::Step(state, random_num, action, reward);
    }

    bool AjanAgent::Step(State &state, double random_num, ACT_TYPE action, double &reward, OBS_TYPE &obs) const {
        //TODO: Implement AjanAgent::Step function to call JNI
        /**
         * 1-4. Repeat the steps like for above step function \n
         * 5. Update the observation as 101 if the terminal has reached or rob and opp is in same state_id i.e. same cell,
         * else, update the observation:
         * for each the direction deduct the mass based on the reading_distribution until it is less than Globals::TINY and then set the reading to observation variable.
         */
        return false;
    }

    double AjanAgent::ObsProb(OBS_TYPE obs, const State &state, ACT_TYPE action) const {
        //TODO: Implement AjanAgent::ObsProb function to call JNI
        double prod = 1.0;
        /**
         * 1. Update the observation if rob and opp has same state_id
         * 2. Get the reading in each direction and return 0 if the reading is greater than the LaserRange of the state in that particular direction, else, multiply the probability mass based on the stored reading_distribution for that state, dir and reading.
         */
        return prod;
    }

    State *AjanAgent::CreateStartState(std::string type) const {
        //TODO: Implement AjanAgent::CreateStartState function to call JNI
        //return a random state
        int n = Random::RANDOM.NextInt(states_.size());
        return new AjanAgentState(*states_[n]);
    }

    Belief *AjanAgent::InitialBelief(const State *start, std::string type) const {
        //TODO: Implement AjanAgent::InitialBelief function to call JNI
        /**
         * Update the particles with rob and opp particle weight and create a particle belief with it.
         */
        return nullptr;
    }

    double AjanAgent::GetMaxReward() const {
        // TODO: Implement AjanAgent::GetMaxReward function to call JNI
        // return TAG_REWARD;
        return 0;
    }

    ValuedAction AjanAgent::GetBestAction() const {
        // TODO: Implement AjanAgent::GetMaxReward function to call JNI
        //return ValuedAction(0, -1);
        return ValuedAction(0, 0);
    }

    ParticleUpperBound *AjanAgent::CreateParticleUpperBound(std::string name) const {
        //TODO: Implement AjanAgent::CreateParticleUpperBound function to call JNI
        /**
         * Based on the name given, initialize TrivialParticleUpperBound,MDPUpperBound or custom upperbound
         */
        return DSPOMDP::CreateParticleUpperBound(name);
    }

    ScenarioUpperBound *AjanAgent::CreateScenarioUpperBound(std::string name, std::string particle_bound_name) const {
        //TODO: Implement AjanAgent:: function to call JNI
        /**
         * Based on the name given, initialize LookaheadUpperBound or custom upperbound.
         */
        return DSPOMDP::CreateScenarioUpperBound(name, particle_bound_name);
    }

    ScenarioLowerBound *AjanAgent::CreateScenarioLowerBound(std::string name, std::string particle_bound_name) const {
        //TODO: Implement AjanAgent::CreateScenarioUpperBound function to call JNI
        /**
         * Based on the name given, initialize TrivialParticleLowerBound,RandomPolicy or custom upperbound. If the same_loc_obs_ is not equal to number of cells on the floor, then use custom policy.
         * else, compute the default actions based on MDP or SP and use MMAPStatePolicy or ModeStatePolicy or MajorityActionPolicy.
         */
        return DSPOMDP::CreateScenarioLowerBound(name, particle_bound_name);
    }

    void AjanAgent::PrintState(const State &state, ostream &out) const {
        //TODO: Implement AjanAgent::PrintState function to call JNI

    }

    void AjanAgent::PrintObs(const State &state, OBS_TYPE obs, ostream &out) const {
        //TODO: Implement AjanAgent::PrintObs function to call JNI

    }

    void AjanAgent::PrintAction(ACT_TYPE action, ostream &out) const {
        //TODO: Implement AjanAgent::PrintAction function to call JNI

    }

    void AjanAgent::PrintBelief(const Belief &belief, ostream &out) const {
        //TODO: Implement AjanAgent::PrintBelief function to call JNI

    }

    State *AjanAgent::Allocate(int state_id, double weight) const {
        //TODO: Implement AjanAgent::Allocate function to call JNI
        return nullptr;
    }

    State *AjanAgent::Copy(const State *particle) const {
        //TODO: Implement AjanAgent::Copy function to call JNI
        return nullptr;
    }

    void AjanAgent::Free(State *particle) const {
        //TODO: Implement AjanAgent::Free function to call JNI

    }

    int AjanAgent::NumActiveParticles() const {
        //TODO: Implement AjanAgent::NumActiveParticles function to call JNI
        return 0;
    }
    //endregion
}