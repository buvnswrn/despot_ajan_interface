//
// Created by bhuvanesh on 16.08.23.
//

#ifndef LASER_TAG_AJAN_JNI_METHOD_GLOBALS_H
#define LASER_TAG_AJAN_JNI_METHOD_GLOBALS_H
#include <string>
#include "ajan_jni_globals.h"
using namespace std;

string getSig(const string &method) { return ("L"+ method +";"); }

//region Planner Methods
static const string InitializeModel_ = "InitializeModel_";
static const string InitializeWorld_ = "InitializeWorld_";
static const string ChooseSolver_ = "ChooseSolver_";
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
static const string NumStates_ = "NumStates_";
static const string NumActions_ = "NumActions_";
static const string TransitionProbability_ = "TransitionProbability_";
static const string Reward_ = "Reward_";

// Belief MDP
static const string CreateBeliefLowerBound_ = "CreateBeliefLowerBound_";
static const string CreateBeliefUpperBound_ = "CreateBeliefUpperBound_";
static const string Tau_ = "Tau_";
static const string Observe_ = "Observe_";
static const string StepReward_ = "StepReward_";

// StateIndexer
static const string GetIndex_ = "GetIndex_";
static const string GetState_ = "GetState_";

// StatePolicy
static const string GetAction_ = "GetAction_";

// MMAPInferencer
static const string GetMMAP_ = "GetMMAP_";

// POMDP
static const string Step_ = "Step_";
static const string ObsProb_ = "ObsProb_";
static const string CreateStartState_ = "CreateStartState_";
static const string InitialBelief_ = "InitialBelief_";
static const string GetMaxReward_ = "GetMaxReward_";
static const string GetBestAction_ = "GetBestAction_";
static const string CreateParticleUpperBound_ = "CreateParticleUpperBound_";
static const string CreateScenarioUpperBound_ = "CreateScenarioUpperBound_";
static const string CreateParticleLowerBound_ = "CreateParticleLowerBound_";
static const string CreateScenarioLowerBound_ = "CreateScenarioLowerBound_";
static const string PrintState_ = "PrintState_";
static const string PrintObs_ = "PrintObs_";
static const string PrintAction_ = "PrintAction_";
static const string PrintBelief_ = "PrintBelief_";
static const string NumActiveParticles_ = "NumActiveParticles_";

// Method signatures (replace placeholders with actual type signatures)
static const string Init_Agent_Sig = "(J)V";
static const string NumStates_Sig = "()I";
static const string NumActions_Sig = "()I";
static const string TransitionProbability_Sig = "(II)" + getSig(VECTOR);
static const string Reward_Sig = "(II)D";
static const string CreateBeliefLowerBound_Sig = "(" + getSig(STRING) + ")" + getSig(AJAN_BELIEF_POLICY);
static const string CreateBeliefUpperBound_Sig = "(" + getSig(STRING) + ")" + getSig(AJAN_UPPER_BOUND);
static const string Tau_Sig = "(" + getSig(AJAN_BELIEF) + "IJ)" + getSig(BELIEF);
static const string Observe_Sig = "()" + getSig(AJAN_AGENT);
static const string StepReward_Sig = "(" + getSig(BELIEF) + "I)D";
static const string GetIndex_Sig = "(" + getSig(STATE) + ")I";
static const string GetState_Sig = "(I)" + getSig(STATE);
static const string GetAction_Sig = "(" + getSig(STATE) + ")I";
static const string GetMMAP_Sig = "(" + getSig(VECTOR) + ")" + getSig(AJAN_AGENT_STATE);
static const string Step_Sig = "(" + getSig(AJAN_AGENT_STATE) + "DIDJ)Z";
static const string ObsProb_Sig = "(J" + getSig(AJAN_AGENT_STATE) + "I)D";
static const string CreateStartState_Sig = "(" + getSig(STRING) + ")" + getSig(AJAN_AGENT_STATE);
static const string InitialBelief_Sig = "(" + getSig(STATE) + getSig(STRING) + ")" + getSig(BELIEF);
static const string GetMaxReward_Sig = "()D";
static const string GetBestAction_Sig = "()" + getSig(VALUED_ACTION);
static const string CreateParticleUpperBound_Sig = "(" + getSig(STRING) + ")" + getSig(AJAN_PARTICLE_UPPER_BOUND);
static const string CreateScenarioUpperBound_Sig = "(" + getSig(STRING) + getSig(STRING) + ")" + getSig(STRING);
static const string CreateParticleLowerBound_Sig = "(" + getSig(STRING) + ")" + getSig(STRING);
static const string CreateScenarioLowerBound_Sig = "(" + getSig(STRING) + getSig(STRING) + ")" + getSig(AJAN_POLICY);
static const string PrintState_Sig = "(" + getSig(STATE) + ")V";
static const string PrintObs_Sig = "(" + getSig(STATE) + "J)V";
static const string PrintAction_Sig = "(I)V";
static const string PrintBelief_Sig = "(" + getSig(BELIEF) + ")V";
static const string NumActiveParticles_Sig = "()I";
//endregion

//region State Methods
static const string Init_State = "<init>";
static const string Text_State = "text";

// Method signatures (replace the placeholders with actual types)
static const string Init_State_Sig = "(IIJ)V";
static const string Text_State_Sig = "(ID)" + getSig(STRING);
//endregion

//region World Methods
static const string Connect_ = "Connect";
static const string Initialize_ = "Initialize_";
static const string GetCurrentState_ = "GetCurrentState_";
static const string ExecuteAction_ = "ExecuteAction_";
static const string GetCurrentObservation_ = "getCurrentObservation";
static const string SetCurrentObservation_ = "setCurrentObservation";

// Method signatures (replace the placeholders with actual types)
static const string Connect_Sig = "()Z";
static const string Initialize_Sig = "()" + getSig(STATE);
static const string GetCurrentState_Sig = "()" + getSig(STATE);
static const string ExecuteAction_Sig = "(II)Z";
static const string GetCurrentObservation_Sig = "()J";
static const string SetCurrentObservation_Sig = "(J)Z";
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

//region Double Methods
static const string DoubleValue = "doubleValue";
static const string IntValue = "intValue";
static const string Value = "Value";

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

#endif //LASER_TAG_AJAN_JNI_METHOD_GLOBALS_H
