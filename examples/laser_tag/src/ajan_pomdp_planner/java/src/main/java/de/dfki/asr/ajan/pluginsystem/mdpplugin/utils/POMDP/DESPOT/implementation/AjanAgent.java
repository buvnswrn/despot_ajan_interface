package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.*;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.*;

import java.lang.ref.Cleaner;
import java.util.Map;
import java.util.Vector;

public class AjanAgent implements MDP, BeliefMDP, StateIndexer, StatePolicy, MMAPInferencer, Cleaner.Cleanable  {

    public long agentModelPointer;
    public AjanAgent() {
        // TODO: Implement AjanAgent constructor to call JNI
        // read the Benchmark map
        // run init function
    }
    public AjanAgent(long modelPointer) {
        this.agentModelPointer= modelPointer;
    }

    // region MDP Functions
    @Override
    public int NumStates() {
        // TODO: Implement AjanAgent::NumStates to call JNI
        // Return number of cells
        return 0;
    }

    @Override
    public int NumActions() {
        // TODO: Implement AjanAgent::NumStates to call JNI
        // Return number of actions
        return 0;
    }

    @Override
    public Vector<State> TransitionProbability(int s, int a) {
        // TODO: Implement AjanAgent::TransitionProbability to call JNI
        // return transition_probabilities_[s][a];
        return null;
    }

    @Override
    public double Reward(int s, int a) {
        // TODO: Implement AjanAgent::TransitionProbability to call JNI
        // If action is tag, and tagged -> tag reward else - tag reward else reward  = -1 (longer it takes, lower is the reward)
        return 0;
    }
    //endregion

    //region Belief MDP

    @Override
    public AjanBeliefPolicy CreateBeliefLowerBound(String name) {
        // TODO: Implement AjanAgent::CreateBeliefLowerBound to call JNI
        // OPTIMIZE: Check how to use built-in bounds
        /*
         * Use some built-in bound - TrivialBeliefLowerBound
         **/
        return null;
    }

    @Override
    public BeliefUpperBound CreateBeliefUpperBound(String name) {
        // TODO: Implement AjanAgent::CreateBeliefUpperBound to call JNI
        // OPTIMIZE: Check how to use built-in bounds
        /*
         * Use some built-in bound - MDPUpperBound, TrivialBeliefUpperBound, LookaheadUpperBound (Scenario Upperbound)
         **/
        return null;
    }

    @Override
    public AjanBelief Tau(Belief belief, int action, long obs) {
        // TODO: Implement AjanAgent::Tau to call JNI - Try this or use getTauParticles Method
        // WARN: See how to manipulate belief and history particles efficiently
        /*
         * Calculates the sum of current weight * next weight * observation probability given state and action.
         * Updates the particles and creates new belief
         */
        AjanBelief belief1 = new AjanBelief();
        return null;
    }

    @Override
    public void Observe(Belief belief, int action, Map<Long, Double> obs) {
        // TODO: Implement AjanAgent::Observe to call JNI
        // Not real implementation here just "too many observations" print message
    }

    @Override
    public double StepReward(Belief belief, int action) {
        // TODO: Implement AjanAgent::StepReward to call JNI
        // WARN: Careful about the history manipulation
        // Calculate the cumulative reward until here according to the actions given.
        return 0;
    }
    //endregion

    //region StateIndexer
    @Override
    public int GetIndex(State state) {
        // TODO: Implement AjanAgent::GetIndex to call JNI
        //return state->state_id;
        return 0;
    }

    @Override
    public State GetState(int index) {
        // TODO: Implement AjanAgent::GetState to call JNI
        //return states_[index];
        return null;
    }
    //endregion

    //region StatePolicy
    @Override
    public int GetAction(State state) {
        // TODO: Implement AjanAgent::GetAction to call JNI
        // return default_action_[GetIndex(state)]
        return 0;
    }
    //endregion

    //region MMAPInferencer

    @Override
    public State GetMMAP(Vector<State> particles) {
        // TODO: Implement AjanAgent::GetMMAP to call JNI
        /*
         * 1. Calculate most likely rob and opp position coordinate
         * 2. Calculate the indices of both robots to state index
         * 3. return the state variable stored for the particular index
         */
        return null;
    }

    //endregion

    //region POMDP

