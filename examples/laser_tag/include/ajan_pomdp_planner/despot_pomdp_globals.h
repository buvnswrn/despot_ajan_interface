//
// Created by bhuvanesh on 29.08.23.
//

#ifndef LASER_TAG_DESPOT_POMDP_GLOBALS_H
#define LASER_TAG_DESPOT_POMDP_GLOBALS_H
#include <string>
using namespace std;

//region Built-in BeliefUpperBound

static const string TRIVIAL = "TRIVIAL";
[[maybe_unused]] static const string LOOKAHEAD = "LOOKAHEAD";
static const string DEFAULT = "DEFAULT" ;
static const string MDP_ = "MDP" ;
static const string MANHATTAN = "MANHATTAN" ;
static const string SP = "SP" ;
static const string RANDOM = "RANDOM" ;
static const string SHR = "SHR" ;
static const string MMAP_MDP = "MMAP-MDP" ;
static const string MMAP_SP = "MMAP-SP" ;
static const string MODE_MDP = "MODE-MDP" ;
static const string MODE_SP = "MODE-SP" ;
static const string MAJORITY_MDP = "MAJORITY-MDP" ;
static const string MAJORITY_SP = "MAJORITY-SP" ;
static const string AJAN = "AJAN" ;

//endregion
#endif //LASER_TAG_DESPOT_POMDP_GLOBALS_H
