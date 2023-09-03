package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.Connector.ROSConnector;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.World;

import java.io.IOException;
import org.json.JSONArray;
import org.json.JSONObject;

import static de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.Connector.ROSConnector.*;

public class AjanWorld extends World {
    ROSConnector rosConnector = new ROSConnector();
    public long currentObservation;
    AjanAgent ajanAgent;

    protected AjanWorld(AjanAgent ajanAgent){
        this.ajanAgent = ajanAgent;
    }

    @Override
    protected boolean Connect() {
        /*
          1. Initialize the ROS node \n
          2. get the laser's noise sigma \n
          3. wait for laser tag controller service to show up \n
          4.Setup service client
         */
        try {
            InitializeROSClient();
        } catch (IOException e) {
            System.err.println("Error in Connecting to ROS Client"+e.getMessage());
            return false;
        }
        return true;
    }

    @Override
    protected State Initialize() {
        // TODO: Implement AjanWorld::Initialize Function to call JNI
        // WARN: Watch out for NULL returning.
        return null;
    }

    @Override
    protected State GetCurrentState() {
        // TODO: Implement AjanWorld::GetCurrentState Function to call JNI
        // WARN: Watch out for NULL returning.
        return null;
    }

    public long getCurrentObservation(){
        return currentObservation;
    }

    public void setCurrentObservation(long obs){
        currentObservation = obs;
    }

    @Override
    protected boolean ExecuteAction(int action, long obs) {
        // TODO: Implement AjanWorld::ExecuteAction Function to call JNI
        /*
         * 1. Set the srv.action to given action // actions: 0 - North, 1 - East, 2 - South, 3 - West, 4 - Tag \n
         * 2. If connected and successfully tagged, exit -> return 1 else continue to observe \n
         * 3. Get the Observations and SetReading to provided obs. and return 0 to continue. \n
         **/
        try{
            String executeActionResponse = String.valueOf(ROSConnector.ExecuteAction(action));
            JSONObject jsonObject = new JSONObject(executeActionResponse);
            JSONArray observations = (JSONArray) jsonObject.get("observations");
            if(action == TAG_ACTION && (boolean) jsonObject.get("tag_success")){
                currentObservation = 0;
                System.out.println("Tag action received");
                for (int dir = 0; dir < NUM_LASER_DIRECTIONS; dir++) {
                    currentObservation = SetReading(currentObservation,
//                            ((Number)variables.get(TERMINATION_OBSERVATION)).longValue(),dir);
                            101,dir);
                    System.out.println("Observation:"+currentObservation+","+101+","+dir);
                }
                return true; // exit
            }

            // continue to observe
            else {
                System.out.println("Laser Observations");
                System.out.println("North: "+ observations.get(0));
                System.out.println("East: "     + observations.get(1));
                System.out.println("South: "    + observations.get(2));
                System.out.println("West: "     + observations.get(3));
                System.out.println("NorthEast: "+ observations.get(4));
                System.out.println("SouthEast: "+ observations.get(5));
                System.out.println("SouthWest: "+ observations.get(6));
                System.out.println("NorthWest: "+ observations.get(7));
                for (int dir = 0; dir < 8; dir++) {
                    currentObservation = SetReading(currentObservation,(int) observations.get(dir), dir);
                    System.out.println("Observation:"+currentObservation+","+observations.get(dir)+","+dir);
                    // OPTIMIZE: Check for converting the data type to long instead of int
                }
                return false; // continue
            }
        } catch (IOException e) {
            return false;
        }
    }
}
