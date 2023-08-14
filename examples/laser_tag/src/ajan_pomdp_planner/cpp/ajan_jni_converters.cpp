//
// Created by bhuvanesh on 10.08.23.
//

#include "ajan_helper.h"
#include "ajan_jni_globals.h"
#include "ajan_belief.h"

[[maybe_unused]] jstring AjanHelper::toJavaString(const string& string1) {
    return getEnv()->NewStringUTF(string1.c_str());
}

[[maybe_unused]] string AjanHelper::getString(jobject javaString) {
    auto solverName = (jstring) javaString;
    return getEnv()->GetStringUTFChars(solverName, nullptr);
}

[[maybe_unused]] jobject AjanHelper::toJavaState(const State& state) {
    jclass ajanStateClass = getStateClass();
//        jobject ajanState = getEnv()->AllocObject(ajanStateClass);
    jobject ajanState = getEnv()->NewObject(ajanStateClass, getMethodID("State","<init>"));
    jfieldID state_id = getEnv()->GetFieldID(ajanStateClass, "state_id", "I");
    jfieldID scenario_id = getEnv()->GetFieldID(ajanStateClass, "scenario_id", "I");
    jfieldID weight = getEnv()->GetFieldID(ajanStateClass, "weight", "D");
    getEnv()->SetIntField(ajanState, state_id, state.state_id);
    getEnv()->SetIntField(ajanState, scenario_id, state.scenario_id);
    getEnv()->SetDoubleField(ajanState, weight, state.weight);
//        cout<<"getAJANStateFromState:Returning"<<endl;
    return ajanState;
}

State* AjanHelper::getState(jobject javaState) {
    auto *state = new State;
    jfieldID state_id = getEnv()->GetFieldID(getStateClass(), "state_id", "I");
    jfieldID scenario_id = getEnv()->GetFieldID(getStateClass(), "scenario_id", "I");
    jfieldID weight = getEnv()->GetFieldID(getStateClass(), "weight", "D");
    state->state_id = getEnv()->GetIntField(javaState, state_id);
    state->scenario_id = getEnv()->GetIntField(javaState, scenario_id);
    state->weight = getEnv()->GetIntField(javaState, weight);
    return state;
}

[[maybe_unused]] AjanAgentState AjanHelper::getAjanAgentState(jobject javaAgentState) {
    AjanAgentState agentState;
    jfieldID state_id = getEnv()->GetFieldID(getStateClass(), "state_id", "I");
    jfieldID scenario_id = getEnv()->GetFieldID(getStateClass(), "scenario_id", "I");
    jfieldID weight = getEnv()->GetFieldID(getStateClass(), "weight", "D");
    agentState.state_id = getEnv()->GetIntField(javaAgentState, state_id);
    agentState.scenario_id = getEnv()->GetIntField(javaAgentState, scenario_id);
    agentState.weight = getEnv()->GetIntField(javaAgentState, weight);
    return agentState;
}

jobject AjanHelper::toJavaAjanAgentState(const AjanAgentState& agentState) {
    jclass ajanAgentStateClass = getStateClass();
    jobject ajanAgentState = getEnv()->NewObject(ajanAgentStateClass,
                                                 getMethodID("State","<init>"),
                                                 agentState.state_id,
                                                 agentState.scenario_id,
                                                 agentState.weight);
    return ajanAgentState;
}

jobject AjanHelper::toJavaDouble(const double value){
    jclass javaDoubleClass = getDoubleClass();
    jobject javaDoubleObject = getEnv()->NewObject(javaDoubleClass,
                                                   getMethodID("Double","<init>"),
                                                   value);
    return javaDoubleObject;
}

jobject AjanHelper::toJavaInteger(const int value){
    jclass javaIntegerClass = getIntegerClass();
    jobject javaIntegerObject = getEnv()->NewObject(javaIntegerClass,
                                                    getMethodID("Integer","<init>"),
                                                    value);
    return javaIntegerObject;
}

[[maybe_unused]] jobject AjanHelper::toJavaLong(const long value){
    jclass javaLongClass = getLongClass();
    jobject javaLongObject = getEnv()->NewObject(javaLongClass,
                                                 getMethodID("Long","<init>"),
                                                 value);
    return javaLongObject;
}

[[maybe_unused]] jobject AjanHelper::toJavaCoord(Coord coord) {
    jclass javaCoordClass = getCoordClass();
    jobject javaCoord = getEnv()->NewObject(javaCoordClass, getMethodID("Coord","<init>"),coord.x, coord.y);
    return javaCoord;
}

[[maybe_unused]] Coord AjanHelper::fromJavaCoord(jobject javaCoord) {
    Coord coord;
    jfieldID x = getEnv()->GetFieldID(getCoordClass(), "x","I");
    jfieldID y = getEnv()->GetFieldID(getCoordClass(), "y","I");
    coord.x = getEnv()->GetIntField(javaCoord, x);
    coord.y = getEnv()->GetIntField(javaCoord, y);
    return coord;
}

