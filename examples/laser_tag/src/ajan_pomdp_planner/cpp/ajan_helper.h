//
// Created by bhuvanesh on 01.08.23.
//

#ifndef LASER_TAG_AJAN_HELPER_H
#define LASER_TAG_AJAN_HELPER_H
#include <string>
#include <jni.h>
#include <map>
#include <despot/interface/pomdp.h>
#include "ajan_state.h"

using namespace std;
using namespace despot;
class AjanHelper {
//region Map to store all the methodIDS [Static]
    static map<string, jmethodID> plannerMethods;
    static map<string, jmethodID> agentMethods;
    static map<string, jmethodID> stateMethods;
    static map<string, jmethodID> particleUpperBoundMethods;
    static map<string, jmethodID> ajanPolicyMethods;
    static map<string, jmethodID> worldMethods;
    static map<string, jmethodID> vectorMethods;
    static map<string, jmethodID> coordMethods;
    static map<string, jmethodID> historyMethods;
//endregion

static JNIEnv* ajanJavaEnv;
static JNIEnv *getEnv();
static void setEnv(JNIEnv *&env);

//region AJAN Reference Objects [Non-Static]
    jobject *ajanJavaPlannerObject;
    jobject getAjanJavaPlannerObject();
    void setAjanJavaPlannerObject(jobject *plannerObject);

    jobject *ajanJavaAgentObject;
    jobject getAjanJavaAgentObject();
    void setAjanJavaAgentObject(jobject *plannerObject);

    jobject *ajanJavaWorldObject;
    jobject getAjanJavaWorldObject();
    void setAjanJavaWorldObject(jobject *plannerObject);

    jobject ajanParticleUpperBound;
    jobject getAjanParticleUpperBound();
    void setAjanParticleUpperBound(jobject *plannerObject);

    jobject ajanPolicyObject;
    jobject getAjanPolicyObject();
    void setAjanPolicyObject(jobject *plannerObject);
//endregion

//region AJAN Reference Classes
    static jclass plannerClass;
    static jclass getPlannerClass();
    static  void setPlannerClass(jclass plannerClass1);

    static jclass agentClass;
    static jclass getAgentClass();
    static void setAgentClass(jclass agentClass1);

    static jclass worldClass;
    static jclass getWorldClass();
    static void setWorldClass(jclass worldClass1);

    static jclass vectorClass;
    static jclass getVectorClass();
    static void setVectorClass(jclass vectorClass1);

    static jclass stateClass;
    static jclass getStateClass();
    static void setStateClass(jclass stateClass1);

    static jclass particleUpperBoundClass;
    static jclass getParticleUpperBoundClass();
    static void setParticleUpperBoundClass(jclass particleUpperBoundClass1);

    static jclass ajanPolicyClass;
    static jclass getPolicyClass();
    static void setPolicyClass(jclass policyClass1);

    static jclass coordClass;
    static jclass getCoordClass();
    static void setCoordClass(jclass coordClass1);

    static jclass floorClass;
    static jclass getFloorClass();
    static void setFloorClass(jclass floorClass1);

    static jclass historyClass;
    static jclass getHistoryClass();
    static void setHistoryClass(jclass historyClass1);

//endregion

//region JNI Cache Methods

    static string getSig(const string &method);
    void Init(JNIEnv *&env, jobject *plannerObject, jobject *agentObject, jobject *worldObject);

    void static getJavaClassReferences();
    void static GetAllMethodID();
    void static GetAllPlannerMethodID();
    void static GetAllAgentMethodID();
    void static GetAllStateMethodID();
    void static GetAllWorldMethodID();
    void static GetAllVectorMethodID();
    void static GetAllParticleUpperBoundMethodID();
    void static GetAllAjanPolicyMethodID();
    void static GetAllCoordMethodID();
    void static GetAllHistoryMethodID();

    jmethodID static getMethodID(const string& clazz, const string& methodName);

//endregion

//region JNI Converters

// TODO: To Java String
    static jstring toJavaString(const string& string1);
// TODO: From Java String
    static string getString(jobject javaString);
// TODO: DESPOT State to Java State
    jobject toJavaState(const State& state);
// TODO: Java State to DESPOT State
    State* getState(jobject javaState);
// TODO: Java Ajan Agent State to DESPOT Ajan Agent State
    AjanAgentState getAjanAgentState(jobject javaAgentState);
// TODO: DESPOT Ajan Agent State to Java Ajan Agent State
    jobject toJavaAjanAgentState(AjanAgentState agentState);
// TODO: To and From Coord
    jobject toJavaCoord(Coord coord);
    Coord fromJavaCoord(jobject javaCoord);

// TODO: CPP Vector to Java Vector : mainly vector<state> (may be vector(particles))
    jobject toJavaAgentStateVector(const vector<State *> &particles);
    vector < State*> getAgentStateVector(jobject javaAgentStateVector);

// TODO: Java History to DESPOT History
    History getHistory(jobject javaHistory);
// TODO: DESPOT Valued Action to Java Valued Action

// TODO: DESPOT Belief to Java Belief

// TODO: Java Belief to DESPOT Belief

// Optionals
// TODO: to and from Ajan Upper Bound
// TODO: to and from Ajan Particle Upper Bound
// TODO: to and from Ajan Belief Policy
// TODO: to and from Belief -> might not be possible so use AJAN_Belief (inheritor) instead
// TODO: To and from AJAN_Agent
// TODO: To and From Floor


//endregion
public:
// TODO: DESPOT History to Java History : either store the history address or copy complete particles
    static jobject toJavaHistory(const History& history);

};

#endif //LASER_TAG_AJAN_HELPER_H
