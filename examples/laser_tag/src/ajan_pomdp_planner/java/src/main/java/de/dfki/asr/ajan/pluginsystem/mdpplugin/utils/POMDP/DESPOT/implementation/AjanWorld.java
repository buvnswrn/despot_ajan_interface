package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.World;

public class AjanWorld extends World {

    @Override
    protected boolean Connect() {
        /*
          1. Initialize the ROS node \n
          2. get the laser's noise sigma \n
          3. wait for laser tag controller service to show up \n
          4.Setup service client
         */
        return true;
    }

    @Override
    protected State Initialize() {
        // TODO: Implement AjanWorld::Initialize Function to call JNI
        // WARN: Watch out for NULL returning.
        return null;
    }

    @Override
    protected State GetCurrentState() {
        // TODO: Implement AjanWorld::GetCurrentState Function to call JNI
        // WARN: Watch out for NULL returning.
        return null;
    }

    @Override
    protected boolean ExecuteAction(int action, long obs) {
        // TODO: Implement AjanWorld::ExecuteAction Function to call JNI
        /*
         * 1. Set the srv.action to given action // actions: 0 - North, 1 - East, 2 - South, 3 - West, 4 - Tag \n
         * 2. If connected and successfully tagged, exit -> return 1 else continue to observe \n
         * 3. Get the Observations and SetReading to provided obs. and return 0 to continue. \n
         **/
        return false;
    }
}
