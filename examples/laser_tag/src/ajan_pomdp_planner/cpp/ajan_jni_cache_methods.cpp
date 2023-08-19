//
// Created by bhuvanesh on 01.08.23.
//

#include <iostream>
#include "ajan_helper.h"
#include "ajan_jni_globals.h"
#include "ajan_jni_method_globals.h"

// Need function to pass State variable to Java
// Need function to pass the particles and make some computations using JNI.
// Need to store all methodIDs (static)
// Need to store Individual Objects (non-static)

using namespace std;



void AjanHelper::Init(JNIEnv *&env, jobject *plannerObject, jobject *agentObject, jobject *worldObject) {

    cout << "Initializing the Java References" << std::endl;
    setEnv(env);
    setAjanJavaPlannerObject(plannerObject);
    setAjanJavaAgentObject(agentObject);
    setAjanJavaWorldObject(worldObject);

    cout << "Initializing the Java classes" << std::endl;
    setPlannerClass(getEnv()->GetObjectClass(*plannerObject));
    setAgentClass(getEnv()->GetObjectClass(*agentObject));
    setWorldClass(getEnv()->GetObjectClass(*worldObject));

    getJavaClassReferences();
}

void  AjanHelper::getJavaClassReferences() {
    setVectorClass(getEnv()->FindClass(getSig(VECTOR).c_str()));
    setDoubleClass(getEnv()->FindClass(getSig(DOUBLE).c_str()));
    setIntegerClass(getEnv()->FindClass(getSig(INTEGER).c_str()));
    setLongClass(getEnv()->FindClass(getSig(LONG).c_str()));
    setStateClass( getEnv()->FindClass(getSig(AJAN_AGENT_STATE).c_str()));
    setCoordClass( getEnv()->FindClass(getSig(COORD).c_str()));
    setFloorClass( getEnv()->FindClass(getSig(FLOOR).c_str()));
    setPolicyClass( getEnv()->FindClass(getSig(AJAN_POLICY).c_str()));
    setParticleUpperBoundClass( getEnv()->FindClass(getSig(AJAN_PARTICLE_UPPER_BOUND).c_str()));
    setHistoryClass(getEnv()->FindClass(getSig(HISTORY).c_str()));
    setValuedActionClass(getEnv()->FindClass(getSig(VALUED_ACTION).c_str()));
    setAjanBeliefClass(getEnv()->FindClass(getSig(AJAN_BELIEF).c_str()));
    cout << "Initializing the Java methods" << endl;
    GetAllMethodID();
}

void AjanHelper::GetAllMethodID() {
    GetAllPlannerMethodID();
    GetAllAgentMethodID();
    GetAllStateMethodID();
    GetAllWorldMethodID();
    GetAllVectorMethodID();
    GetAllDoubleMethodID();
    GetAllIntegerMethodID();
    GetAllParticleUpperBoundMethodID();
    GetAllAjanPolicyMethodID();
    GetAllCoordMethodID();
    GetAllHistoryMethodID();
    GetAllValuedActionMethodID();
    GetAllAjanBeliefMethodID();
}

/**
 * Corresponding Java Class: AjanPlanner.java
 */
void AjanHelper::GetAllPlannerMethodID() {

    cout << "Initializing of Planner methods" << std::endl;
    const int totalMethod = 5;
    string methodNames[totalMethod][2] = {
            {InitializeModel_, InitializeModel_Sig},
            {InitializeWorld_, InitializeWorld_Sig},
            {ChooseSolver_,    ChooseSolver_Sig},
            {GetWorldType_, GetWorldType_Sig}
    };
    for (auto &methodName: methodNames) {
        plannerMethods[methodName[0]] = (methodName[0], ajanJavaEnv->GetMethodID(getPlannerClass(),
                                                                                 methodName[0].c_str(),
                                                                                 methodName[1].c_str()));
    }
    cout << "Initialization of Planner methods Complete" << std::endl;

}

/**
 * Corresponding Java Class: AjanAgent.java
 */
