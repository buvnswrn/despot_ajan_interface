package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;

public abstract class World {

    /**
     * Connect to the environment (for simulators)
     * @return the status of the connection
     */
    protected abstract boolean Connect();

    /**
     * Initialize or reset the environment (for simulators or POMDP world only)
     * @return pointer to the start state of the system if applicable
     */
    protected abstract State Initialize();

    /**
     * Get the state of the system (only applicable for simulators or POMDP world)
     * @return the pointer to the start state
     */
    protected abstract State GetCurrentState();

    /**
     * Send action to be executed by the system, receive observations terminal signals from the system
     * @param action the action to be executed by the system
     * @param obs observation to be updated -> &obs
     * @return true/1 to exit, false/0 to continue
     */
    protected abstract boolean ExecuteAction(int action, long obs);

}
