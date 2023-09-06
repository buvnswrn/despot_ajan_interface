package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.example;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanAgent;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanParticleUpperBound;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.DespotPomdpGlobals;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Floor;

import java.util.Vector;

public class TagSPParticleUpperBound extends AjanParticleUpperBound {
    LaserTag tag_model_;

    TagSPParticleUpperBound(AjanAgent model, long cppReference) {
       super(model, cppReference);
       tag_model_ = (LaserTag) model;
       value_ = new Vector<>();
        Floor floor = tag_model_.floor_;
        value_.ensureCapacity(tag_model_.NumStates());
        for (int s = 0; s < tag_model_.NumStates(); s++) {
            int rob = tag_model_.rob_.get(s), opp = tag_model_.opp_.get(s);
            int dist = (int) floor.Distance(rob, opp);
            value_.add(s, -(1 - DespotPomdpGlobals.Discount(dist)) / (1 - DespotPomdpGlobals.Discount())
            + tag_model_.TAG_REWARD * DespotPomdpGlobals.Discount(dist));
        }
    }

    @Override
    protected double Value(State s) {
        LaserTagState state = (LaserTagState) s;
        return value_.get(state.state_id);
    }
}
