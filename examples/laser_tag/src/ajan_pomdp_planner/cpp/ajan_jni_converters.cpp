//
// Created by bhuvanesh on 10.08.23.
//

#include "ajan_helper.h"

jstring AjanHelper::toJavaString(const string& string1) {
    return getEnv()->NewStringUTF(string1.c_str());
}

string AjanHelper::getString(jobject javaString) {
    auto solverName = (jstring) javaString;
    return getEnv()->GetStringUTFChars(solverName, nullptr);
}

jobject AjanHelper::toJavaState(const State& state) {
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

AjanAgentState AjanHelper::getAjanAgentState(jobject javaAgentState) {
    AjanAgentState agentState;
    jfieldID state_id = getEnv()->GetFieldID(getStateClass(), "state_id", "I");
    jfieldID scenario_id = getEnv()->GetFieldID(getStateClass(), "scenario_id", "I");
    jfieldID weight = getEnv()->GetFieldID(getStateClass(), "weight", "D");
    agentState.state_id = getEnv()->GetIntField(javaAgentState, state_id);
    agentState.scenario_id = getEnv()->GetIntField(javaAgentState, scenario_id);
    agentState.weight = getEnv()->GetIntField(javaAgentState, weight);
    return agentState;
}

jobject AjanHelper::toJavaAjanAgentState(AjanAgentState agentState) {
    jclass ajanAgentStateClass = getStateClass();
    jobject ajanAgentState = getEnv()->NewObject(ajanAgentStateClass,
                                                 getMethodID("State","<init>"),
                                                 agentState.state_id,
                                                 agentState.scenario_id,
                                                 agentState.weight);
    return ajanAgentState;
}

jobject AjanHelper::toJavaCoord(Coord coord) {
    jclass javaCoordClass = getCoordClass();
    jobject javaCoord = getEnv()->NewObject(javaCoordClass, getMethodID("Coord","<init>"),coord.x, coord.y);
    return javaCoord;
}

Coord AjanHelper::fromJavaCoord(jobject javaCoord) {
    Coord coord;
    jfieldID x = getEnv()->GetFieldID(getCoordClass(), "x","I");
    jfieldID y = getEnv()->GetFieldID(getCoordClass(), "y","I");
    coord.x = getEnv()->GetIntField(javaCoord, x);
    coord.y = getEnv()->GetIntField(javaCoord, y);
    return coord;
}

jobject AjanHelper::toJavaAgentStateVector(const vector<State *> &particles) {
    jobject vectorObject = getEnv()->NewObject(getVectorClass(), getMethodID("Vector","<init>"));
    for (int i = 0; i < particles.size(); ++i) {
        jobject ajanStateObject = toJavaAjanAgentState((AjanAgentState &&) particles[i]); // WARN: Potential scope issue here
        getEnv()->CallBooleanMethod(vectorObject, getMethodID("Vector","add"), ajanStateObject);
        getEnv()->DeleteLocalRef(ajanStateObject);
    }
    return vectorObject;
}

vector<State *> AjanHelper::getAgentStateVector(jobject javaAgentStateVector) {
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
    auto* historyPtr = new History(history);
    jobject historyObject = getEnv()->NewObject(getHistoryClass(), getMethodID("History","<init>"),reinterpret_cast<jlong>(historyPtr));
    return historyObject;
}

History AjanHelper::getHistory(jobject javaHistory) {
    return History();
}







