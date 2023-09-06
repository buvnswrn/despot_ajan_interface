package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.example;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.AjanPlanner;

public class LaserTagPlanner extends AjanPlanner {
    @Override
    public boolean InitializeModel(){
        ajanAgent = new LaserTag();
        ajanWorld = new TagWorld(ajanAgent);
        return true;
    }

    public boolean InitializeWorld(String worldType) {
        System.out.println("World Type:"+worldType);
        ajanWorld = new TagWorld(ajanAgent);
        return true;
    }

    public static void main(String[] args){
        LaserTagPlanner planner = new LaserTagPlanner();
        planner.InitializeModel();
        planner.RunPlanner(planner.ajanAgent, planner.ajanWorld);
    }
}
