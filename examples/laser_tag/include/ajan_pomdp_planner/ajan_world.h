//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for World
// @see: unified_pomdp_planner/unified_laser_tag_world.h
//

#ifndef SRC_AJAN_WORLD_H
#define SRC_AJAN_WORLD_H
#include <unified_laser_tag.h>
#include <despot/interface/world.h>
#include <ros/ros.h>
#include "ajan_helper.h"

using namespace despot;

class AjanWorld : public World {
public:
    ros::NodeHandlePtr nh;
    ros::ServiceClient client;
    AjanHelper* helper;

    virtual bool Connect();

    //Initialize or reset the environment (for simulators or POMDP world only), return the start state of the system if applicable
    virtual State* Initialize();

    //Get the state of the system (only applicable for simulators or POMDP world)
    [[maybe_unused]] virtual State* GetCurrentState();

    //Send action to be executed by the system, receive observations terminal signals from the system
    virtual bool ExecuteAction(ACT_TYPE action, OBS_TYPE& obs);

    static double noise_sigma_;
};


#endif //SRC_AJAN_WORLD_H
