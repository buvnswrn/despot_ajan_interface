//
// Created by bhuvanesh on 07.08.23.
//

#ifndef LASER_TAG_AJAN_JNI_GLOBALS_H
#define LASER_TAG_AJAN_JNI_GLOBALS_H
#include <string>
using namespace std;

static const string STRING = "java/lang/String";
static const string VECTOR = "java/util/Vector";
static const string HASHMAP = "java/util/HashMap";
static const string DOUBLE = "java/lang/Double";
static const string INTEGER = "java/lang/Integer";
static const string LONG = "java/lang/Long";
static const string OBJECT = "java/lang/Object";

static const string PACKAGE_NAME = "de/dfki/asr/ajan/pluginsystem/mdpplugin/utils/POMDP/DESPOT/";
static const string IMPL_PKG = PACKAGE_NAME + "implementation/";
static const string EXAMPLE_PKG = PACKAGE_NAME + "example/";
static const string CORE_PKG = PACKAGE_NAME + "core/";
static const string UTIL_PKG = PACKAGE_NAME + "util/";
static const string INTF_PKG = PACKAGE_NAME + "interface_/";

// region core
[[maybe_unused]] static const string GLOBALS = CORE_PKG + "Globals";
static const string HISTORY = CORE_PKG + "History";
//endregion

//region implementation

static const string AJAN_AGENT_STATE = EXAMPLE_PKG + "LaserTagState";
static const string AGENT_STATE = IMPL_PKG + "AjanAgentState";
static const string AJAN_AGENT_OG = IMPL_PKG + "AjanAgent";
static const string AJAN_AGENT = EXAMPLE_PKG + "LaserTag";
static const string AJAN_BELIEF = IMPL_PKG + "AjanBelief";
static const string AJAN_BELIEF_POLICY = EXAMPLE_PKG + "TagBlindBeliefPolicy";
static const string AJAN_PARTICLE_UPPER_BOUND = EXAMPLE_PKG + "TagSPParticleUpperBound";
static const string AJAN_PARTICLE_LOWER_BOUND = IMPL_PKG + "AjanParticleLowerBound";
static const string AJAN_POLICY = EXAMPLE_PKG + "TagSHRPolicy";
static const string AJAN_UPPER_BOUND = EXAMPLE_PKG + "TagManhattanUpperBound";
[[maybe_unused]] static const string AJAN_WORLD = EXAMPLE_PKG + "TagWorld";
[[maybe_unused]] static const string AJAN_PLANNER = EXAMPLE_PKG + "LaserTagPlanner";

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
