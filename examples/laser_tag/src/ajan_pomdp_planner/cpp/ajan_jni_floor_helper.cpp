//
// Created by bhuvanesh on 05.09.23.
//

#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor.h"
#include "despot/util/floor.h"
#include "ajan_helper.h"

using namespace despot;
AjanHelper helper;
Floor floor_;
JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Init__
        (JNIEnv * env, jobject thisObject) {
    floor_ = Floor();
    return reinterpret_cast<jlong>(&floor_);
}

JNIEXPORT jlong JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Init__II
        (JNIEnv * env, jobject thisObject, jint rows, jint cols) {
    floor_ = Floor(rows,cols);
    return reinterpret_cast<jlong>(&floor_);
}

JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_AddCell
        (JNIEnv * env, jobject thisObject, jint x, jint y, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor *>(floorPtr);
    floor1->AddCell(Coord(x,y));
}

JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_GetCell
        (JNIEnv * env, jobject thisObject, jint x, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    Coord coord = floor1->GetCell(x);
    jclass s = env->FindClass("de/dfki/asr/ajan/pluginsystem/mdpplugin/utils/POMDP/DESPOT/util/Coord");
    jobject jcoord = env->AllocObject(s);
    jcoord = AjanHelper::getJavaObject(env,s, jcoord, "x","I",coord.x);
    jcoord = AjanHelper::getJavaObject(env,s, jcoord, "y","I",coord.y);
    return jcoord;
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_GetIndex
        (JNIEnv *, jobject, jint x, jint y, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:GetIndex"<<endl;
    return floor1->GetIndex(x,y);
}

JNIEXPORT jboolean JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Inside__Lde_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Coord_2J
        (JNIEnv * env, jobject thisFloorObject, jobject, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:Coord:NotImplemented"<<endl;
    return true;
}

JNIEXPORT jboolean JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Inside__IIJ
        (JNIEnv * env, jobject thisFloorObject, jint x, jint y, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:Inside"<<endl;
    return floor1->Inside(x, y);
}

JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_ComputeDistances
        (JNIEnv * env, jobject thisFloorObject, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:ComputeDistances"<<endl;
    floor1->ComputeDistances();
}

JNIEXPORT jdouble JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_Distance
        (JNIEnv * env, jobject thisFloorObject, jint c1, jint c2, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:Distance"<<endl;
    return floor1->Distance(c1, c2);
}

JNIEXPORT jobject JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_ComputeShortestPath
        (JNIEnv * env, jobject thisFloorObject, jint start, jint end, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:ComputeShortestPath"<<endl;
    return AjanHelper::toJavaIntegerVector(floor1->ComputeShortestPath(start, end));
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_num_1rows
        (JNIEnv * env, jobject thisFloorObject, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:num_1rows"<<endl;
    return floor1->num_rows();
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_num_1cols
        (JNIEnv * env, jobject thisFloorObject, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:num_1cols"<<endl;
    return floor1->num_cols();
}

JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_NumCells
        (JNIEnv * env, jobject thisFloorObject, jlong floorPtr) {
    auto * floor1 = reinterpret_cast<Floor*>(floorPtr);
    cout<<"Native:ajan_jni_floor_helper:NumCells"<<endl;
    return floor1->NumCells();
}

JNIEXPORT void JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_util_Floor_destroyNativeClass
        (JNIEnv * env, jobject thisFloorObject, jlong floorPtr) {
    cout<<"Native:ajan_jni_floor_helper:destroyNativeClass"<<endl;
    delete reinterpret_cast<Floor*>(floorPtr);
}