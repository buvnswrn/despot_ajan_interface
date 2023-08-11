//
// Created by bhuvanesh on 10.08.23.
//

#include <despot/core/history.h>
#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History.h"
#include "ajan_helper.h"

using namespace despot;

JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Add_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr, jint action, jlong obs) {
    auto* history = reinterpret_cast<History*>(historyPtr);
    history->Add(action, obs);
}

JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_RemoveLast_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        history->RemoveLast();
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Action_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr, jint t) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return history->Action(t);
}

JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Observation_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr, jint t) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return static_cast<jlong>(history->Observation(t));
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Size_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return static_cast<jint>(history->Size()); // WARN: This might cause some data loss if the size is larger than standard int size
}

JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Truncate_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr, jint d) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        history->Truncate(d);
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_LastAction_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return history->LastAction();
}

JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_LastObservation_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return static_cast<jlong>(history->LastObservation());
}

JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Suffix_1
        (JNIEnv * env, jobject thisHistoryObject, jlong historyPtr, jint s) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        History suffixedHistory = history->Suffix(s);
        AjanHelper helper = AjanHelper();
        return helper.toJavaHistory(suffixedHistory);
}