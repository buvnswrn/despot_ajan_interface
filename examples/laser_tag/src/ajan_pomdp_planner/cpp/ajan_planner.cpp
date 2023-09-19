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
        world_type = AjanHelper::fromJavaString(AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaPlannerObject(),
                                                                          AjanHelper::getMethodID(AJAN_PLANNER,GetWorldType_)));
        cout<<"Initialising world of type:"<<world_type<<std::endl;
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
//        return AjanHelper::fromJavaString(AjanHelper::getEnv()->CallObjectMethod(helper->getAjanJavaPlannerObject(),
//                                               AjanHelper::getMethodID(AJAN_PLANNER, ChooseSolver_)));
        return "DESPOT";
    }

    /*Customize your planning pipeline by overloading the following function if necessary*/
    void PlanningLoop(Solver*& solver, World* world, Logger* logger) {
        for (int i = 0; i < Globals::config.sim_len; i++) {
            bool terminal = RunStep(solver, world, logger);
            if (terminal)
                break;
        }
    }

    /*Customize the inner step of the planning pipeline by overloading the following function if necessary*/
    bool RunStep(Solver* solver, World* world, Logger* logger) {
        logger->CheckTargetTime();

        double step_start_t = get_time_second();

        double start_t = get_time_second();
        ACT_TYPE action = solver->Search().action;
        double end_t = get_time_second();
        double search_time = (end_t - start_t);
        logi << "[Custom RunStep] Time spent in " << typeid(*solver).name()
             << "::Search(): " << search_time << endl;

        OBS_TYPE obs;
        start_t = get_time_second();
        bool terminal = world->ExecuteAction(action, obs);
        end_t = get_time_second();
        double execute_time = (end_t - start_t);
        logi << "[Custom RunStep] Time spent in ExecuteAction(): " << execute_time << endl;

        start_t = get_time_second();
        solver->BeliefUpdate(action, obs);
        end_t = get_time_second();
        double update_time = (end_t - start_t);
        logi << "[Custom RunStep] Time spent in Update(): " << update_time << endl;

        return logger->SummarizeStep(step_++, round_, terminal, action, obs,
                                     step_start_t);
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