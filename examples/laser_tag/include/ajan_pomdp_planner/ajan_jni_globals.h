//
// Created by bhuvanesh on 07.08.23.
//

#ifndef LASER_TAG_AJAN_JNI_GLOBALS_H
#define LASER_TAG_AJAN_JNI_GLOBALS_H
#include <string>
using namespace std;

const string STRING = "java/lang/String";
extern const string VECTOR = "java/util/Vector";
const string OBJECT = "java/lang/Object";

const string PACKAGE_NAME = "de/dfki/asr/ajan/pluginsystem/mdpplugin/utils/POMDP/DESPOT/";
const string IMPL_PKG = PACKAGE_NAME + "implementation/";
const string CORE_PKG = PACKAGE_NAME + "core/";
const string UTIL_PKG = PACKAGE_NAME + "util/";
const string INTF_PKG = PACKAGE_NAME + "interface_/";

// region core
const string GLOBALS = CORE_PKG + "Globals";
const string HISTORY = CORE_PKG + "History";
//endregion

//region implementation

const string AJAN_AGENT_STATE = IMPL_PKG + "AjanAgentState";
const string AJAN_AGENT = IMPL_PKG + "AjanAgent";
const string AJAN_BELIEF = IMPL_PKG + "AjanBelief";
const string AJAN_BELIEF_POLICY = IMPL_PKG + "AjanBeliefPolicy";
const string AJAN_PARTICLE_UPPER_BOUND = IMPL_PKG + "AjanParticleUpperBound";
const string AJAN_POLICY = IMPL_PKG + "AjanPolicy";
const string AJAN_UPPER_BOUND = IMPL_PKG + "AjanUpperBound";
const string AJAN_WORLD = IMPL_PKG + "AjanWorld";

//endregion

//region interface_

const string STATE = INTF_PKG + "State";
const string BELIEF = INTF_PKG + "Belief";
const string VALUED_ACTION = INTF_PKG + "ValuedAction";

//endregion

//region util

const string COORD = UTIL_PKG + "Coord";
const string Floor = UTIL_PKG + "Floor";

//endregion
#endif //LASER_TAG_AJAN_JNI_GLOBALS_H
