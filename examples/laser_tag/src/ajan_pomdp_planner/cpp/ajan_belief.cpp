//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for Beliefs.
// See: examples/laser_tag/include/unified_pomdp_planner/tag_belief.cpp
//
#include "ajan_belief.h"

using namespace despot;
/* ==============================================================================
 * AjanBelief class
 * ==============================================================================*/
[[maybe_unused]] despot::AjanBelief::AjanBelief(std::vector<despot::State *> particles, const despot::DSPOMDP *model, despot::Belief *prior):
despot::ParticleBelief(particles, model, prior, false),
tag_model_(model){
// TODO: Implement AjanBelief::AjanBelief to call using JNI
}

void despot::AjanBelief::Update(despot::ACT_TYPE action, despot::OBS_TYPE obs) {
    // TODO: Implement AjanBelief::Update using JNI
    // WARN: Be careful here (as this affects performance)

    /** call Tau using JNI
        1. Free the particles from the particle belief -> Seems like a typical step
        2. get the updated particles -> Seems like a typical step
        3. Always DESPOT has the history and in Java end We do not have any sort of History to do anything,
            so it's better to do all history related functions here in C++ and not Java.-> Reconsider later
        4. See the AjanAgent::Tau Function
        5. Functional Equivalence: See whether in Tau we can use multiple JNI calls
            to update a single particle instead of copying and sending all of them.
        6. In Java, assign obj=null; System.gc(); to garbage collect the variables.
    **/
AjanHelper::getEnv()->CallVoidMethod(javaReferenceObject, AjanHelper::getMethodID(AJAN_BELIEF,Update_), action, obs);
}

[[maybe_unused]] JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_interface_1_Belief_Sample_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisBeliefObject, jlong beliefPtr, jint num) {
    auto* belief = reinterpret_cast<Belief *>(beliefPtr);
    return AjanHelper::toJavaAgentStateVector(belief->Sample(num));
}

[[maybe_unused]] JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_interface_1_Belief_Update_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisBeliefObject, [[maybe_unused]] jlong beliefPtr, [[maybe_unused]] jint action, [[maybe_unused]] jlong obs) {
// WARN: Potential Deadlock here
}

[[maybe_unused]] JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_interface_1_Belief_MakeCopy_1
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisBeliefObject, jlong beliefPtr) {
    cout<<"JNI:MakeCopy:This method should not be called";
    auto* belief = reinterpret_cast<Belief *>(beliefPtr);
    return AjanHelper::toJavaAjanBelief(belief->MakeCopy());
}