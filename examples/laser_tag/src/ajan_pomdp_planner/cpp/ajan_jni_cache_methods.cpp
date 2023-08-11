//
// Created by bhuvanesh on 01.08.23.
//

#include <iostream>
#include "ajan_helper.h"
#include "ajan_jni_globals.h"

// Need function to pass State variable to Java
// Need function to pass the particles and make some computations using JNI.
// Need to store all methodIDs (static)
// Need to store Individual Objects (non-static)

using namespace std;

string AjanHelper::getSig(const string &method) { return ("L"+ method +";"); }

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
    setStateClass( getEnv()->FindClass(getSig(AJAN_AGENT_STATE).c_str()));
    setCoordClass( getEnv()->FindClass(getSig(COORD).c_str()));
    setFloorClass( getEnv()->FindClass(getSig(FLOOR).c_str()));
    setPolicyClass( getEnv()->FindClass(getSig(AJAN_POLICY).c_str()));
    setParticleUpperBoundClass( getEnv()->FindClass(getSig(AJAN_PARTICLE_UPPER_BOUND).c_str()));
    setHistoryClass(getEnv()->FindClass(getSig(HISTORY).c_str()));
    cout << "Initializing the Java methods" << endl;
    GetAllMethodID();
}

void AjanHelper::GetAllMethodID() {
    GetAllPlannerMethodID();
    GetAllAgentMethodID();
    GetAllStateMethodID();
    GetAllWorldMethodID();
    GetAllVectorMethodID();
    GetAllParticleUpperBoundMethodID();
    GetAllAjanPolicyMethodID();
}

/**
 * Corresponding Java Class: AjanPlanner.java
 */
void AjanHelper::GetAllPlannerMethodID() {

    cout << "Initializing of Planner methods" << std::endl;
    const int totalMethod = 5;
    string methodNames[totalMethod][2] = {
            {"InitializeModel", "()Z"},
            {"InitializeWorld", "(" + getSig(STRING) + ")Z",},
            {"ChooseSolver",    "()" + getSig(STRING)},
            {"getWorldType",    "()" + getSig(STRING)}
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
            //region  MDP Functions
            {"NumStates",                 "()I"},
            {"NumActions",                "()I"},
            {"TransitionProbability",     "(II)" + getSig(VECTOR)},
            {"Reward",                    "(II)D"},
            //endregion
            //region Belief MDP
            {"CreateBeliefLowerBound",  "(" + getSig(STRING) + ")" + getSig(AJAN_BELIEF_POLICY)}, // WARN: Need to check whether BeliefLowerBound class can be created. Can throw error here.
            {"CreateBeliefUpperBound",  "(" + getSig(STRING) + ")" + getSig(AJAN_UPPER_BOUND)},
            {"Tau", "(" + getSig(AJAN_BELIEF)+ "IJ)" + getSig(BELIEF)}, // WARN:This may not work
            //            {"getTauParticles",           "(" + getSig(VECTOR) + "II)" + getSig(VECTOR)}, // Not available till now but can be created
            {"Observe",             "()" + getSig(AJAN_AGENT)}, // see what is it for map
            {"StepReward","("+ getSig(BELIEF)+"I)"+"D"},
//            {"StepRewardFromParticles",             "("+ getSig(VECTOR)+"I)D"},
//            {"StepRewardFromParticles",   "(" + getSig(VECTOR) + "I)D"},
            //endregion
            //region StateIndexer
            {"GetIndex",                  "("+ getSig(STATE)+")I"}, // WARN: State is an abstract class, see whether AjanAgentState can be used instead
            {"GetState",                  "(I)"+ getSig(STATE)},
            //endregion
            //region StatePolicy
            {"GetAction",                 "(" + getSig(STATE) + ")I"},
            //endregion
            //region MMAPInferencer
            {"GetMMAP",                   "(" + getSig(VECTOR) + ")" + getSig(AJAN_AGENT_STATE)},
            //endregion
            //region POMDP
            {"Step",                      "(" + getSig(AJAN_AGENT_STATE) + "DIDJ)Z"},
//            {"Step",                      "(" + getSig(AJAN_AGENT_STATE) + "DID)Z"}, // not possible to call by same name according to this method
//            {"Step",                      "(" + getSig(AJAN_AGENT_STATE) + "IDJ)Z"}, // not possible to call by same name according to this method
//                {"Reward","("+ getSig(STATE)+"I)D"}, // cached in region MDP with other params. not possible to call by same name according to this method. Call directly
            {"ObsProb",                   "(J" + getSig(AJAN_AGENT_STATE) + "I)D"},
            {"CreateStartState",          "(" + getSig(STRING) + ")" + getSig(AJAN_AGENT_STATE)}, // WARN: Return type is State
            {"InitialBelief","("+ getSig(STATE)+ getSig(STRING)+")"+ getSig(BELIEF)},// WARN: Belief and State are abstract classes - Might not be possible to create objects
//            {"getInitialBeliefParticles", "(" + getSig(STATE) + getSig(STRING) + ")" + getSig(VECTOR)},
            {"GetMaxReward",              "()D"},
            {"GetBestAction",             "()" + getSig(VALUED_ACTION)},
            {"CreateParticleUpperBound",  "("+ getSig(STRING)+")"+ getSig(AJAN_PARTICLE_UPPER_BOUND)},// WARN: Return type is Particle Upperbound which is abstract
            {"CreateScenarioUpperBound",  "("+ getSig(STRING)+ getSig(STRING)+")"+ getSig(STRING)}, // WARN: This does not exist as of now
            {"CreateParticleLowerBound",  "("+ getSig(STRING)+")"+ getSig(STRING)}, // WARN: This does not exist as of now
            {"CreateScenarioLowerBound",  "(" + getSig(STRING) + getSig(STRING) + ")" + getSig(AJAN_POLICY)}, // WARN: Return type is ScenarioLowerBound
            {"PrintState",                "(" + getSig(STATE) + ")V"},
            {"PrintObs",                  "(" + getSig(STATE) + "J)V"},
            {"PrintAction",               "(I)V"},
            {"PrintBelief",               "(" + getSig(BELIEF) + ")V"},
//            {"Observe","("+ getSig()+"II)"+ getSig()},
            {"NumActiveParticles","()I"},
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
//            {"<init>","()V"},
            {"<init>","(IIJ)V"},
            {"text", "(ID)" + getSig(STRING)}
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
            {"Connect",               "()Z"},
            {"Initialize",            "()" + getSig(STATE)},
            {"GetCurrentState",       "()" + getSig(STATE)},
            {"ExecuteAction",         "(II)Z",},
            {"getCurrentObservation", "()J"},
            {"setCurrentObservation", "(J)Z"}
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
            {"size",   "()I",},
            {"<init>", "()V",},
            {"get",    "(I)" + getSig(OBJECT)},
            {"add",    "(" + getSig(OBJECT) + ")Z"}
    };
    for (auto &methodName: methodNames) {
        vectorMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getVectorClass(),
                                                                                methodName[0].c_str(),
                                                                                methodName[1].c_str()));
    }
    cout << "Initialization of Vector methods Complete" << std::endl;
}