[[maybe_unused]] jobject AjanHelper::toJavaAgentStateVector(const vector<State *> &particles) {
    jobject vectorObject = getEnv()->NewObject(getVectorClass(), getMethodID("Vector","<init>"));
    for (auto particle : particles) {
        jobject ajanStateObject = toJavaAjanAgentState((AjanAgentState &&) particle); // WARN: Potential scope issue here
        getEnv()->CallBooleanMethod(vectorObject, getMethodID("Vector","add"), ajanStateObject);
        getEnv()->DeleteLocalRef(ajanStateObject);
    }
    return vectorObject;
}

[[maybe_unused]] jobject AjanHelper::toJavaDoubleVector(const vector<double> &particles){
    jobject vectorObject = getEnv()->NewObject(getVectorClass(), getMethodID("Vector","<init>"));
    for (auto particle : particles) {
        jobject ajanStateObject = toJavaDouble( particle); // WARN: Potential scope issue here
        getEnv()->CallBooleanMethod(vectorObject, getMethodID("Vector","add"), ajanStateObject);
        getEnv()->DeleteLocalRef(ajanStateObject);
    }
    return vectorObject;
}

[[maybe_unused]] jobject AjanHelper::toJavaIntegerVector(const vector<int> &particles){
    jobject vectorObject = getEnv()->NewObject(getVectorClass(), getMethodID("Vector","<init>"));
    for (auto particle : particles) {
        jobject ajanStateObject = toJavaInteger( particle); // WARN: Potential scope issue here
        getEnv()->CallBooleanMethod(vectorObject, getMethodID("Vector","add"), ajanStateObject);
        getEnv()->DeleteLocalRef(ajanStateObject);
    }
    return vectorObject;
}

[[maybe_unused]] vector<State *> AjanHelper::getAgentStateVector(jobject javaAgentStateVector) {
    vector<State * > vectorOfStates;
    jint size = getEnv()->CallIntMethod(javaAgentStateVector, getMethodID("Vector","size"));
    jmethodID getMethod = getMethodID("Vector","get");
    for (int i = 0; i < size; i++) {
        jobject state = getEnv()->CallObjectMethod(javaAgentStateVector, getMethod, i);
        State * cstate = getState(state);
        vectorOfStates.push_back(cstate);
    }
    return vectorOfStates;
}

jobject AjanHelper::toJavaHistory(const History& history) {
    // cannot access the internals of history to copy it
    // If you come back here for changing to History* then see toJavaAgentModel and implement like that.
    auto* historyPtr = new History(history);
    jobject historyObject = getEnv()->NewObject(getHistoryClass(), getMethodID("History","<init>"),reinterpret_cast<jlong>(historyPtr));
    return historyObject;
}

[[maybe_unused]] History AjanHelper::getHistory(jobject javaHistory) {
    jfieldID historyPtrField = getEnv()->GetFieldID(getHistoryClass(),"historyPointer","J");
    long historyPtr = getEnv()->GetLongField(javaHistory, historyPtrField);
    return reinterpret_cast<History&&>(historyPtr);
}

[[maybe_unused]] jobject AjanHelper::toJavaValuedAction(ValuedAction valuedAction) {
    jobject valuedActionObject = getEnv()->NewObject(getValuedActionClass(), getMethodID("ValuedAction","<init>"),valuedAction.action, valuedAction.value);
    return valuedActionObject;
}

[[maybe_unused]] ValuedAction AjanHelper::getValuedAction(jobject javaValuedAction) {
    jfieldID actionFieldID = getEnv()->GetFieldID(getValuedActionClass(), "action","I");
    jfieldID valueFieldID = getEnv()->GetFieldID(getValuedActionClass(), "value","J");
    jint action = getEnv()->GetIntField(javaValuedAction, actionFieldID);
    jdouble value = getEnv()->GetDoubleField(javaValuedAction, valueFieldID);
    return {action,value};
}

[[maybe_unused]] jobject AjanHelper::toJavaBelief(const Belief* belief) {
    // converts belief to Ajan Belief in Java. Basically, adds up the particle vector, but more or less the same.
    jobject beliefObject = getEnv()->NewObject(getAjanBeliefClass(),getMethodID("AjanBelief","<init>"),reinterpret_cast<jlong>(belief));
    jobject historyObject = toJavaHistory(belief->history_);
    jobject modelObject = toJavaAgentModel(belief->model_);
    jfieldID  historyField = getEnv()->GetFieldID(getAjanBeliefClass(),"history_", getSig(AJAN_BELIEF).c_str());
    getEnv()->SetObjectField(beliefObject,historyField,historyObject);
    jfieldID  modelField = getEnv()->GetFieldID(getAjanBeliefClass(),"model_", getSig(AJAN_AGENT).c_str());
    getEnv()->SetObjectField(beliefObject,historyField,modelObject);
    getEnv()->SetObjectField(beliefObject, modelField, historyObject);
    getEnv()->DeleteLocalRef(historyObject);
    getEnv()->DeleteLocalRef(modelObject);
    return beliefObject;
}