void AjanHelper::GetAllAgentMethodID() {
    cout << "Initializing of Agent methods" << std::endl;
    const int totalMethod = 30;
    string methodNames[totalMethod][2] = {
            {Init_Agent,              Init_Agent_Sig},

            // MDP Functions
            {NumStates_,              NumStates_Sig},
            {NumActions_,             NumActions_Sig},
            {TransitionProbability_,  TransitionProbability_Sig},
            {Reward_,                 Reward_Sig},

            // Belief MDP
            {CreateBeliefLowerBound_, CreateBeliefLowerBound_Sig},
            {CreateBeliefUpperBound_, CreateBeliefUpperBound_Sig},
            {Tau_,                    Tau_Sig}, // WARN:This may not work
            //            {"getTauParticles",           "(" + getSig(VECTOR) + "II)" + getSig(VECTOR)}, // Not available till now but can be created
            {Observe_,    Observe_Sig}, // see what is it for map
            {StepReward_, StepReward_Sig},
//            {"StepRewardFromParticles",             "("+ getSig(VECTOR)+"I)D"},
//            {"StepRewardFromParticles",   "(" + getSig(VECTOR) + "I)D"},
            //endregion
            //region StateIndexer
            {GetIndex_,                GetIndex_Sig}, // WARN: State is an abstract class, see whether AjanAgentState can be used instead
            {GetState_,                GetState_Sig},
            //endregion
            //region StatePolicy
            {GetAction_,               GetAction_Sig},
            //endregion
            //region MMAPInferencer
            {GetMMAP_,                 GetMMAP_Sig},
            //endregion
            //region POMDP
            {Step_,                     Step_Sig},
//            {"Step_",                      "(" + getSig(AJAN_AGENT_STATE) + "DID)Z"}, // not possible to call by same name according to this method
//            {"Step_",                      "(" + getSig(AJAN_AGENT_STATE) + "IDJ)Z"}, // not possible to call by same name according to this method
//                {"Reward_","("+ getSig(STATE)+"I)D"}, // cached in region MDP with other params. not possible to call by same name according to this method. Call directly
            {ObsProb_,                  ObsProb_Sig},
            {CreateStartState_,         CreateStartState_Sig}, // WARN: Return type is State
            {InitialBelief_,            InitialBelief_Sig},// WARN: Belief and State are abstract classes - Might not be possible to create objects
//            {"getInitialBeliefParticles", "(" + getSig(STATE) + getSig(STRING) + ")" + getSig(VECTOR)},
            {GetMaxReward_,             GetMaxReward_Sig},
            {GetBestAction_,            GetBestAction_Sig},
            {CreateParticleUpperBound_, CreateParticleUpperBound_Sig},// WARN: Return type is Particle Upperbound which is abstract
            {CreateScenarioUpperBound_, CreateScenarioUpperBound_Sig}, // WARN: This does not exist as of now
            {CreateParticleLowerBound_, CreateParticleLowerBound_Sig}, // WARN: This does not exist as of now
            {CreateScenarioLowerBound_, CreateScenarioLowerBound_Sig}, // WARN: Return type is ScenarioLowerBound
            {PrintState_,               PrintState_Sig},
            {PrintObs_,                 PrintObs_Sig},
            {PrintAction_,              PrintAction_Sig},
            {PrintBelief_,              PrintBelief_Sig},
//            {"Observe_","("+ getSig()+"II)"+ getSig()},
            {NumActiveParticles_, NumActiveParticles_Sig}
//            {"PrintMethod",               "()V"},
            //endregion
    };

    for (auto &methodName: methodNames) {
        agentMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getAgentClass(),
                                                                               methodName[0].c_str(),
                                                                               methodName[1].c_str()));
    }
    cout << "Initialization of Agent methods Complete" << std::endl;

}

/**
 * Corresponding Java Class: AjanAgentState.java
 */