    @Override
    public boolean Step(State state, double random_num, int action, double reward, long obs) {
        //TODO: Implement AjanAgent::Step function to call JNI
        /*
         * 1. Compute the reward after calculating the distance of rob and opp \n
         * 2. Compute the sum of weight for random_num of next states and get the state_id of state that has greater weight than the calculated sum \n
         * 3. Assign the given state to be the calculated state_id \n
         * 4. return terminal=true if the tag is done.
         */
        return false;
    }

    @Override
    public boolean Step(State state, double random_num, int action, double reward) {
        //TODO: Implement AjanAgent::Step function to call JNI
        /*
         * 1-4. Repeat the steps like for above step function \n
         * 5. Update the observation as 101 if the terminal has reached or rob and opp is in same state_id i.e. same cell,
         * else, update the observation:
         * for each the direction deduct the mass based on the reading_distribution until it is less than Globals::TINY and then set the reading to observation variable.
         */
        return false;
    }

    @Override
    public boolean Step(State state, int action, double reward, long obs) {
        return false;
    }

    @Override
    public double Reward(State state, int action) {
        return 0;
    }

    @Override
    public double ObsProb(long obs, State state, int action) {
        //TODO: Implement AjanAgent::ObsProb function to call JNI
        double prod = 1.0;
        /*
         * 1. Update the observation if rob and opp has same state_id
         * 2. Get the reading in each direction and return 0 if the reading is greater than the LaserRange of the state in that particular direction, else, multiply the probability mass based on the stored reading_distribution for that state, dir and reading.
         */
        return 0;
    }

    @Override
    public State CreateStartState(String type) {
        //TODO: Implement AjanAgent::CreateStartState function to call JNI
        //return a random state
        return null;
    }

    @Override
    public Belief InitialBelief(State start, String type) {
        //TODO: Implement AjanAgent::InitialBelief function to call JNI
        /*
         * Update the particles with rob and opp particle weight and create a particle belief with it.
         */
        return null;
    }

    @Override
    public double GetMaxReward() {
        // TODO: Implement AjanAgent::GetMaxReward function to call JNI
        // return TAG_REWARD;
        return 0;
    }

    @Override
    public ValuedAction GetBestAction() {
        // TODO: Implement AjanAgent::GetMaxReward function to call JNI
        //return ValuedAction(0, -1);
        return null;
    }

    @Override
    public AjanParticleUpperBound CreateParticleUpperBound(String name) {
        //TODO: Implement AjanAgent::CreateParticleUpperBound function to call JNI
        /*
         * Based on the name given, initialize TrivialParticleUpperBound,MDPUpperBound or custom upperbound
         */
        return null;
    }

    @Override
    public ScenarioUpperBound CreateScenarioUpperBound(String name, String particle_bound_name) {
        //TODO: Implement AjanAgent:: function to call JNI
        /*
         * Based on the name given, initialize LookaheadUpperBound or custom upperbound.
         */
        return null;
    }

    @Override
    public ParticleLowerBound CreateParticleLowerBound(String name) {
        return null; 
    }

    @Override
    public AjanPolicy CreateScenarioLowerBound(String bound_name, String particle_bound_name) {
        //TODO: Implement AjanAgent::CreateScenarioUpperBound function to call JNI
        /*
         * Based on the name given, initialize TrivialParticleLowerBound,RandomPolicy or custom upperbound. If the same_loc_obs_ is not equal to number of cells on the floor, then use custom policy.
         * else, compute the default actions based on MDP or SP and use MMAPStatePolicy or ModeStatePolicy or MajorityActionPolicy.
         */
        return null;
    }

    @Override
    public void PrintState(State state) {
        //TODO: Implement AjanAgent::PrintState function to call JNI
    }

    @Override
    public void PrintObs(State state, long obs) {
        //TODO: Implement AjanAgent::PrintObs function to call JNI
    }

    @Override
    public void PrintAction(int action) {
        //TODO: Implement AjanAgent::PrintAction function to call JNI
    }

    @Override
    public void PrintBelief(Belief belief) {
        //TODO: Implement AjanAgent::PrintBelief function to call JNI
    }

    @Override
    public int NumActiveParticles() {
        //TODO: Implement AjanAgent::NumActiveParticles function to call JNI
        return 0;
    }

    @Override
    public void clean() {
        if(agentModelPointer != 0){
            deleteAgent(agentModelPointer);
        }
    }
    native static void deleteAgent(long agentPointer);
    //endregion
}
