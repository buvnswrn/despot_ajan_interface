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

void AjanHelper::GetAllPlannerMethodID() {

    cout << "Initializing of Planner methods" << std::endl;
    const int totalMethod = 5;
    string methodNames[totalMethod][2] = {
            {"InitializeModel", "()Z"},
            {"InitializeWorld", "(" + getSig(STRING) + ")Z",},
            {"PrintMethod",     "()V"},
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

void AjanHelper::GetAllAgentMethodID() {
    cout << "Initializing of Agent methods" << std::endl;
    const int totalMethod = 30;
    string methodNames[totalMethod][2] = {
            {"Step",                      "(" + getSig(AJAN_AGENT_STATE) + "DIDI)Z"},
            {"NumActions",                "()I"},
            {"NumStates",                 "()I"},
            {"ObsProb",                   "(I" + getSig(AJAN_AGENT_STATE) + "I)D"},
            {"CreateStartState",          "(" + getSig(STRING) + ")" + getSig(AJAN_AGENT_STATE)},
            {"getInitialBeliefParticles", "(" + getSig(STATE) + getSig(STRING) + ")" + getSig(VECTOR)},
            {"GetMaxReward",              "()D"},
//                {"Reward","("+ getSig(STATE)+"I)D"},
            {"Reward",                    "(II)D"},
            {"GetBestAction",             "()" + getSig(VALUED_ACTION)},
            {"GetAction",                 "(" + getSig(STATE) + ")I"},
            {"CreateScenarioLowerBound",  "(" + getSig(STRING) + getSig(STRING) + ")" + getSig(AJAN_POLICY)},
            {"CreateScenarioUpperBound",  "("+ getSig(STRING)+ getSig(STRING)+")"+ getSig(STRING)},
            {"CreateParticleUpperBound",  "("+ getSig(STRING)+")"+ getSig(AJAN_PARTICLE_UPPER_BOUND)},
            {"CreateParticleLowerBound",  "("+ getSig(STRING)+")"+ getSig(STRING)},
            {"TransitionProbability",     "(II)" + getSig(VECTOR)},
            {"GetIndex",                  "("+ getSig(STATE)+")I"},
            {"GetState",                  "(I)"+ getSig(STATE)},
            {"PrintState",                "(" + getSig(STATE) + ")V"},
            {"PrintObs",                  "(" + getSig(STATE) + "I)V"},
            {"PrintAction",               "(I)V"},
            {"PrintBelief",               "(" + getSig(BELIEF) + ")V"},
            {"GetMMAP",                   "(" + getSig(VECTOR) + ")" + getSig(AJAN_AGENT_STATE)},
            {"getTauParticles",           "(" + getSig(VECTOR) + "II)" + getSig(VECTOR)},
            {"Observe",             "()" + getSig(AJAN_AGENT)}, // see what is it for map
            {"StepRewardFromParticles",             "("+ getSig(VECTOR)+"I)D"},
//            {"Observe","("+ getSig()+"II)"+ getSig()},
            {"StepRewardFromParticles",   "(" + getSig(VECTOR) + "I)D"},
            {"PrintMethod",               "()V"},

    };

    for (auto &methodName: methodNames) {
        agentMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getAgentClass(),
                                                                               methodName[0].c_str(),
                                                                               methodName[1].c_str()));
    }
    cout << "Initialization of Agent methods Complete" << std::endl;

}

void AjanHelper::GetAllStateMethodID() {
    cout << "Initializing the State methods" << std::endl;
    const int totalMethod = 2;
    string methodNames[totalMethod][2] = {
            {"<init>","()V"},
            {"text", "(ID)" + getSig(STRING)}
    };
    for (auto &methodName: methodNames) {
        stateMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getStateClass(),
                                                                               methodName[0].c_str(),
                                                                               methodName[1].c_str()));
    }
    cout << "Initialization of State methods Complete" << std::endl;
}

void AjanHelper::GetAllWorldMethodID() {
    cout << "Initializing the World methods" << std::endl;
    const int totalMethod = 6;
    string methodNames[totalMethod][2] = {
            {"Connect",               "()Z"},
            {"ExecuteAction",         "(II)Z",},
            {"getCurrentObservation", "()J"},
            {"setCurrentObservation", "(J)Z"},
            {"Initialize",            "()" + getSig(STATE)},
            {"GetCurrentState",       "()" + getSig(STATE)}
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

void AjanHelper::GetAllParticleUpperBoundMethodID() {
    cout << "Initializing the ParticleUpperBound methods" << std::endl;
    const int totalMethod = 1;
    string methodNames[totalMethod][2] = {
            {"Value", "(I)D"}
    };
    for (auto &methodName: methodNames) {
        particleUpperBoundMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getParticleUpperBoundClass(),
                                                                                            methodName[0].c_str(),
                                                                                            methodName[1].c_str()));
    }
    cout << "Initialization of ParticleUpperBound methods Complete" << std::endl;
}

void AjanHelper::GetAllAjanPolicyMethodID() {
    cout << "Initializing the AJAN Policy methods" << std::endl;
    const int totalMethod = 2;
    string methodNames1[totalMethod][2] = {
            {"Action", "(" + getSig(VECTOR) + "J)I",},
            {"TestMethod", "()I"}
    };

    for (auto &methodName: methodNames1) {
        ajanPolicyMethods[methodName[0]] = (methodName[0], getEnv()->GetMethodID(getPolicyClass(),
                                                                                    methodName[0].c_str(),
                                                                                    methodName[1].c_str()));
    }
    cout << "Initialization of AJAN Policy methods Complete" << std::endl;
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
    } else {
        cout << "Cannot find the method" << endl;
        return nullptr;
    }
}


