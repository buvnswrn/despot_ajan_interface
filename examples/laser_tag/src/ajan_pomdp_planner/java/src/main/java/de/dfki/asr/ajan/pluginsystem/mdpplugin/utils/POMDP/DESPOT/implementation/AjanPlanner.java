package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

public class AjanPlanner {

    public AjanAgent ajanAgent;
    public AjanWorld ajanWorld;

//    static {
//        System.loadLibrary("ajanplanner");
//    }

    public boolean InitializeModel() {
        ajanAgent = new AjanAgent();
        ajanWorld = new AjanWorld(ajanAgent);
        return true;
    }

    public boolean InitializeWorld(String worldType) {
        System.out.println("World Type:"+worldType);
        ajanWorld = new AjanWorld(ajanAgent);
        return true;
    }

    public String ChooseSolver() {
        return "DESPOT";
    }

    public String getWorldType() {
        return "simulator";
    }

    private native int RunPlanner(AjanAgent ajanAgent, AjanWorld ajanWorld);

    public static void main(String[] args){
        AjanPlanner planner = new AjanPlanner();
        planner.InitializeModel();
        planner.RunPlanner(planner.ajanAgent, planner.ajanWorld);
    }
}
