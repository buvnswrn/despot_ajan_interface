//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Agent POMDP Model.
// See: examples/laser_tag/include/unified_pomdp_planner/unified_laser_tag.h
//

#ifndef SRC_AJAN_AGENT_H
#define SRC_AJAN_AGENT_H

#include <despot/interface/pomdp.h>
#include <despot/core/mdp.h>
#include <despot/util/coord.h>
#include <despot/util/floor.h>
#include <despot/core/builtin_lower_bounds.h>
#include <despot/core/builtin_policy.h>
#include <despot/core/builtin_upper_bounds.h>
#include <despot/core/particle_belief.h>
#include "ajan_state.h"
#include "ajan_helper.h"
#include "ajan_jni_method_globals.h"
#include "despot_pomdp_globals.h"
#include "ajan_particleupperbound.h"
#include "ajan_beliefpolicy.h"
#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_MDP.h"
#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_implementation_AjanAgent.h"

namespace despot {
/* ==============================================================================
 * AjanAgent class : Similar to UnifiedLaserTag class
 * ==============================================================================*/
class AjanHelper;
class AjanBeliefPolicy;
class AjanAgent: public MDP,
                     public BeliefMDP,
                     public StateIndexer,
                     public StatePolicy,
                     public MMAPInferencer {
        friend class AjanAgentState;
        friend class AjanPolicy;
        friend class AjanParticleUpperBound;
        friend class AjanUpperBound;

    protected:
        mutable MemoryPool<AjanAgentState> memory_pool_;
        std::vector<AjanAgentState*> states_; // optional
        AjanHelper *helper;
        // rob_[s]: robot cell index for state s
        // opp_[s]: opponent cell index for state s


        // region Problem-Specific
    private:
        static int NBEAMS; // optional
        static int BITS_PER_READING; // optional

        double noise_sigma_; // optional
        double unit_size_; // optional
        std::vector<std::vector<std::vector<double> > > reading_distributions_; // optional

    protected:
        // optional
        std::vector<std::vector<std::vector<State> > > transition_probabilities_; //state, action, [state, weight]


    protected:
        std::map<int, double> OppTransitionDistribution(int state) const;

        void ReadConfig(std::istream& is);
        void Init(std::istream& is);

        const AjanAgentState& MostLikelyState(const std::vector<State*>& particles) const;
        void PrintTransitions() const;

    protected:
        std::string RandomMap(int height, int width, int obstacles);
        std::string BenchmarkMap();
        int NextRobPosition(int rob, int opp, ACT_TYPE a) const;

        mutable std::vector<int> default_action_;
        // endregion
    public:

        // region Problem Specific
        static double TAG_REWARD;
        //endregion

        AjanAgent();
        AjanAgent(std::string params_file);
//        virtual ~AjanAgent(); // virtual ~BaseTag();

        // region MDP Functions

        int NumStates() const;
        int NumActions() const;
        const std::vector<State>& TransitionProbability(int s, ACT_TYPE a) const;
        double Reward(int s, ACT_TYPE a) const;

        // endregion

        // region BeliefMDP

        BeliefLowerBound* CreateBeliefLowerBound(std::string name = "DEFAULT") const;
        BeliefUpperBound* CreateBeliefUpperBound(std::string name = "DEFAULT") const;
        /**
        * Transition function for the belief MDP.
        */
        Belief* Tau(const Belief* belief, ACT_TYPE action, OBS_TYPE obs) const;

        /**
        * Observation function for the belief MDP.
        */
        void Observe(const Belief* belief, ACT_TYPE action,
                     std::map<OBS_TYPE, double>& obss) const;

        /**
         * Reward function for the belief MDP.
         */
        double StepReward(const Belief* belief, ACT_TYPE action) const;

        //endregion

        // region StateIndexer

        // NumStates is in region MDP
        int GetIndex(const State* state) const;
        const State* GetState(int index) const;

        // endregion

        // region StatePolicy

        int GetAction(const State& tagstate) const;

        //endregion

        // region MMAPInferencer

        const State* GetMMAP(const std::vector<State*>& particles) const;

        // endregion

        // region POMDP

        bool Step(State& state, double random_num, ACT_TYPE action, double& reward) const;

        bool Step(State& state, double random_num, ACT_TYPE action,
                  double& reward, OBS_TYPE& obs) const;

        // NumActions is in region MDP

        // Reward is in region MDP

        double ObsProb(OBS_TYPE obs, const State& state, ACT_TYPE action) const;

        State* CreateStartState(std::string type = "DEFAULT") const;

        Belief* InitialBelief(const State* start, std::string type = "DEFAULT") const;

        double GetMaxReward() const;

        ValuedAction GetBestAction() const;

        ParticleUpperBound* CreateParticleUpperBound(std::string name = "DEFAULT") const;

        ScenarioUpperBound* CreateScenarioUpperBound(std::string name = "DEFAULT",
                                                     std::string particle_bound_name = "DEFAULT") const;

        // CreateParticleLowerBound not implemented

        ScenarioLowerBound* CreateScenarioLowerBound(std::string name = "DEFAULT",
                                                     std::string particle_bound_name = "DEFAULT") const;

        // CreatePOMCPPrior not implemented

        /* ========================================================================
        * Display
        * ========================================================================*/

        void PrintState(const State& state, std::ostream& out = std::cout) const;
        void PrintObs(const State& state, OBS_TYPE obs, std::ostream& out = std::cout) const;
        void PrintAction(ACT_TYPE action, std::ostream& out = std::cout) const;
        void PrintBelief(const Belief& belief, std::ostream& out = std::cout) const;

        /* ========================================================================
        * Memory management.
        * ========================================================================*/

        State* Allocate(int state_id, double weight) const;
        State* Copy(const State* particle) const;
        // Copy(const std::vector<State*>& particles) not implemeted
        void Free(State* particle) const;
        int NumActiveParticles() const;
        // Makecopy not implemented

        // endregion

        void ComputeDefaultActions(std::string type) const;

        std::string WhichDefaultPolicyToUse() const;
    };

}


#endif //SRC_AJAN_AGENT_H