void AjanHelper::GetAllStateMethodID() {
    cout << "Initializing the State methods" << std::endl;
    const int totalMethod = 2;
    string methodNames[totalMethod][2] = {
//            {Init_,"()V"},
            {Init_State,Init_State_Sig},
            {Text_State, Text_State_Sig}
    };
    for (auto &methodName: methodNames) {
        stateMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getStateClass(),
                                                                               methodName[0].c_str(),
                                                                               methodName[1].c_str()));
    }
    cout << "Initialization of State methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: AjanWorld.java
 */
void AjanHelper::GetAllWorldMethodID() {
    cout << "Initializing the World methods" << std::endl;
    const int totalMethod = 6;
    string methodNames[totalMethod][2] = {
            {Connect_,                Connect_Sig},
            {Initialize_,            Initialize_Sig},
            {GetCurrentState_,       GetCurrentState_Sig},
            {ExecuteAction_,         ExecuteAction_Sig},
            {GetCurrentObservation_, GetCurrentObservation_Sig},
            {SetCurrentObservation_, SetCurrentObservation_Sig}
    };

    for (auto &methodName: methodNames) {
        worldMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getWorldClass(),
                                                                               methodName[0].c_str(),
                                                                               methodName[1].c_str()));
    }
    cout << "Initialization of World methods Complete" << std::endl;
}

void AjanHelper::GetAllVectorMethodID() {
    cout << "Initializing the Vector methods" << std::endl;

    const int totalMethod = 4;
    string methodNames[totalMethod][2] = {
            {Size,  Size_Sig},
            {Init_, Init_Void_Sig,},
            {Get,   Get_Sig},
            {Add,   Add_Sig}
    };
    for (auto &methodName: methodNames) {
        vectorMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getVectorClass(),
                                                                                methodName[0].c_str(),
                                                                                methodName[1].c_str()));
    }
    cout << "Initialization of Vector methods Complete" << std::endl;
}

void AjanHelper::GetAllDoubleMethodID() {
    cout << "Initializing the Double methods" << std::endl;

    const int totalMethod = 4;
    string methodNames[totalMethod][2] = {
            {Init_, Init_Void_Sig},
            {DoubleValue,DoubleValue_Sig},
            {IntValue,IntValue_Sig} // any methods available. Ref: https://docs.oracle.com/javase/8/docs/api/java/lang/Double.html
    };
    for (auto &methodName: methodNames) {
        doubleMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getDoubleClass(),
                                                                             methodName[0].c_str(),
                                                                             methodName[1].c_str()));
    }
    cout << "Initialization of Double methods Complete" << std::endl;
}

void AjanHelper::GetAllIntegerMethodID() {
    cout << "Initializing the Integer methods" << std::endl;

    const int totalMethod = 4;
    string methodNames[totalMethod][2] = {
            {Init_, Init_Void_Sig},
            {DoubleValue,DoubleValue_Sig},
            {IntValue,IntValue_Sig} // any methods available. Ref:
    };
    for (auto &methodName: methodNames) {
        doubleMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getIntegerClass(),
                                                                             methodName[0].c_str(),
                                                                             methodName[1].c_str()));
    }
    cout << "Initialization of Integer methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: AjanParticleUpperBound.java
 */
void AjanHelper::GetAllParticleUpperBoundMethodID() {
    cout << "Initializing the ParticleUpperBound methods" << std::endl;
    const int totalMethod = 2;
    string methodNames[totalMethod][2] = {
//            {"Value", "(I)D"},
            {Init_,Init_Long_Void_Sig},
            {Value, Value_State_Double_Sig}
    };
    for (auto &methodName: methodNames) {
        particleUpperBoundMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getParticleUpperBoundClass(),
                                                                                            methodName[0].c_str(),
                                                                                            methodName[1].c_str()));
    }
    cout << "Initialization of ParticleUpperBound methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: AjanPolicy.java -> DefaultPolicy -> ScenarioLowerBound
 */
