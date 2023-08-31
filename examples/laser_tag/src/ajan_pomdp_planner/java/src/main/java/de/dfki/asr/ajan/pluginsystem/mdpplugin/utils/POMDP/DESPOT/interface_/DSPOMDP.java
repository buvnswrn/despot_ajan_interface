package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_;

public interface DSPOMDP {
    /**
     * [Essential]
     * Deterministic simulate model for POMDP.
     * Returns whether the terminal state has been reached
     * @param state      Current state of the world in a scenario
     * @param random_num Random number in a scenario
     * @param action     Action to be taken
     * @param reward     Reward received after taking action from state
     * @param obs        Observation received after taking action
     */
    boolean Step(State state, double random_num, int action, double reward, long obs);

    /**
     * [Optional]
     * Override this to get speedup for LookaheadUpperBound. No observation generated.
     * Returns whether the terminal state has been reached
     * @param state      Current state of the world in a scenario
     * @param random_num Random number in a scenario
     * @param action     Action to be taken
     * @param reward     Reward received after taking action from state
     */
    boolean Step(State state, double random_num, int action, double reward);

    /**
     * [Optional]
     * Simulate model for POMCP. No random number required.
     * Returns whether the terminal state has been reached
     * @param state      Current state of the world in a scenario
     * @param action     Action to be taken
     * @param reward     Reward received after taking action from state
     * @param obs        Observation received after taking action
     */
    boolean Step(State state, int action, double reward,long obs);

    int NumActions();

    /* ========================================================================
     * Reward
     * ========================================================================*/
    /**
     * [Optional]
     * Returns the reward for taking an action at a state ( to help evaluate the planning process)
     * @param state  Current state of the world
     * @param action Action to be taken
     */
     double Reward( State state, int action) ;

    /* ========================================================================
     * Functions related to beliefs and starting states.
     * ========================================================================*/
    /**
     * [Essential]
     * Returns the observation probability.
     * @param obs    Observation candidate
     * @param state  Current state of the world
     * @param action Action that has been taken
     */
     double ObsProb(long obs,  State state,
                           int action)  ;

    /**
     * [Optional]
     * Returns a starting state of simulation.
     * Used to generate states in the initial belief or the true starting state of a POMDP-based world
     */
     State CreateStartState(String type ) ;

    /**
     * [Essential]
     * Returns the initial belief.
     * @param start The start state of the world
     * @param type  Type of the initial belief
     */
     Belief InitialBelief( State start,
                                  String type )  ;

    /* ========================================================================
     * Bound-related functions.
     * ========================================================================*/
    /**
     * [Essential]
     * Returns the maximum reward.
     */
     double GetMaxReward()  ;

    /**
     * [Essential]
     * Returns (a, v), where 'a' is an action with the largest minimum reward when it is
     * executed, and v is its minimum reward, that is, a = \max_{a'} \min_{s}
     * R(a', s), and v = \min_{s} R(a, s).
     */
     ValuedAction GetBestAction()  ;

    /**
     * [Optional]
     * Override to create custom ParticleUpperBounds for solvers
     * @param name Name of the particle upper bound to be used
     */
     ParticleUpperBound CreateParticleUpperBound(String name , long cppReference) ;

    /**
     * [Optional]
     * Override to create custom ScenarioUpperBounds for solvers
     * @param name 				  Name of the upper bound to be used
     * @param particle_bound_name Name of the ParticleUpperBound to be used as the base of ScenarioUpperBound
     */
     ScenarioUpperBound CreateScenarioUpperBound(String name ,
                                                         String particle_bound_name ) ;

    /**
     * [Optional]
     * Override to create custom ParticleLowerBounds for solvers
     * @param name Name of the particle lower bound to be used
     */
     ParticleLowerBound CreateParticleLowerBound(String name ) ;

    /**
     * [Optional]
     * Override to create custom ScenarioLowerBounds for solvers
     * @param bound_name 				  Name of the lower bound to be used
     * @param particle_bound_name Name of the ParticleLowerBound to be used as the base of ScenarioLowerBound
     */
     ScenarioLowerBound CreateScenarioLowerBound(String bound_name ,
                                                         String particle_bound_name,
                                                 long cppReference) ;

//    /**
//     * [Optional]
//     * Override to create custom priors for the POMCP solver
//     * @param name - Name of the prior to be used
//     */
//     POMCPPrior CreatePOMCPPrior(String name ) ;

    /* ========================================================================
     * Display
     * ========================================================================*/
    /**
     * [Essential]
     * Prints a state.
     * @param state The state to be printed
//     * @param out   The destination stream
     */
     void PrintState( State state)  ;

    /**
     * [Essential]
     * Prints an observation.
     * @param state The current state
     * @param obs   The observation to be printed
//     * @param out   The destination stream
     */
     void PrintObs( State state, long obs)  ;

    /**
     * [Essential]
     * Prints an action.
     * @param action The action to be printed
//     * @param out    The destination stream
     */
     void PrintAction(int action)  ;

    /**
     * [Essential]
     * Prints a belief.
     * @param belief The belief to be printed
//     * @param out    The destination stream
     */
     void PrintBelief( Belief belief)  ;

    /**
     * [Essential]
     * Returns number of allocated particles (sampled states).
     */
     int NumActiveParticles()  ;

    /**
     * [Optional]
     * Returns a copy of this POMDP model.
     */
    default DSPOMDP MakeCopy()  {
        return null;
    }
    

}
