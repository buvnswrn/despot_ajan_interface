/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor */

#ifndef _Included_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
#define _Included_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    Init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Init__
  (JNIEnv *, jobject);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    Init
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Init__II
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    AddCell
 * Signature: (IIJ)V
 */
JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_AddCell
  (JNIEnv *, jobject, jint, jint, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    GetCell
 * Signature: (IJ)Lde/dfki/asr/ajan/pluginsystem/mdpplugin/utils/POMDP/DESPOT/util/Coord;
 */
JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_GetCell
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    GetIndex
 * Signature: (Lde/dfki/asr/ajan/pluginsystem/mdpplugin/utils/POMDP/DESPOT/util/Coord;J)I
 */
JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_GetIndex
  (JNIEnv *, jobject, jobject, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    Inside
 * Signature: (Lde/dfki/asr/ajan/pluginsystem/mdpplugin/utils/POMDP/DESPOT/util/Coord;J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Inside__Lde_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Coord_2J
  (JNIEnv *, jobject, jobject, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    Inside
 * Signature: (IIJ)Z
 */
JNIEXPORT jboolean JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Inside__IIJ
  (JNIEnv *, jobject, jint, jint, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    ComputeDistances
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_ComputeDistances
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    Distance
 * Signature: (IIJ)D
 */
JNIEXPORT jdouble JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Distance
  (JNIEnv *, jobject, jint, jint, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    ComputeShortestPath
 * Signature: (IIJ)Ljava/util/Vector;
 */
JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_ComputeShortestPath
  (JNIEnv *, jobject, jint, jint, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    num_rows
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_num_1rows
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    num_cols
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_num_1cols
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    NumCells
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_NumCells
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor
 * Method:    destroyNativeClass
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_destroyNativeClass
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
