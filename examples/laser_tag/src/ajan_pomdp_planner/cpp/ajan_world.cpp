//
// Created by bhuvanesh on 01.08.23.
// JNI Interface for World
// @see: unified_pomdp_planner/unified_laser_tag_world.cpp
//

#include "ajan_world.h"

using namespace despot;

/**
 * Connect to the environment (for simulators)
 * @return the status of the connection
 */
bool AjanWorld::Connect() {
    // TODO: Implement AjanWorld:Connect Function to call JNI
    /**
     * 1. Initialize the ROS node \n
     * 2. get the laser's noise sigma \n
     * 3. wait for laser tag controller service to show up \n
     * 4.Setup service client
     **/
    return true;
}

/**
 * Initialize or reset the environment (for simulators or POMDP world only)
 * @return the start state of the system if applicable
 */
State *AjanWorld::Initialize() {
    // TODO: Implement AjanWorld::Initialize Function to call JNI
    // WARN: Watch out for NULL returning.
    return nullptr;
}

/**
 * Get the state of the system (only applicable for simulators or POMDP world)
 * @return the current state of the system if applicable
 */
State *AjanWorld::GetCurrentState() {
    // TODO: Implement AjanWorld::GetCurrentState Function to call JNI
    // WARN: Watch out for NULL returning.
    return nullptr;
}

/**
 * Send action to be executed by the system, receive observations terminal signals from the system
 * @return true/1 to exit, false/0 to continue
 */
bool AjanWorld::ExecuteAction(ACT_TYPE action, OBS_TYPE &obs) {
    // TODO: Implement AjanWorld::ExecuteAction Function to call JNI
    /**
     * 1. Set the srv.action to given action // actions: 0 - North, 1 - East, 2 - South, 3 - West, 4 - Tag \n
     * 2. If connected and successfully tagged, exit -> return 1 else continue to observe \n
     * 3. Get the Observations and SetReading to provided obs. and return 0 to continue. \n
     **/
    return false;
}
