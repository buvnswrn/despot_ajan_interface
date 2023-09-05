//
// Created by bhuvanesh on 09.08.23.
//
#include "ajan_helper.h"
using namespace std;

// region Getter and Setter
JNIEnv * AjanHelper::ajanJavaEnv;
jclass AjanHelper::doubleClass;
jclass AjanHelper::integerClass;
jclass AjanHelper::longClass;
jclass AjanHelper::plannerClass;
jclass AjanHelper::agentClass;
jclass AjanHelper::worldClass;
jclass AjanHelper::vectorClass;
jclass AjanHelper::hashMapClass;
jclass AjanHelper::stateClass;
jclass AjanHelper::particleUpperBoundClass;
jclass AjanHelper::upperBoundClass;
jclass AjanHelper::ajanPolicyClass;
jclass AjanHelper::ajanBeliefPolicyClass;
jclass AjanHelper::coordClass;
jclass AjanHelper::floorClass;
jclass AjanHelper::historyClass;
jclass AjanHelper::valuedActionClass;
jclass AjanHelper::ajanBeliefClass;

JNIEnv *AjanHelper::getEnv() {return AjanHelper::ajanJavaEnv;}
void AjanHelper::setEnv(JNIEnv *&env) {AjanHelper::ajanJavaEnv = env;}

[[maybe_unused]] jobject AjanHelper::getAjanJavaPlannerObject() { return *ajanJavaPlannerObject; }
void AjanHelper::setAjanJavaPlannerObject(jobject *plannerObject) { ajanJavaPlannerObject = plannerObject; }

[[maybe_unused]] jobject AjanHelper::getAjanJavaAgentObject() const { return *ajanJavaAgentObject; }
void AjanHelper::setAjanJavaAgentObject(jobject *plannerObject) { ajanJavaAgentObject = plannerObject; }

[[maybe_unused]] jobject AjanHelper::getAjanJavaWorldObject() { return *ajanJavaWorldObject; }
void AjanHelper::setAjanJavaWorldObject(jobject *plannerObject) { ajanJavaWorldObject = plannerObject; }

[[maybe_unused]] jobject AjanHelper::getAjanParticleUpperBound() { return *ajanJavaWorldObject; }
//[[maybe_unused]] void AjanHelper::setAjanParticleUpperBound(jobject *plannerObject) { ajanParticleUpperBound = *plannerObject; }

[[maybe_unused]] jobject AjanHelper::getAjanPolicyObject() const { return ajanPolicyObject; }
[[maybe_unused]] void AjanHelper::setAjanPolicyObject(jobject *plannerObject) { ajanPolicyObject = *plannerObject; }

jclass AjanHelper::getDoubleClass() { return doubleClass; }
void AjanHelper::setDoubleClass(jclass doubleClass1) {doubleClass = doubleClass1;}

jclass AjanHelper::getIntegerClass() { return integerClass; }
void AjanHelper::setIntegerClass(jclass integerClass1) {integerClass = integerClass1;}

jclass AjanHelper::getLongClass() { return longClass; }
void AjanHelper::setLongClass(jclass longClass1) {longClass = longClass1;}

jclass AjanHelper::getPlannerClass() { return plannerClass; }
void AjanHelper::setPlannerClass(jclass plannerClass1) {plannerClass = plannerClass1;}

jclass AjanHelper::getAgentClass() { return agentClass; }
void AjanHelper::setAgentClass(jclass agentClass1) { agentClass = agentClass1; }

jclass AjanHelper::getWorldClass() { return worldClass; }
void AjanHelper::setWorldClass(jclass worldClass1) { worldClass=worldClass1; }

jclass AjanHelper::getVectorClass() { return vectorClass; }
void AjanHelper::setVectorClass(jclass vectorClass1) { vectorClass = vectorClass1; }

jclass AjanHelper::getHashMapClass() { return hashMapClass; }
void AjanHelper::setHashMapClass(jclass hashMapClass1) { hashMapClass = hashMapClass1; }

jclass AjanHelper::getStateClass() { return stateClass; }
void AjanHelper::setStateClass(jclass stateClass1) { stateClass = stateClass1; }

jclass AjanHelper::getParticleUpperBoundClass() { return particleUpperBoundClass; }
void AjanHelper::setParticleUpperBoundClass(jclass particleUpperBoundClass1) { particleUpperBoundClass = particleUpperBoundClass1; }

jclass AjanHelper::getUpperBoundClass() { return upperBoundClass; }
void AjanHelper::setUpperBoundClass(jclass upperBoundClass1) { upperBoundClass = upperBoundClass1; }

jclass AjanHelper::getPolicyClass() { return ajanPolicyClass; }
void AjanHelper::setPolicyClass(jclass ajanPolicyClass1) { ajanPolicyClass = ajanPolicyClass1; }

jclass AjanHelper::getBeliefPolicyClass() { return ajanBeliefPolicyClass; }
void AjanHelper::setBeliefPolicyClass(jclass ajanBeliefPolicyClass1) { ajanBeliefPolicyClass = ajanBeliefPolicyClass1; }

jclass AjanHelper::getCoordClass() { return coordClass; }
void AjanHelper::setCoordClass(jclass coordClass1) { coordClass = coordClass1; }

[[maybe_unused]] jclass AjanHelper::getFloorClass() { return floorClass; }
void AjanHelper::setFloorClass(jclass floorClass1) { floorClass = floorClass1; }

jclass AjanHelper::getHistoryClass() { return historyClass; }
void AjanHelper::setHistoryClass(jclass historyClass1) { historyClass = historyClass1; }

jclass AjanHelper::getValuedActionClass() { return valuedActionClass; }
void AjanHelper::setValuedActionClass(jclass valuedActionClass1) { valuedActionClass = valuedActionClass1; }

jclass AjanHelper::getAjanBeliefClass() { return ajanBeliefClass; }
void AjanHelper::setAjanBeliefClass(jclass ajanBeliefClass1) { ajanBeliefClass = ajanBeliefClass1; }

// endregion