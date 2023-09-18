//
// Created by bhuvanesh on 10.09.23.
//

#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Ajan_Util_Helper.h"
#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_Connector_ROSConnector.h"
#include <despot/util/util.h>

using namespace despot;

JNIEXPORT jdouble JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Ajan_1Util_1Helper_gausscdf
        (JNIEnv * env, jclass ajanUtilHelperClass, jdouble x, jdouble mean, jdouble sigma) {
    return gausscdf(x, mean, sigma);
}

JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_Connector_ROSConnector_SetReading_1
        (JNIEnv * env, jclass rosConnectorClass, jlong obs, jlong reading, jlong dir) {
    int BITS_PER_READING = 7;
    const uint64_t ONE = 1;
    obs &= ~(((ONE << BITS_PER_READING) - 1) << (dir * BITS_PER_READING));
    // Set bits
    obs |= reading << (dir * BITS_PER_READING);
    return obs;
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_Connector_ROSConnector_GetReading_1
        (JNIEnv * env, jclass rosConnectorClass, jlong obs, jlong dir) {
    int BITS_PER_READING = 7;
    const uint64_t ONE = 1;
    return (obs >> (dir * BITS_PER_READING)) & ((ONE << BITS_PER_READING) - 1);
}
