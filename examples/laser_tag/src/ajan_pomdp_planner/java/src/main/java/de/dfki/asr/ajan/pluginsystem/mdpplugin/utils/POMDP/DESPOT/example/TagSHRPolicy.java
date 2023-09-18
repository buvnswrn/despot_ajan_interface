package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.example;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.History;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanAgent;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanPolicy;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Compass;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Coord;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Floor;

import java.util.Random;
import java.util.Vector;

public class TagSHRPolicy extends AjanPolicy {
    LaserTag tag_model_; // TODO: Make sure this is and floor_ is set
    Floor floor_;
    public TagSHRPolicy(long cppReference) {
        super(cppReference);
    }

    public TagSHRPolicy(AjanAgent model) {
        super(model);
        tag_model_ = (LaserTag) model;
    }

    @Override
    protected int Action(Vector<State> particles, History history) {
        // If history is empty then take a random move
        if (history.Size() == 0) {
            Random random = new Random();
            return random.nextInt(tag_model_.NumActions() - 1);
        }

// Compute rob position
        Coord rob;
        if (tag_model_.same_loc_obs_ != floor_.NumCells()) {
//            cout<<"Getting MostLikelyRobotPosition"<<endl;
            rob = tag_model_.MostLikelyRobPosition(particles);
        } else {
           System.out.println("Getting Robot position from History LastObservation");
            rob = floor_.GetCell((int) history.LastObservation());
        }

// Compute opp position
        Coord opp;
        opp = tag_model_.MostLikelyOpponentPosition(particles);

        double distance = Coord.ManhattanDistance(rob, opp);

// If we just saw an opponent then TAG
        if (distance <= 1) {
            return tag_model_.TagAction();
        }
        Vector<Integer> actions = new Vector<>();

// Don't double back and don't go into walls
        for (int d = 0; d < 4; d++) {
            if (!Compass.Opposite(d, history.LastAction())
                    && floor_.Inside(Coord.Add(rob , Compass.DIRECTIONS[d], false))) {
                actions.add(d);
            }
        }

// Have to double back
        if (actions.size() == 0) {
            for (int d = 0; d < 4; d++) {
                if (floor_.Inside(Coord.Add(rob , Compass.DIRECTIONS[d], false)))
                    actions.add(d);
            }
        }

// Rob may be trapped by the obstacles
        if (actions.size() == 0)
            return 0;
        Random random =  new Random();
        return actions.get(random.nextInt(actions.size()));
    }

}
