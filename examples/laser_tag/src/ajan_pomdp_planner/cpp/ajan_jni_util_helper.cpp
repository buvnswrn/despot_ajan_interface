//
// Created by bhuvanesh on 10.09.23.
//

#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Ajan_Util_Helper.h"
#include <despot/util/util.h>

using namespace despot;

JNIEXPORT jdouble JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Ajan_1Util_1Helper_gausscdf
        (JNIEnv * env, jclass ajanUtilHelperClass, jdouble x, jdouble mean, jdouble sigma) {
    return gausscdf(x, mean, sigma);
}