/**
 * Corresponding Java Class: AjanParticleUpperBound.java
 */
void AjanHelper::GetAllParticleUpperBoundMethodID() {
    cout << "Initializing the ParticleUpperBound methods" << std::endl;
    const int totalMethod = 1;
    string methodNames[totalMethod][2] = {
//            {"Value", "(I)D"},
            {"Value", "("+ getSig(STATE)+")D"}
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
            {"Action", "(" + getSig(VECTOR) + getSig(HISTORY)+")I"}
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
    cout << "Initializing the AJAN Policy methods" << std::endl;
    const int totalMethod = 2;
    string methodNames1[totalMethod][2] = {
            {"<init>", "(II)V"}
    };

    for (auto &methodName: methodNames1) {
        coordMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getCoordClass(),
                                                                                 methodName[0].c_str(),
                                                                                 methodName[1].c_str()));
    }
    cout << "Initialization of Coord methods Complete" << std::endl;
}

jmethodID AjanHelper::getMethodID(const string& clazz, const string& methodName) {
//    cout<<"Calling "<<methodName<<" for "<<clazz<<endl;
    if (clazz == "Agent") {
        return agentMethods[methodName];
    } else if (clazz == "Planner") {
        return plannerMethods[methodName];
    } else if (clazz == "World") {
        return worldMethods[methodName];
    } else if (clazz == "Vector") {
        return vectorMethods[methodName];
    } else if (clazz == "ParticleUpperBound") {
        return particleUpperBoundMethods[methodName];
    } else if (clazz == "Policy") {
        return ajanPolicyMethods[methodName];
    } else if (clazz == "State") {
        return stateMethods[methodName];
    } else if (clazz == "Coord") {
        return coordMethods[methodName];
    } else {
        cout << "Cannot find the method" << endl;
        return nullptr;
    }
}