void AjanHelper::GetAllAjanPolicyMethodID() {
    cout << "Initializing the AJAN Policy methods" << std::endl;
    const int totalMethod = 2;
    string methodNames1[totalMethod][2] = {
//            {"Action", "(" + getSig(VECTOR) + "J)I",},
            {Action_, Action_Sig}
//            {"TestMethod", "()I"}
    };

    for (auto &methodName: methodNames1) {
        ajanPolicyMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getPolicyClass(),
                                                                                    methodName[0].c_str(),
                                                                                    methodName[1].c_str()));
    }
    cout << "Initialization of AJAN Policy methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: Coord.java
 */
void AjanHelper::GetAllCoordMethodID() {
    cout << "Initializing the AJAN Coord methods" << std::endl;
    const int totalMethod = 2;
    string methodNames1[totalMethod][2] = {
            {Init_, Init_Int_Int_Void_Sig}
    };

    for (auto &methodName: methodNames1) {
        coordMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getCoordClass(),
                                                                                 methodName[0].c_str(),
                                                                                 methodName[1].c_str()));
    }
    cout << "Initialization of Coord methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: History.java
 */
void AjanHelper::GetAllHistoryMethodID() {
    cout << "Initializing the AJAN History methods" << std::endl;
    const int totalMethod = 2;
    string methodNames1[totalMethod][2] = {
            {Init_, Init_Long_Void_Sig}
    };

    for (auto &methodName: methodNames1) {
        historyMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getHistoryClass(),
                                                                            methodName[0].c_str(),
                                                                            methodName[1].c_str()));
    }
    cout << "Initialization of History methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: ValuedAction.java
 */
void AjanHelper::GetAllValuedActionMethodID() {
    cout << "Initializing the AJAN ValuedAction methods" << std::endl;
    const int totalMethod = 2;
    string methodNames1[totalMethod][2] = {
            {Init_, Init_Int_Long_Void_Sig}
    };

    for (auto &methodName: methodNames1) {
        valuedActionMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getHistoryClass(),
                                                                              methodName[0].c_str(),
                                                                              methodName[1].c_str()));
    }
    cout << "Initialization of ValuedAction methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: AjanBelief.java
 */
void AjanHelper::GetAllAjanBeliefMethodID() {
    cout << "Initializing the AjanBelief methods" << std::endl;
    const int totalMethod = 2;
    string methodNames1[totalMethod][2] = {
            {Init_, Init_Long_Void_Sig}
    };

    for (auto &methodName: methodNames1) {
        ajanBeliefMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getHistoryClass(),
                                                                                   methodName[0].c_str(),
                                                                                   methodName[1].c_str()));
    }
    cout << "Initialization of AjanBelief methods Complete" << std::endl;
}

jmethodID AjanHelper::getMethodID(const string& clazz, const string& methodName) {
//    cout<<"Calling "<<methodName<<" for "<<clazz<<endl;
    if (clazz == AJAN_AGENT) {
        return agentMethods[methodName];
    } else if (clazz == AJAN_PLANNER) {
        return plannerMethods[methodName];
    } else if (clazz == AJAN_WORLD) {
        return worldMethods[methodName];
    } else if (clazz == VECTOR) {
        return vectorMethods[methodName];
    }  else if (clazz == DOUBLE) {
        return doubleMethods[methodName];
    }   else if (clazz == INTEGER) {
        return integerMethods[methodName];
    } else if (clazz == AJAN_PARTICLE_UPPER_BOUND) {
        return particleUpperBoundMethods[methodName];
    } else if (clazz == AJAN_POLICY) {
        return ajanPolicyMethods[methodName];
    } else if (clazz == AJAN_AGENT_STATE) {
        return stateMethods[methodName];
    } else if (clazz == COORD) {
        return coordMethods[methodName];
    } else if (clazz == HISTORY) {
        return historyMethods[methodName];
    } else if (clazz == VALUED_ACTION) {
        return valuedActionMethods[methodName];
    }else if (clazz == AJAN_BELIEF) {
        return ajanBeliefMethods[methodName];
    } else {
        cout << "Cannot find the method" << endl;
        return nullptr;
    }
}


