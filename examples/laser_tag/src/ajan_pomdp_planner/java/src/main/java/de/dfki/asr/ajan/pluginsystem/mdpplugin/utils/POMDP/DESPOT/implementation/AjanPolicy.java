package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.DSPOMDP;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.DefaultPolicy;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;

import java.util.Vector;

public class AjanPolicy extends DefaultPolicy {
    long pointerToCpp;

    public AjanPolicy(long cppReference) {
        pointerToCpp = cppReference;
    }

    public AjanPolicy(DSPOMDP model) {
    }
    protected int Action(Vector<State> particles, History history) {
        // TODO: Implement AjanPolicy::Action Function to call JNI
        /*
         * 1. See whether RandomStreams are important or not.
         * 2. Do not pass RandomStreams to JNI \n
         * LOGIC (Laser_Tag): \n
         * 1. If history is empty then take a random move \n
         * 2. Compute rob position \n
         * 3. Compute opp position \n
         * 4. Compute their manhattan distance \n
         * 5. If we just saw an opponent then TAG \n
         * 6. Don't double back and don't go into walls. If one direction is not opposite to history.LastAction \n
         *  and current rob coordinate + Compass::DIRECTIONS(current direction) is Inside the floor \n
         *  (floor.Inside), then add direction to actions variable. \n
         * 7. Have to double back: if there are no actions, then if all four directions are inside the floor, \n
         *  then add directions to actions. \n
         * 8. Robot may be trapped by the obstacles : If still the actions are zero, then return 0 -> Indicating North. \n
         * 9. Else, choose a random action from the computed variables. \n
         */
        return 0;
    }

    public void SetReferenceToCpp_(long ptr) {
        this.pointerToCpp = ptr;
    }
}
