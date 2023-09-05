//
// Created by bhuvanesh on 10.08.23.
//

#include <despot/core/history.h>
#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History.h"
#include "ajan_helper.h"

using namespace despot;

[[maybe_unused]] JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Add_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr, jint action, jlong obs) {
    auto* history = reinterpret_cast<History*>(historyPtr);
    history->Add(action, obs);
}

[[maybe_unused]] JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_RemoveLast_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        history->RemoveLast();
}

[[maybe_unused]] JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Action_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr, jint t) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return history->Action(t);
}

[[maybe_unused]] JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Observation_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr, jint t) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return static_cast<jlong>(history->Observation(t));
}

[[maybe_unused]] JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Size_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return static_cast<jint>(history->Size()); // WARN: This might cause some data loss if the size is larger than standard int size
}

[[maybe_unused]] JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Truncate_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr, jint d) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        history->Truncate(d);
}

[[maybe_unused]] JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_LastAction_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return history->LastAction();
}

[[maybe_unused]] JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_LastObservation_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        return static_cast<jlong>(history->LastObservation());
}

[[maybe_unused]] JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_Suffix_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisHistoryObject, jlong historyPtr, jint s) {
        auto* history = reinterpret_cast<History*>(historyPtr);
        History suffixedHistory = history->Suffix(s);
        return AjanHelper::toJavaHistory(suffixedHistory);
}

[[maybe_unused]] JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_core_History_deleteHistory
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jclass thisHistoryObject, jlong historyPtr) {
    auto* history = reinterpret_cast<History*>(historyPtr);
    delete history;
}