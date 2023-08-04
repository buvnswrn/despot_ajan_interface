package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

import java.util.Vector;

public interface MMAPInferencer {
    State GetMMAP(Vector<State> particles);
}
