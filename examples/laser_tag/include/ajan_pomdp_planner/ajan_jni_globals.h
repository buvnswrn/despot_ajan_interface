//
// Created by bhuvanesh on 07.08.23.
//

#ifndef LASER_TAG_AJAN_JNI_GLOBALS_H
#define LASER_TAG_AJAN_JNI_GLOBALS_H
#include <string>
using namespace std;

static const string STRING = "java/lang/String";
extern const string VECTOR = "java/util/Vector";
static const string OBJECT = "java/lang/Object";

static const string PACKAGE_NAME = "de/dfki/asr/ajan/pluginsystem/mdpplugin/utils/POMDP/DESPOT/";
static const string IMPL_PKG = PACKAGE_NAME + "implementation/";
static const string CORE_PKG = PACKAGE_NAME + "core/";
static const string UTIL_PKG = PACKAGE_NAME + "util/";
static const string INTF_PKG = PACKAGE_NAME + "interface_/";

// region core
[[maybe_unused]] static const string GLOBALS = CORE_PKG + "Globals";
static const string HISTORY = CORE_PKG + "History";
//endregion

//region implementation

static const string AJAN_AGENT_STATE = IMPL_PKG + "AjanAgentState";
static const string AJAN_AGENT = IMPL_PKG + "AjanAgent";
static const string AJAN_BELIEF = IMPL_PKG + "AjanBelief";
static const string AJAN_BELIEF_POLICY = IMPL_PKG + "AjanBeliefPolicy";
static const string AJAN_PARTICLE_UPPER_BOUND = IMPL_PKG + "AjanParticleUpperBound";
static const string AJAN_POLICY = IMPL_PKG + "AjanPolicy";
static const string AJAN_UPPER_BOUND = IMPL_PKG + "AjanUpperBound";
[[maybe_unused]] static const string AJAN_WORLD = IMPL_PKG + "AjanWorld";

//endregion

//region interface_

static const string STATE = INTF_PKG + "State"; // Abstract class
static const string BELIEF = INTF_PKG + "Belief"; // Abstract class
static const string VALUED_ACTION = INTF_PKG + "ValuedAction";

//endregion

//region util

static const string COORD = UTIL_PKG + "Coord";
static const string FLOOR = UTIL_PKG + "Floor";

//endregion
#endif //LASER_TAG_AJAN_JNI_GLOBALS_H
