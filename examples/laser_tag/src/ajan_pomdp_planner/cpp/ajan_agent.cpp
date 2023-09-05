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
    //region MDP Functions

    int AjanAgent::NumStates() const {
        // TODO: Implement AjanAgent::NumStates to call JNI
        // Return number of cells
        return AjanHelper::getEnv()->CallIntMethod(helper->getAjanJavaAgentObject(),
                                              AjanHelper::getMethodID(AJAN_AGENT,NumStates_));
    }

    int AjanAgent::NumActions() const {
        // TODO: Implement AjanAgent::NumStates to call JNI
        // Return number of actions
        return AjanHelper::getEnv()->CallIntMethod(helper->getAjanJavaAgentObject(),
                                                   AjanHelper::getMethodID(AJAN_AGENT,NumActions_));
    }

    const std::vector<State> &AjanAgent::TransitionProbability(int s, ACT_TYPE a) const {
        static vector<State > vectorOfStates;
        vectorOfStates.clear();
        // TODO: Implement AjanAgent::TransitionProbability to call JNI
        // return transition_probabilities_[s][a];
        jobject transProb = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                                   AjanHelper::getMethodID(AJAN_AGENT,TransitionProbability_),s,a);
        vectorOfStates= AjanHelper::fromJavaAgentStateVector(transProb);
        return vectorOfStates;
    }

    double AjanAgent::Reward(int s, ACT_TYPE a) const {
        // TODO: Implement AjanAgent::TransitionProbability to call JNI
        // If action is tag, and tagged -> tag reward else - tag reward else reward  = -1 (longer it takes, lower is the reward)
        return AjanHelper::getEnv()->CallDoubleMethod(helper->getAjanJavaAgentObject(),
                                                      AjanHelper::getMethodID(AJAN_AGENT,Reward_),s, a);
    }
    //endregion

    //region BeliefMDP
    BeliefLowerBound *AjanAgent::CreateBeliefLowerBound(std::string name) const {
        // TODO: Implement AjanAgent::CreateBeliefLowerBound to call JNI
        // OPTIMIZE: Check how to use built-in bounds
        /**
         * Use some built-in bound - TrivialBeliefLowerBound
        **/
        if (name == TRIVIAL) {
            return new TrivialBeliefLowerBound(this);
        } else if (name == DEFAULT || name == BLIND) {
            auto * beliefPolicy = new AjanBeliefPolicy(this);
//            jobject beliefLowerBoundObject = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
//                                                                                    AjanHelper::getMethodID(AJAN_AGENT,CreateBeliefLowerBound_),name.c_str(), reinterpret_cast<jlong>(beliefPolicy));
//            beliefPolicy->javaReferenceObject = beliefLowerBoundObject; //uncheck this if the above creation doesn't work
            // send back the cpp reference as well
            return beliefPolicy;
        } else {
            cerr << "Unsupported belief lower bound: " << name << endl;
            exit(1);
            return nullptr;
        }
    }

    BeliefUpperBound *AjanAgent::CreateBeliefUpperBound(std::string name) const {
        // TODO: Implement AjanAgent::CreateBeliefUpperBound to call JNI
        // OPTIMIZE: Check how to use built-in bounds
        if (name == TRIVIAL) {
            return new TrivialBeliefUpperBound(this);
        } else if (name == DEFAULT || name == MDP_) {
            return new MDPUpperBound(this, *this);
        }
//      else if (name == LOOKAHEAD) {
//            return new LookaheadUpperBound(this,*this); // Cannot use this here as of this writing, needs particle upperbound. Will look into this when it's extremely needed.
//        }
        else if (name == MANHATTAN || name == AJAN) {
            auto * ajanUpperBound = new AjanUpperBound(this);
            jobject beliefUpperBound = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                                              AjanHelper::getMethodID(AJAN_AGENT,CreateBeliefUpperBound_), name.c_str(),reinterpret_cast<jlong>(ajanUpperBound));
            if(beliefUpperBound == nullptr) {
                cerr << "Cannot get belief upper bound: " << name << endl;
                return nullptr;
            }
            ajanUpperBound->javaReferenceObject = beliefUpperBound; // Update reference to java object
            return new AjanUpperBound(this);
        } else {
            if (name != "print")
                cerr << "Unsupported belief upper bound: " << name << endl;
            cerr << "Supported types: TRIVIAL, MDP, MANHATTAN (default to MDP)" << endl;
            exit(1);
            return nullptr;
        }
    }

    Belief *AjanAgent::Tau(const Belief *belief, ACT_TYPE action, OBS_TYPE obs) const {
        // TODO: Implement AjanAgent::Tau to call JNI
        // WARN: See how to manipulate belief and history particles efficiently
        /**
         * Calculates the sum of current weight * next weight * observation probability given state and action.
         * Updates the particles and creates new belief
         */
        jobject javaBelief = AjanHelper::toJavaAjanBelief(belief); // when it is sent back, java reference is not available
        jobject returnBelief = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                               AjanHelper::getMethodID(AJAN_AGENT, Tau_),javaBelief,action,obs);
        // TODO: Have to work more in here - not sure until now how to manipulate or convert to and from particle belief and so on
        return AjanHelper::newBeliefFromAjanBelief(returnBelief,this, nullptr); // Whenevr you send, send a AjanBelief, so it has the java object
    }

    void AjanAgent::Observe(const Belief *belief, ACT_TYPE action, map<OBS_TYPE, double> &obss) const {
        // TODO: Change the implmentation or test it when actual logic is written for the Observe function
        jobject javaAjanBelief = AjanHelper::toJavaAjanBelief(belief); // Conversion might not be needed.
        jobject javaObsMap = AjanHelper::toJavaLongDoubleMap(obss);
        AjanHelper::getEnv()->CallVoidMethod(helper->getAjanJavaAgentObject(),
                                             AjanHelper::getMethodID(AJAN_AGENT,Observe_),javaAjanBelief,action,javaObsMap); // since return is void we can simply return obss variable back that is updated and use here. Not sure whether & acts a pointer
        // Not real implementation here just "too many observations" print message
    }

    double AjanAgent::StepReward(const Belief *belief, ACT_TYPE action) const {
        // TODO: Implement AjanAgent::StepReward to call JNI
        // WARN: Careful about the history manipulation
        // Calculate the cumulative reward until here according to the actions given.
        // Consider passing belief as a memory address
        jobject javaBelief = AjanHelper::toJavaAjanBelief(belief);
        return AjanHelper::getEnv()->CallDoubleMethod(helper->getAjanJavaAgentObject(),
                                               AjanHelper::getMethodID(AJAN_AGENT,StepReward_),javaBelief,action);
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
        jobject ajanState = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                                   AjanHelper::getMethodID(AJAN_AGENT,GetState_),index);
        const State * statePtr = new State(AjanHelper::fromJavaState(ajanState));
        return statePtr;
    }

    //endregion

    //region StatePolicy
    int AjanAgent::GetAction(const State &tagstate) const {
        // TODO: Implement AjanAgent::GetAction to call JNI
        // return default_action_[GetIndex(state)]
        jobject agentState = AjanHelper::toJavaAjanAgentState((AjanAgentState &&) tagstate);
        return AjanHelper::getEnv()->CallIntMethod(helper->getAjanJavaAgentObject(),
                                                   AjanHelper::getMethodID(AJAN_AGENT,GetAction_), agentState);
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
         jobject javaParticles = AjanHelper::toJavaAgentStateVector(particles);
         jobject javaState =  AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                       AjanHelper::getMethodID(AJAN_AGENT,GetMMAP_),javaParticles);
        auto * returnState = new State(AjanHelper::fromJavaState(javaState));
        return returnState;
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
         jobject javaState = AjanHelper::toJavaAjanAgentState(dynamic_cast<const AjanAgentState &>(state));
         bool returnValue = AjanHelper::getEnv()->CallBooleanMethod(helper->getAjanJavaAgentObject(),
                                                        AjanHelper::getEnv()->GetMethodID(AjanHelper::getAgentClass(),Step_.c_str(),
                                                                                          ("("+getSig(STATE)+"DID)Z").c_str()),javaState,random_num,action,reward);
        jobject javaAgentState = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                                        AjanHelper::getMethodID(AJAN_AGENT,GetCurrentState_Agent));
        state = AjanHelper::fromJavaState(javaAgentState);
        reward = AjanHelper::getEnv()->CallDoubleMethod(helper->getAjanJavaAgentObject(),
                                                        AjanHelper::getMethodID(AJAN_AGENT,GetCurrentReward_Agent));
        return returnValue;
    }

    bool AjanAgent::Step(State &state, double random_num, ACT_TYPE action, double &reward, OBS_TYPE &obs) const {
        //TODO: Implement AjanAgent::Step function to call JNI
        /**
         * 1-4. Repeat the steps like for above step function \n
         * 5. Update the observation as 101 if the terminal has reached or rob and opp is in same state_id i.e. same cell,
         * else, update the observation:
         * for each the direction deduct the mass based on the reading_distribution until it is less than Globals::TINY and then set the reading to observation variable.
         */
         jobject javaState = AjanHelper::toJavaAjanAgentState(dynamic_cast<const AjanAgentState &>(state));
         bool returnValue = AjanHelper::getEnv()->CallBooleanMethod(helper->getAjanJavaAgentObject(),AjanHelper::getMethodID(AJAN_AGENT,Step_),javaState,random_num, action, reward, obs); // TODO: Set values of obs and reward here
         obs = AjanHelper::getEnv()->CallLongMethod(helper->getAjanJavaAgentObject(),
                                                    AjanHelper::getMethodID(AJAN_AGENT,GetCurrentObservation_Agent));
         reward = AjanHelper::getEnv()->CallDoubleMethod(helper->getAjanJavaAgentObject(),
                                                         AjanHelper::getMethodID(AJAN_AGENT,GetCurrentReward_Agent));
         action = AjanHelper::getEnv()->CallIntMethod(helper->getAjanJavaAgentObject(),
                                                      AjanHelper::getMethodID(AJAN_AGENT,GetCurrentAction_Agent));
         jobject javaAgentState = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                                         AjanHelper::getMethodID(AJAN_AGENT,GetCurrentState_Agent));
         state = AjanHelper::fromJavaState(javaAgentState);
         return returnValue;
    }

    double AjanAgent::ObsProb(OBS_TYPE obs, const State &state, ACT_TYPE action) const {
        //TODO: Implement AjanAgent::ObsProb function to call JNI
        jobject s = AjanHelper::toJavaAjanAgentState((AjanAgentState &&) state);
        return AjanHelper::getEnv()->CallDoubleMethod(helper->getAjanJavaAgentObject(),
                                               AjanHelper::getMethodID(AJAN_AGENT,ObsProb_),obs,s,action);
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
         jobject javaState = AjanHelper::toJavaAjanAgentState((AjanAgentState &&) start);
         jobject returnBelief = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                AjanHelper::getMethodID(AJAN_AGENT, InitialBelief_),javaState, type.c_str());
         AjanBelief * ajanBelief = AjanHelper::newBeliefFromAjanBelief(returnBelief,this, nullptr);
         ajanBelief->state_indexer(this);
        return ajanBelief;
    }

    double AjanAgent::GetMaxReward() const {
        // TODO: Implement AjanAgent::GetMaxReward function to call JNI
        // return TAG_REWARD;
        return AjanHelper::getEnv()->CallDoubleMethod(helper->getAjanJavaAgentObject(),
                                                      AjanHelper::getMethodID(AJAN_AGENT,GetMaxReward_));
    }

    ValuedAction AjanAgent::GetBestAction() const {
        // TODO: Implement AjanAgent::GetMaxReward function to call JNI
        //return ValuedAction(0, -1);
        jobject returnValuedAction = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                                            AjanHelper::getMethodID(AJAN_AGENT,GetBestAction_));
        return AjanHelper::fromJavaValuedAction(returnValuedAction);
    }

    ParticleUpperBound *AjanAgent::CreateParticleUpperBound(std::string name) const {
        //TODO: Implement AjanAgent::CreateParticleUpperBound function to call JNI
        /**
         * Based on the name given, initialize TrivialParticleUpperBound,MDPUpperBound or custom upperbound
         */
        if (name == TRIVIAL) {
            return  new TrivialParticleUpperBound(this);
        } else if (name == MDP_) {
            return new MDPUpperBound(this, *this);
        } else if (name == SP || name == DEFAULT || name == MANHATTAN || name == AJAN) {
            auto * particleUpperBound = new AjanParticleUpperBound(this);
            jobject javaParticleUpperBound = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                AjanHelper::getMethodID(AJAN_AGENT,CreateParticleUpperBound_),
                                                                    name.c_str(),
                                                                    reinterpret_cast<jlong>(particleUpperBound));
            if(javaParticleUpperBound == nullptr) {
                cerr << "Cannot get belief upper bound: " << name << endl;
                return nullptr;
            }
            particleUpperBound->javaReferenceObject = javaParticleUpperBound;
            return particleUpperBound; // WARN:Changed the type from ajan agent to DSPOMDP
        } else {
            if (name != "print")
                cerr << "Unsupported particle lower bound: " << name << endl;
            cerr << "Supported types: TRIVIAL, MDP, SP, MANHATTAN (default to SP)" << endl;
            exit(1);
            return nullptr;
        }
        return DSPOMDP::CreateParticleUpperBound(name);
    }

    ScenarioUpperBound *AjanAgent::CreateScenarioUpperBound(std::string name, std::string particle_bound_name) const {
        //TODO: Implement AjanAgent:: function to call JNI
        /**
         * Based on the name given, initialize LookaheadUpperBound or custom upperbound.
         */
        if(name == TRIVIAL || name == DEFAULT || name == MDP_ ||
           name == SP || name == MANHATTAN) {
            return CreateParticleUpperBound(name);
        } else if (name == LOOKAHEAD) {
            return new LookaheadUpperBound(this, *this, CreateParticleUpperBound(particle_bound_name));
        } else {
            if (name != "print")
                cerr << "Unsupported upper bound: " << name << endl;
            cerr << "Supported types: TRIVIAL, MDP, SP, MANHATTAN, LOOKAHEAD (default to SP)" << endl;
            cerr << "With base upper bound: LOOKAHEAD" << endl;
            exit(1);
            return nullptr;
        }
    }

    ScenarioLowerBound *AjanAgent::CreateScenarioLowerBound(std::string name, std::string particle_bound_name) const {
        //TODO: Implement AjanAgent::CreateScenarioUpperBound function to call JNI
        /**
         * Based on the name given, initialize TrivialParticleLowerBound,RandomPolicy or custom upperbound. If the same_loc_obs_ is not equal to number of cells on the floor, then use custom policy.
         * else, compute the default actions based on MDP or SP and use MMAPStatePolicy or ModeStatePolicy or MajorityActionPolicy.
         */
         const DSPOMDP* model = this;
         const StateIndexer* indexer = this;
         const StatePolicy* policy = this;
         const MMAPInferencer* mmap_inferencer = this;
         if(name == TRIVIAL) {
             return new TrivialParticleLowerBound(model);
         } else if (name == RANDOM) {
             return new RandomPolicy(model, CreateParticleLowerBound(particle_bound_name));
         } else if ( name == SHR || name == AJAN) {
             // have to check for smae_loc_obs_ to be equal or not and then use it. May be use computedefault actions and use this one
             auto * ajanPolicy = new AjanPolicy(model, CreateParticleLowerBound(particle_bound_name));
//             jobject javaAjanPolicy = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
//                                AjanHelper::getMethodID(AJAN_AGENT,CreateScenarioLowerBound_),
//                                                                    name.c_str(),
//                                                                    particle_bound_name.c_str(),
//                                                                    reinterpret_cast<jlong>(ajanPolicy)); // uncomment this if the above constructor call doesn't work
//             if(javaAjanPolicy == nullptr) {
//                 cerr << "Cannot get belief upper bound: " << name << endl;
//                 return nullptr;
//             }
//             ajanPolicy->javaReferenceObject = javaAjanPolicy;
             return ajanPolicy;
         } else if(name == MMAP_MDP){
             ComputeDefaultActions(MDP_);
             return new MMAPStatePolicy(model, *mmap_inferencer, *policy, CreateParticleLowerBound(particle_bound_name));
         } else if (name == MMAP_SP){
             ComputeDefaultActions(SP);
             return new MMAPStatePolicy(model, *mmap_inferencer, *policy, CreateParticleLowerBound(particle_bound_name));
         } else if (name == MODE_MDP){
             ComputeDefaultActions(MDP_);
             return new ModeStatePolicy(model, *indexer, *policy, CreateParticleLowerBound(particle_bound_name));
         } else if (name == MODE_SP) {
             ComputeDefaultActions(SP);
             return new ModeStatePolicy(model, *indexer, *policy,
                                        CreateParticleLowerBound(particle_bound_name));
         } else if (name == MAJORITY_MDP) {
             ComputeDefaultActions(MDP_);
             return new MajorityActionPolicy(model, *policy,
                                             CreateParticleLowerBound(particle_bound_name));
         } else if (name == MAJORITY_SP) {
             ComputeDefaultActions(SP);
             return new MajorityActionPolicy(model, *policy,
                                             CreateParticleLowerBound(particle_bound_name));
         } else if (name == DEFAULT) {
             string policyToUse = WhichDefaultPolicyToUse(); // Ask AJAN on which policy to use and use it. Calculate whether same_loc_obs is equal or not there.
             if(policyToUse == AJAN){
             auto * ajanPolicy = new AjanPolicy(model, CreateParticleLowerBound(particle_bound_name));
                 jobject javaAjanPolicy = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                                                                 AjanHelper::getMethodID(AJAN_AGENT,CreateScenarioLowerBound_),
                                                                                 name.c_str(),
                                                                                 particle_bound_name.c_str(),
                                                                                 reinterpret_cast<jlong>(ajanPolicy));
                 if(javaAjanPolicy == nullptr) {
                     cerr << "Cannot get belief upper bound: " << name << endl;
                     return nullptr;
                 }
                 ajanPolicy->javaReferenceObject = javaAjanPolicy;
                 return ajanPolicy; // changed AjanAgent model to DSPOMDP model
             } else if (policyToUse == MODE_MDP) {
                 ComputeDefaultActions(MDP_);
                 return new ModeStatePolicy(model, *indexer, *policy, CreateParticleLowerBound(particle_bound_name));
             }
         } else {
             if (name != "print")
                 cerr << "Unsupported lower bound: " << name << endl;
             cerr << "Supported types: TRIVIAL, RANDOM, SHR, MODE-MDP, MODE-SP, MAJORITY-MDP, MAJORITY-SP (default to MODE-MDP)" << endl;
             cerr << "With base lower bound: except TRIVIAL" << endl;
             exit(1);
         }
        return nullptr;
    }

    void AjanAgent::PrintState(const State &state, ostream &out) const {
        //TODO: Implement AjanAgent::PrintState function to call JNI
        jobject javaState = AjanHelper::toJavaAjanAgentState((AjanAgentState &&) state);
        AjanHelper::getEnv()->CallVoidMethod(helper->getAjanJavaAgentObject(),
                                             AjanHelper::getMethodID(AJAN_AGENT, PrintState_),javaState);
    }

    void AjanAgent::PrintObs(const State &state, OBS_TYPE obs, ostream &out) const {
        //TODO: Implement AjanAgent::PrintObs function to call JNI
        jobject javaState = AjanHelper::toJavaAjanAgentState((AjanAgentState &&) state);
        AjanHelper::getEnv()->CallVoidMethod(helper->getAjanJavaAgentObject(),
                                             AjanHelper::getMethodID(AJAN_AGENT, PrintObs_),javaState,obs);
    }

    void AjanAgent::PrintAction(ACT_TYPE action, ostream &out) const {
        //TODO: Implement AjanAgent::PrintAction function to call JNI
        AjanHelper::getEnv()->CallVoidMethod(helper->getAjanJavaAgentObject(),
                                             AjanHelper::getMethodID(AJAN_AGENT, PrintAction_),action);
    }

    void AjanAgent::PrintBelief(const Belief &belief, ostream &out) const {
        //TODO: Implement AjanAgent::PrintBelief function to call JNI
        jobject javaBelief = AjanHelper::toJavaAjanBelief(&belief);
        AjanHelper::getEnv()->CallVoidMethod(helper->getAjanJavaAgentObject(),
                                             AjanHelper::getMethodID(AJAN_AGENT, PrintBelief_),javaBelief);
    }

    State *AjanAgent::Allocate(int state_id, double weight) const {
        //TODO: Implement AjanAgent::Allocate function to call JNI
        AjanAgentState* state = memory_pool_.Allocate();
        state->state_id = state_id;
        state->weight = weight;
        return state;
    }

    State *AjanAgent::Copy(const State *particle) const {
        //TODO: Implement AjanAgent::Copy function to call JNI
        AjanAgentState* state = memory_pool_.Allocate();
        *state = *dynamic_cast<const AjanAgentState*>(particle);
        state->SetAllocated();
        return state;
    }

    void AjanAgent::Free(State *particle) const {
        //TODO: Implement AjanAgent::Free function to call JNI
        memory_pool_.Free(static_cast<AjanAgentState*>(particle));
    }

    int AjanAgent::NumActiveParticles() const {
        //TODO: Implement AjanAgent::NumActiveParticles function to call JNI
        return memory_pool_.num_allocated();
    }
    //endregion

    //region problem helpers
    void AjanAgent::ComputeDefaultActions(string type) const {
        AjanHelper::getEnv()->CallVoidMethod(helper->getAjanJavaAgentObject(),
                                             AjanHelper::getMethodID(AJAN_AGENT,ComputeDefaultActions_),type.c_str());
    }

    string AjanAgent::WhichDefaultPolicyToUse() const {
        jobject javaString = AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaAgentObject(),
                                               AjanHelper::getMethodID(AJAN_AGENT,WhichDefaultPolicyToUse_));
        return AjanHelper::fromJavaString(javaString);
    }
    //endregion
}