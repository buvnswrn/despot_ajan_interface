//
// Created by bhuvanesh on 09.08.23.
//
#include <iostream>
#include "ajan_helper.h"
#include "ajan_jni_globals.h"
using namespace std;

// region Getter and Setter

JNIEnv *AjanHelper::getEnv() {return ajanJavaEnv;}
void AjanHelper::setEnv(JNIEnv *&env) {ajanJavaEnv = env;}

jobject AjanHelper::getAjanJavaPlannerObject() { return *ajanJavaPlannerObject; }
void AjanHelper::setAjanJavaPlannerObject(jobject *plannerObject) { ajanJavaPlannerObject = plannerObject; }

jobject AjanHelper::getAjanJavaAgentObject() { return *ajanJavaAgentObject; }
void AjanHelper::setAjanJavaAgentObject(jobject *plannerObject) { ajanJavaAgentObject = plannerObject; }

jobject AjanHelper::getAjanJavaWorldObject() { return *ajanJavaWorldObject; }
void AjanHelper::setAjanJavaWorldObject(jobject *plannerObject) { ajanJavaWorldObject = plannerObject; }

jobject AjanHelper::getAjanParticleUpperBound() { return *ajanJavaWorldObject; }
void AjanHelper::setAjanParticleUpperBound(jobject *plannerObject) { ajanParticleUpperBound = *plannerObject; }

jobject AjanHelper::getAjanPolicyObject() { return ajanPolicyObject; }
void AjanHelper::setAjanPolicyObject(jobject *plannerObject) { ajanPolicyObject = *plannerObject; }

jclass AjanHelper::getPlannerClass() { return plannerClass; }
void AjanHelper::setPlannerClass(jclass plannerClass1) {plannerClass = plannerClass1;}

jclass AjanHelper::getAgentClass() { return agentClass; }
void AjanHelper::setAgentClass(jclass agentClass1) { agentClass = agentClass1; }

jclass AjanHelper::getWorldClass() { return worldClass; }
void AjanHelper::setWorldClass(jclass worldClass1) { worldClass=worldClass1; }

jclass AjanHelper::getVectorClass() { return vectorClass; }
void AjanHelper::setVectorClass(jclass vectorClass1) { vectorClass = vectorClass1; }

jclass AjanHelper::getStateClass() { return stateClass; }
void AjanHelper::setStateClass(jclass plannerClass1) { plannerClass = plannerClass1; }

jclass AjanHelper::getParticleUpperBoundClass() { return particleUpperBoundClass; }
void AjanHelper::setParticleUpperBoundClass(jclass particleUpperBoundClass1) { particleUpperBoundClass = particleUpperBoundClass1; }

jclass AjanHelper::getPolicyClass() { return ajanPolicyClass; }
void AjanHelper::setPolicyClass(jclass ajanPolicyClass1) { ajanPolicyClass = ajanPolicyClass1; }

jclass AjanHelper::getCoordClass() { return coordClass; }
void AjanHelper::setCoordClass(jclass coordClass1) { coordClass = coordClass1; }

jclass AjanHelper::getFloorClass() { return floorClass; }
void AjanHelper::setFloorClass(jclass floorClass1) { floorClass = floorClass1; }

// endregion