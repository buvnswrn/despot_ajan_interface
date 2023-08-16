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
static const string InitializeModel = "InitializeModel";
static const string InitializeWorld = "InitializeWorld";
static const string ChooseSolver = "ChooseSolver";
static const string GetWorldType = "getWorldType";

// Method signatures (replace the placeholders with actual types)
static const string InitializeModel_Sig = "()Z";
static const string InitializeWorld_Sig = "(" + getSig(STRING) + ")Z";
static const string ChooseSolver_Sig = "()" + getSig(STRING);
static const string GetWorldType_Sig = "()" + getSig(STRING);
//endregion
// region AjanAgent Methods
static const string Init_Agent = "<init>";

// MDP Functions
static const string NumStates = "NumStates";
static const string NumActions = "NumActions";
static const string TransitionProbability = "TransitionProbability";
static const string Reward = "Reward";

// Belief MDP
static const string CreateBeliefLowerBound = "CreateBeliefLowerBound";
static const string CreateBeliefUpperBound = "CreateBeliefUpperBound";
static const string Tau = "Tau";
static const string Observe = "Observe";
static const string StepReward = "StepReward";

// StateIndexer
static const string GetIndex = "GetIndex";
static const string GetState = "GetState";

// StatePolicy
static const string GetAction = "GetAction";

// MMAPInferencer
static const string GetMMAP = "GetMMAP";

// POMDP
static const string Step = "Step";
static const string ObsProb = "ObsProb";
static const string CreateStartState = "CreateStartState";
static const string InitialBelief = "InitialBelief";
static const string GetMaxReward = "GetMaxReward";
static const string GetBestAction = "GetBestAction";
static const string CreateParticleUpperBound = "CreateParticleUpperBound";
static const string CreateScenarioUpperBound = "CreateScenarioUpperBound";
static const string CreateParticleLowerBound = "CreateParticleLowerBound";
static const string CreateScenarioLowerBound = "CreateScenarioLowerBound";
static const string PrintState = "PrintState";
static const string PrintObs = "PrintObs";
static const string PrintAction = "PrintAction";
static const string PrintBelief = "PrintBelief";
static const string NumActiveParticles = "NumActiveParticles";

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
static const string Connect = "Connect";
static const string Initialize = "Initialize";
static const string GetCurrentState = "GetCurrentState";
static const string ExecuteAction = "ExecuteAction";
static const string GetCurrentObservation = "getCurrentObservation";
static const string SetCurrentObservation = "setCurrentObservation";

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
static const string Action = "Action";

// Method signature (replace the placeholders with actual types)
static const string Action_Sig = "(" + getSig(VECTOR) + getSig(HISTORY) + ")I";
//endregion

#endif //LASER_TAG_AJAN_JNI_METHOD_GLOBALS_H
