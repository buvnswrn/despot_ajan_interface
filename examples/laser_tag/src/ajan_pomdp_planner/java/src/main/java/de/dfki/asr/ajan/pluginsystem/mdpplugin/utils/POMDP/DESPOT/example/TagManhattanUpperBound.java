package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.example;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanBelief;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanUpperBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.DSPOMDP;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Coord;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.DespotPomdpGlobals;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Floor;

import java.util.Vector;

public class TagManhattanUpperBound extends AjanUpperBound {

    LaserTag tag_model_;
    Vector<Double> value_;
    public TagManhattanUpperBound(long cppReference) {
        super(cppReference);
    }

    public TagManhattanUpperBound(DSPOMDP model) {
        tag_model_ = (LaserTag) model;
        value_ = new Vector<>();
        Floor floor = tag_model_.floor_;
        value_.ensureCapacity(tag_model_.NumStates());
        for (int s = 0; s < tag_model_.NumStates(); s++) {
            Coord rob = floor.GetCell(tag_model_.rob_.get(s)),
                    opp = floor.GetCell(tag_model_.opp_.get(s));
            int dist = Coord.ManhattanDistance(rob, opp);
            value_.add(s, -(1 - DespotPomdpGlobals.Discount(dist)) / (1 - DespotPomdpGlobals.Discount())
            + tag_model_.TAG_REWARD * DespotPomdpGlobals.Discount(dist));
        }
    }
    @Override
    public double Value(AjanBelief belief) {
      Vector<State> particles =(belief).particles();
        double value = 0;
        for (int i = 0; i < particles.size(); i++) {
            State particle = particles.get(i);
            LaserTagState state = (LaserTagState) particle;
            value += state.weight * value_.get(state.state_id);
        }
        return value;
    }

    @Override
    protected double Value(State s) {
        LaserTagState state = (LaserTagState) s;
        return value_.get(state.state_id);
    }

}
