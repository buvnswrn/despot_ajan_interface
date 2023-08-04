package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

public interface StateIndexer {

     int NumStates() ;
     int GetIndex( State state) ;
      State GetState(int index) ;

    
}