//[[maybe_unused]] Belief AjanHelper::getBelief(jobject javaBelief) {
//    jfieldID historyFieldID = getEnv()->GetFieldID(getAjanBeliefClass(),"history_", getSig(AJAN_BELIEF).c_str());
//    jfieldID modelFieldID = getEnv()->GetFieldID(getAjanBeliefClass(),"model_", getSig(AJAN_AGENT).c_str());
//    jobject historyObject = getEnv()->GetObjectField(javaBelief,historyFieldID);
//    jobject modelObject = getEnv()->GetObjectField(javaBelief,modelFieldID);
//    History history = getHistory(historyObject);
//    DSPOMDP* model = getAgentModel(modelObject);
//    vector<State*> state;
//    AjanBelief ajanBelief = AjanBelief(state,dynamic_cast<AjanAgent *>(model));
//    return ajanBelief;
//}

jobject AjanHelper::toJavaAgentModel(const DSPOMDP *model) {
    auto modelPtr = reinterpret_cast<jlong>(model);
    jobject modelObject = getEnv()->NewObject(getHistoryClass(), getMethodID("Agent","<init>"),reinterpret_cast<jlong>(modelPtr));
    return modelObject;
}

DSPOMDP *AjanHelper::getAgentModel(jobject modelObject) {
    jfieldID historyPtrField = getEnv()->GetFieldID(getAgentClass(),"agentModelPointer","J");
    long modelPtr = getEnv()->GetLongField(modelObject, historyPtrField);
    return reinterpret_cast<DSPOMDP*>(modelPtr);
}

[[maybe_unused]] jobject AjanHelper::toJavaAjanParticleUpperBound(const AjanParticleUpperBound *particleUpperBound) {
    auto particleUpperBoundPtr = reinterpret_cast<jlong>(particleUpperBound);
    jobject particleUpperBoundObject = getEnv()->NewObject(getParticleUpperBoundClass(),
                                                     getMethodID("ParticleUpperBound","<init>"), particleUpperBoundPtr);
    jobject modelObject = toJavaAgentModel(particleUpperBound->tag_model_);
    jfieldID modelID = getEnv()->GetFieldID(getParticleUpperBoundClass(),"agent_model", getSig(AJAN_PARTICLE_UPPER_BOUND).c_str());
    getEnv()->SetObjectField(particleUpperBoundObject,modelID,modelObject);
    getEnv()->DeleteLocalRef(modelObject);
    // Have to write for value_
    jobject valueVectorObject = toJavaDoubleVector(particleUpperBound->value_);
    jfieldID valueID = getEnv()->GetFieldID(getParticleUpperBoundClass(),"value_", getSig(VECTOR).c_str());
    getEnv()->SetObjectField(particleUpperBoundObject,valueID,valueVectorObject);
    getEnv()->DeleteLocalRef(valueVectorObject);
    return particleUpperBoundObject;
}

AjanParticleUpperBound* AjanHelper::getAjanParticleUpperBound(const jobject particleUpperBoundObject) {
    // WARN: May be some issues here for not having Java Double vector initialized for value_
    jfieldID modelID = getEnv()->GetFieldID(getParticleUpperBoundClass(),"agent_model", getSig(AJAN_PARTICLE_UPPER_BOUND).c_str());
    jobject modelObject = getEnv()->GetObjectField(particleUpperBoundObject, modelID);
    DSPOMDP* agentModel = getAgentModel(modelObject);

    jfieldID doubleVectorID = getEnv()->GetFieldID(getVectorClass(),"value_", getSig(VECTOR).c_str());
    jobject doubleVectorObject = getEnv()->GetObjectField(particleUpperBoundObject, doubleVectorID);
    vector<double> valueVectorObject = getDoubleVector(doubleVectorObject);
    auto * particleUpperBound = new AjanParticleUpperBound((AjanAgent *)agentModel);
    return particleUpperBound;
}

vector<double> AjanHelper::getDoubleVector(jobject javaDoubleVector) {
    vector<double> result;
    jint size = getEnv()->CallIntMethod(javaDoubleVector, getMethodID("Vector","size"));
    for (int i = 0; i < size; i++) {
        jobject javaDouble = getEnv()->CallObjectMethod(javaDoubleVector, getMethodID("Vector","get"),i);
        jdouble value = getEnv()->CallDoubleMethod(javaDouble, getMethodID("Double","doubleValue"));
        result.push_back(value);
        getEnv()->DeleteLocalRef(javaDouble);
    }
    return result;
}

[[maybe_unused]] vector<int> AjanHelper::getIntVector(jobject javaIntegerVector) {
    vector<int> result;
    jint size = getEnv()->CallIntMethod(javaIntegerVector, getMethodID("Vector", "size"));
    for (int i = 0; i < size; i++) {
        jobject javaInt = getEnv()->CallObjectMethod(javaIntegerVector, getMethodID("Vector", "get"), i);
        jint value = getEnv()->CallIntMethod(javaInt, getMethodID("Integer", "intValue"));
        result.push_back(value);
        getEnv()->DeleteLocalRef(javaInt);
    }
    return result;
}






