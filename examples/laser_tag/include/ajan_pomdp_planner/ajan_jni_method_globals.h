//
// Created by bhuvanesh on 16.08.23.
//

#ifndef LASER_TAG_AJAN_JNI_METHOD_GLOBALS_H
#define LASER_TAG_AJAN_JNI_METHOD_GLOBALS_H
#include <string>
#include "ajan_jni_globals.h"
using namespace std;

static string getSig(const string &method) { return ("L"+ method +";"); }

//region Planner Methods
static const string InitializeModel_ = "InitializeModel";
static const string InitializeWorld_ = "InitializeWorld";
static const string ChooseSolver_ = "ChooseSolver";
static const string GetWorldType_ = "getWorldType";

// Method signatures (replace the placeholders with actual types)
static const string InitializeModel_Sig = "()Z";
static const string InitializeWorld_Sig = "(" + getSig(STRING) + ")Z";
static const string ChooseSolver_Sig = "()" + getSig(STRING);
static const string GetWorldType_Sig = "()" + getSig(STRING);
//endregion
// region AjanAgent Methods
static const string Init_Agent = "<init>";

// MDP Functions
static const string NumStates_ = "NumStates";
static const string NumActions_ = "NumActions";
static const string TransitionProbability_ = "TransitionProbability";
static const string Reward_ = "Reward";

// Belief MDP
static const string CreateBeliefLowerBound_ = "CreateBeliefLowerBound";
static const string CreateBeliefUpperBound_ = "CreateBeliefUpperBound";
static const string Tau_ = "Tau";
static const string Observe_ = "Observe";
static const string StepReward_ = "StepReward";

// StateIndexer
static const string GetIndex_ = "GetIndex";
static const string GetState_ = "GetState";

// StatePolicy
static const string GetAction_ = "GetAction";

// MMAPInferencer
static const string GetMMAP_ = "GetMMAP";

// POMDP
static const string Step_ = "Step";
static const string ObsProb_ = "ObsProb";
static const string CreateStartState_ = "CreateStartState";
static const string InitialBelief_ = "InitialBelief";
static const string GetMaxReward_ = "GetMaxReward";
static const string GetBestAction_ = "GetBestAction";
static const string CreateParticleUpperBound_ = "CreateParticleUpperBound";
static const string CreateScenarioUpperBound_ = "CreateScenarioUpperBound";
static const string CreateParticleLowerBound_ = "CreateParticleLowerBound";
static const string CreateScenarioLowerBound_ = "CreateScenarioLowerBound";
static const string PrintState_ = "PrintState";
static const string PrintObs_ = "PrintObs";
static const string PrintAction_ = "PrintAction";
static const string PrintBelief_ = "PrintBelief";
static const string NumActiveParticles_ = "NumActiveParticles";
static const string ComputeDefaultActions_ = "ComputeDefaultActions";
static const string WhichDefaultPolicyToUse_ = "WhichDefaultPolicyToUse";
static const string GetCurrentState_Agent = "getCurrentState";
static const string GetCurrentReward_Agent = "getCurrentReward";
static const string GetCurrentAction_Agent = "getCurrentAction";
static const string GetCurrentObservation_Agent = "getCurrentObservation";

// Method signatures (replace placeholders with actual type signatures)
static const string Init_Agent_Sig = "(J)V";
static const string NumStates_Sig = "()I";
static const string NumActions_Sig = "()I";
static const string TransitionProbability_Sig = "(II)" + getSig(VECTOR);
static const string Reward_Sig = "(II)D";
static const string CreateBeliefLowerBound_Sig = "(" + getSig(STRING) + "J)" + getSig(AJAN_BELIEF_POLICY);
static const string CreateBeliefUpperBound_Sig = "(" + getSig(STRING) + "J)" + getSig(AJAN_UPPER_BOUND);
static const string Tau_Sig = "(" + getSig(AJAN_BELIEF) + "IJ)" + getSig(AJAN_BELIEF);
static const string Observe_Sig = "("+ getSig(AJAN_BELIEF)+"I"+ getSig(HASHMAP)+")V";
static const string StepReward_Sig = "(" + getSig(BELIEF) + "I)D";
static const string GetIndex_Sig = "(" + getSig(STATE) + ")I";
static const string GetState_Sig = "(I)" + getSig(STATE);
static const string GetAction_Sig = "(" + getSig(STATE) + ")I";
static const string GetMMAP_Sig = "(" + getSig(VECTOR) + ")" + getSig(AJAN_AGENT_STATE);
static const string Step_Sig = "(" + getSig(STATE) + "DIDJ)Z";
static const string ObsProb_Sig = "(J" + getSig(AJAN_AGENT_STATE) + "I)D";
static const string CreateStartState_Sig = "(" + getSig(STRING) + ")" + getSig(AJAN_AGENT_STATE);
static const string InitialBelief_Sig = "(" + getSig(STATE) + getSig(STRING) + ")" + getSig(BELIEF);
static const string GetMaxReward_Sig = "()D";
static const string GetBestAction_Sig = "()" + getSig(VALUED_ACTION);
static const string CreateParticleUpperBound_Sig = "(" + getSig(STRING) + "J)" + getSig(AJAN_PARTICLE_UPPER_BOUND);
static const string CreateScenarioUpperBound_Sig = "(" + getSig(STRING) + getSig(STRING) + ")" + getSig(AJAN_UPPER_BOUND);
static const string CreateParticleLowerBound_Sig = "(" + getSig(STRING) + ")" + getSig(AJAN_PARTICLE_LOWER_BOUND);
static const string CreateScenarioLowerBound_Sig = "(" + getSig(STRING) + getSig(STRING) + "J)" + getSig(AJAN_POLICY);
static const string PrintState_Sig = "(" + getSig(STATE) + ")V";
static const string PrintObs_Sig = "(" + getSig(STATE) + "J)V";
static const string PrintAction_Sig = "(I)V";
static const string PrintBelief_Sig = "(" + getSig(AJAN_BELIEF) + ")V";
static const string NumActiveParticles_Sig = "()I";
static const string ComputeDefaultActions_Sig = "("+ getSig(STRING)+")V";
static const string WhichDefaultPolicyToUse_Sig = "()"+ getSig(STRING);
static const string GetCurrentState_Sig_Agent = "()"+ getSig(AGENT_STATE);
static const string GetCurrentReward_Sig_Agent = "()D";
static const string GetCurrentAction_Sig_Agent = "()I";
static const string GetCurrentObservation_Sig_Agent = "()J";
//endregion

