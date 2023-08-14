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
#include "ajan_agent.h"
#include "ajan_particleupperbound.h"

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
    static map<string, jmethodID> doubleMethods;
    static map<string, jmethodID> integerMethods;
    static map<string, jmethodID> coordMethods;
    static map<string, jmethodID> historyMethods;
    static map<string, jmethodID> valuedActionMethods;
    static map<string, jmethodID> ajanBeliefMethods;
//endregion

static JNIEnv* ajanJavaEnv;
static JNIEnv *getEnv();
static void setEnv(JNIEnv *&env);

//region AJAN Reference Objects [Non-Static]
    jobject *ajanJavaPlannerObject;
    [[maybe_unused]]  jobject getAjanJavaPlannerObject();
    void setAjanJavaPlannerObject(jobject *plannerObject);

    jobject *ajanJavaAgentObject;
    [[maybe_unused]] jobject getAjanJavaAgentObject();
    void setAjanJavaAgentObject(jobject *plannerObject);

    jobject *ajanJavaWorldObject;
    [[maybe_unused]] jobject getAjanJavaWorldObject();
    void setAjanJavaWorldObject(jobject *plannerObject);

    [[maybe_unused]] jobject ajanParticleUpperBound;
    [[maybe_unused]] jobject getAjanParticleUpperBound();
    [[maybe_unused]] void setAjanParticleUpperBound(jobject *plannerObject);

    jobject ajanPolicyObject;
    [[maybe_unused]] jobject getAjanPolicyObject();
    [[maybe_unused]] void setAjanPolicyObject(jobject *plannerObject);
//endregion
// region Java Reference Classes
    static jclass doubleClass;
    static jclass getDoubleClass();
    static  void setDoubleClass(jclass doubleClass1);

    static jclass integerClass;
    static jclass getIntegerClass();
    static  void setIntegerClass(jclass integerClass1);

    static jclass longClass;
    static jclass getLongClass();
    static  void setLongClass(jclass longClass1);
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
    [[maybe_unused]] static jclass getFloorClass();
    static void setFloorClass(jclass floorClass1);

    static jclass historyClass;
    static jclass getHistoryClass();
    static void setHistoryClass(jclass historyClass1);

    static jclass valuedActionClass;
    static jclass getValuedActionClass();
    static void setValuedActionClass(jclass historyClass1);
    static jclass ajanBeliefClass;
    static jclass getAjanBeliefClass();
    static void setAjanBeliefClass(jclass ajanBeliefClass1);

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
    void static GetAllDoubleMethodID();
    void static GetAllIntegerMethodID();
    void static GetAllParticleUpperBoundMethodID();
    void static GetAllAjanPolicyMethodID();
    void static GetAllCoordMethodID();
    void static GetAllHistoryMethodID();
    void static GetAllValuedActionMethodID();
    void static GetAllAjanBeliefMethodID();

    jmethodID static getMethodID(const string& clazz, const string& methodName);

//endregion

//region JNI Converters
public:
// TODO: Check String methods
    [[maybe_unused]] static jstring toJavaString(const string& string1);
    [[maybe_unused]] static string fromJavaString(jobject javaString);

// TODO: Check State methods
    [[maybe_unused]] static jobject toJavaState(const State& state);
    static State* fromJavaState(jobject javaState);

// TODO: Check Ajan Agent State
    static jobject toJavaAjanAgentState(const AjanAgentState& agentState);
    [[maybe_unused]] static AjanAgentState fromJavaAjanAgentState(jobject javaAgentState);

// TODO: To and From Coord
    [[maybe_unused]] static jobject toJavaCoord(Coord coord);
    [[maybe_unused]] static Coord fromJavaCoord(jobject javaCoord);

// TODO: CPP Vector to Java Vector : mainly vector<state> (may be vector(particles))
    [[maybe_unused]] static jobject toJavaAgentStateVector(const vector<State *> &particles);
    [[maybe_unused]] static vector < State*> fromJavaAgentStateVector(jobject javaAgentStateVector);

    [[maybe_unused]] static jobject toJavaDoubleVector(const vector<double> &particles);
    [[maybe_unused]] static vector <double> fromJavaDoubleVector(jobject javaDoubleVector);
    [[maybe_unused]] [[maybe_unused]] static jobject toJavaIntegerVector(const vector<int> &particles);
    [[maybe_unused]] [[maybe_unused]] static vector <int> fromJavaIntegerVector(jobject javaDoubleVector);

// TODO: Check History Methods: either store the history address or copy complete particles
    static jobject toJavaHistory(const History& history);
    [[maybe_unused]] static History fromJavaHistory(jobject javaHistory);

// TODO: Check Valued Action Methods
    [[maybe_unused]] static jobject toJavaValuedAction(ValuedAction valuedAction);
    [[maybe_unused]] static ValuedAction fromJavaValuedAction(jobject javaValuedAction);

// TODO: Java Belief to DESPOT Belief
//    [[maybe_unused]] static Belief getBelief(jobject javaBelief);
// Optionals
// [Not Needed] to and from Ajan Upper Bound
// TODO: to and from Ajan Particle Upper Bound
    [[maybe_unused]] static jobject toJavaAjanParticleUpperBound(const AjanParticleUpperBound *particleUpperBound);
static AjanParticleUpperBound* fromJavaAjanParticleUpperBound(const jobject particleUpperBoundObject);
// TODO: to and from Ajan Belief Policy
// TODO: to and from Belief -> might not be possible so use AJAN_Belief (inheritor) instead
// TODO: To and from AJAN_Agent
    static jobject toJavaAgentModel(const DSPOMDP *model);
    static DSPOMDP *fromJavaAgentModel(jobject modelObject);
//    static jobject toJavaAgentModel(const AjanAgent model);
//    static jobject toJavaAgentModel(const long modelPtr);
// TODO: To and From Floor

// TODO: DESPOT Belief to Java Belief
    [[maybe_unused]] static jobject toJavaBelief(const Belief* belief);
//    Belief getBelief(jobject javaBelief);

    static jobject toJavaDouble(double value);
    static jobject toJavaInteger(int value);
    [[maybe_unused]] static jobject toJavaLong(long value);

//endregion
};

#endif //LASER_TAG_AJAN_HELPER_H
