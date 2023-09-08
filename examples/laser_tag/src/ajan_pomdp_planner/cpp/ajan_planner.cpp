//
// Created by bhuvanesh on 08.08.23.
//


#include <despot/planner.h>
#include "de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_implementation_AjanPlanner.h"
#include "ajan_agent.h"
#include "ajan_world.h"

using namespace despot;
using namespace std;

class AjanPlanner : public Planner {
AjanHelper *helper;
public:
    DSPOMDP* InitializeModel(option::Option* options) override {
        // Initialize POMDP Model here;
        AjanAgent* model = new AjanAgent();
        helper = new AjanHelper();
        model->helper = helper;
        helper->Init(AjanHelper::getLastAjanJavaPlannerObject_S(), AjanHelper::getLastAjanJavaAgentObject_S(),
                     AjanHelper::getLastAjanJavaWorldObject_S());
        return model;
    }

    World* InitializeWorld(std::string& world_type, DSPOMDP* model, option::Option* options) override {
        // TODO: Make JNI Call to get World Type and Instantiate it.

        if(world_type == "pomdp") {
            return InitializePOMDPWorld(world_type, model, options);
        } else {
            cout<<"Create a world as defined and implemented by the user"<<endl;
            auto* world = new AjanWorld();
            world->helper = helper;
            cout<<"Establish connection with external system"<<endl;
            world->Connect();
            cout<<"Initialize the state of the external system"<<endl;
            world->Initialize();
            cout<<"Initialized"<<endl;
//            static_cast<AJANAgent*>(model)->NoiseSigma(world->noise_sigma_);
            cout<<"Assigned Noise sigma"<<endl;
            return world;
        }
    }

    void InitializeDefaultParameters() override {
        Globals::config.pruning_constant = 0.01;
    }

    std::string ChooseSolver() override {
        // TODO: Make JNI Call to get Solver name
        return "DESPOT";
    }
};

int main(int argc, char* argv[]) {
    return AjanPlanner().RunPlanning(argc, argv);
}

[[maybe_unused]] JNIEXPORT jint JNICALL Java_de_dfki_asr_ajan_pluginsystem_mdpplugin_utils_POMDP_DESPOT_implementation_AjanPlanner_RunPlanner
        ([[maybe_unused]] JNIEnv * env, [[maybe_unused]] jobject thisObject, [[maybe_unused]]  jobject agentObject, [[maybe_unused]]  jobject worldObject) {
    char* argv[] = {strdup("AJAN_Planner") };
    cout<<"Starting the AJAN-DESPOT Planner" <<endl;
    AjanHelper::S_Init(env, &thisObject, &agentObject, &worldObject);
    return AjanPlanner().RunEvaluation(1, argv);
}