//region State Methods
static const string Init_State = "<init>";
static const string Text_State = "text";

// Method signatures (replace the placeholders with actual types)
static const string Init_State_Sig = "(IID)V";
static const string Text_State_Sig = "(ID)" + getSig(STRING);
//endregion

//region World Methods
static const string Connect_ = "Connect";
static const string Initialize_ = "Initialize";
static const string GetCurrentState_World = "GetCurrentState";
static const string ExecuteAction_ = "ExecuteAction";
static const string GetCurrentObservation_World = "getCurrentObservation";
static const string SetCurrentObservation_World = "setCurrentObservation";

// Method signatures (replace the placeholders with actual types)
static const string Connect_Sig = "()Z";
static const string Initialize_Sig = "()" + getSig(STATE);
static const string GetCurrentState_Sig_World = "()" + getSig(STATE);
static const string ExecuteAction_Sig = "(IJ)Z";
static const string GetCurrentObservation_Sig_World = "()J";
static const string SetCurrentObservation_Sig_World = "(J)Z";

//endregion

//region Vector Methods
static const string Size = "size";
static const string Init_ = "<init>";
static const string Get = "get";
static const string Add = "add";

// Method signatures (replace the placeholders with actual types)
static const string Size_Sig = "()I";
static const string Init_Void_Sig = "()V";
static const string Init_Long_Void_Sig = "(J)V";
static const string Init_Int_Int_Void_Sig = "(II)V";
static const string Init_Int_Long_Void_Sig = "(IJ)V";
static const string Get_Sig = "(I)" + getSig(OBJECT);
static const string Add_Sig = "(" + getSig(OBJECT) + ")Z";
//endregion

//region HashMap Methods
static const string Put = "put";

//Method Signatures (replace the placeholders with actual types)
static const string Put_Sig = "("+getSig(OBJECT)+ getSig(OBJECT)+")"+ getSig(OBJECT);
static const string Get_Sig_HashMap = "("+getSig(OBJECT)+")"+ getSig(OBJECT);

//endregion

//region Double Methods
static const string DoubleValue = "doubleValue";
[[maybe_unused]] static const string LongValue = "longValue";
static const string IntValue = "intValue";
static const string Value_ = "Value";

// Method signatures (replace the placeholders with actual types)
static const string DoubleValue_Sig = "()D";
static const string IntValue_Sig = "()I";
static const string Value_State_Double_Sig = "("+ getSig(STATE)+")D";
//endregion

//region AjanPolicy Methods
static const string Action_ = "Action";

// Method signature (replace the placeholders with actual types)
static const string Action_Sig = "(" + getSig(VECTOR) + getSig(HISTORY) + ")I";
//endregion
// region AjanUpperBound Methods
static const string Value_Belief = "Value";
static const string Value_Particles_History = "Value";

// Method signature (replace the placeholders with actual types)
static const string Value_Belief_Sig = "("+ getSig(BELIEF)+")D";
static const string Value_Particles_History_Sig = "("+ getSig(VECTOR)+ getSig(HISTORY)+")D";
//endregion

//region AjanBelief methods
static const string Particles_ = "particles"; // a method of ParticleBelief
static const string Update_ = "Update";
static const string Belief_Init_II = "<init>";
// Method signature (replace the placeholders with actual types)
static const string Particles_Sig = "()"+ getSig(VECTOR);
static const string Update_Sig = "(IJ)V";
static const string Belief_Init_II_Sig = "(J"+ getSig(AJAN_AGENT)+ getSig(HISTORY)+ getSig(VECTOR)+")V";
//endregion

//region AjanBeleifPolicy methods
// Method signature (replace the placeholders with actual types)
static const string BeliefPolicy_Init_Sig = "(" + getSig(AJAN_AGENT)+"J)V";
//endregion
static const string SetReferenceToCpp_ = "SetReferenceToCpp_";
static const string SetReferenceToCpp_Sig = "(J)V";
#endif //LASER_TAG_AJAN_JNI_METHOD_GLOBALS_H
