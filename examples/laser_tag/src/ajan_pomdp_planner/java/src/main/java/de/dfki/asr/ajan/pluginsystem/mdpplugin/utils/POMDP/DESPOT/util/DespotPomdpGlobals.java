package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util;

import static java.lang.Math.pow;

public class DespotPomdpGlobals {
    public static  String TRIVIAL = "TRIVIAL";
    public static  String LOOKAHEAD = "LOOKAHEAD";
    public static  String DEFAULT = "DEFAULT" ;
    public static  String MDP_ = "MDP" ;
    public static  String MANHATTAN = "MANHATTAN" ;
    public static  String SP = "SP" ;
    public static  String RANDOM = "RANDOM" ;
    public static  String SHR = "SHR" ;
    public static  String MMAP_MDP = "MMAP-MDP" ;
    public static  String MMAP_SP = "MMAP-SP" ;
    public static  String MODE_MDP = "MODE-MDP" ;
    public static  String MODE_SP = "MODE-SP" ;
    public static  String MAJORITY_MDP = "MAJORITY-MDP" ;
    public static  String MAJORITY_SP = "MAJORITY-SP" ;
    public static  String AJAN = "AJAN" ;
    public static  String UNSUPPORTED = "Unsupported Policy" ;

    public static double Discount(int d) {
        return pow(config.discount, d);
    }

    public static double Discount() {
        return config.discount;
    }
}
