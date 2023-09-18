package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.example;

import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core.Globals;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.implementation.*;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.State;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.interface_.ValuedAction;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Compass;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Coord;
import de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Floor;

import java.util.*;

import static de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.Connector.ROSConnector.*;
import static de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.Ajan_Util_Helper.gausscdf;
import static de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.DespotPomdpGlobals.MDP_;
import static de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util.DespotPomdpGlobals.SP;
import static java.lang.Double.min;
import static java.lang.Math.sqrt;

@SuppressWarnings("ALL")
public class LaserTag extends AjanAgent {
    Vector<Double> probs;
    Vector<Double> opp_probs;
    Vector<Double> rob_probs;

    //region Problem-Specific
    int NBEAMS = 8;
    int BITS_PER_READING = 7;
    double TAG_REWARD = 10;
    final long ONE = 1;

    double noise_sigma_;
    double unit_size_;

    LaserTag current_;
    boolean robot_pos_unknown_;
    Vector<LaserTagState> states_;
    Floor floor_;
    Vector<Integer> opp_;
    Vector<Integer> rob_;

    Vector<Vector<Vector<State>>> transition_probabilities_;
    Vector<Vector<Vector<Double>>> reading_distributions_;
    Vector<Integer> default_action_;
    long same_loc_obs_;

    LaserTag() {
        noise_sigma_ = 0.5;
        unit_size_ = 1.0;
        current_ = this;
        robot_pos_unknown_ = false;
        transition_probabilities_ = new Vector<Vector<Vector<State>>>();
        reading_distributions_ = new Vector<>();
        states_ = new Vector<>();
        rob_ = new Vector<>();
        opp_ = new Vector<>();
        Init(BenchmarkMap());
        probs = new Vector<>(NumStates());
        for (int i = 0; i < NumStates(); i++) {
            probs.add(0.0);
        }
        opp_probs = new Vector<>(floor_.NumCells());
        for (int i = 0; i < NumStates(); i++) {
            opp_probs.add(0.0);
        }
        rob_probs = new Vector<>(floor_.NumCells());
        for (int i = 0; i < NumStates(); i++) {
            rob_probs.add(0.0);
        }
        default_action_ = new Vector<>();
    }

    void Init(String iss) {
        System.out.println(iss);
        ReadConfig(new Scanner(iss));
        LaserTagState state;
        states_.ensureCapacity(NumStates());
        rob_.ensureCapacity(NumStates());
        opp_.ensureCapacity(NumStates());
        for (int rob = 0; rob < floor_.NumCells(); rob++) {
            for (int opp = 0; opp < floor_.NumCells(); opp++) {
                int s = RobOppIndicesToStateIndex(rob, opp);
                state = new LaserTagState(s);
                states_.add(s,state);
                rob_.add(s, rob);
                opp_.add(s, opp);
            }
        }
        transition_probabilities_.ensureCapacity(NumStates());
        for (int s = 0; s < NumStates(); s++) {
            transition_probabilities_.add(s,new Vector<>());
            transition_probabilities_.get(s).ensureCapacity(NumActions());

            HashMap<Integer, Double> opp_distribution = OppTransitionDistribution(s);
            for (int a = 0; a < NumActions(); a++) {
                    transition_probabilities_.get(s).add(a, new Vector<>());

                int next_rob = NextRobPosition(rob_.get(s), opp_.get(s), a);

                if(!(a == TagAction() && Coord.ManhattanDistance(floor_.GetCell(rob_.get(s)),floor_.GetCell(opp_.get(s)))<=1)) {
                    for(Map.Entry<Integer, Double> entry : opp_distribution.entrySet()) {
                        int key = entry.getKey();
                        double value = entry.getValue();
                        State next = new LaserTagState(RobOppIndicesToStateIndex(next_rob, key),value);
                        transition_probabilities_.get(s).get(a).add(next);
                    }
                }
            }
        }

        for (int i = 0; i < NBEAMS; i++) {
            same_loc_obs_ = SetReading_(same_loc_obs_, 101, i);
        }

        reading_distributions_.ensureCapacity(NumStates());


        for (int s = 0; s < NumStates(); s++) {
            reading_distributions_.add(s, new Vector<>());
            reading_distributions_.get(s).ensureCapacity(NBEAMS);

            for (int d = 0; d < NBEAMS; d++) {
                double dist = LaserRange(states_.get(s), d);
                for (int reading = 0; reading < dist / unit_size_; reading++) {
                    double min_noise = reading * unit_size_ - dist;
                    double max_noise = min(dist, (reading + 1) * unit_size_) - dist;

                    double prob =
                            2
                            * (gausscdf(max_noise, 0, noise_sigma_)
                            - (reading > 0 ?
                                    gausscdf(min_noise, 0, noise_sigma_) : 0));
                    if(reading_distributions_.get(s).size() <= d) {
                        reading_distributions_.get(s).add(d, new Vector<>());
                    }
                    reading_distributions_.get(s).get(d).add(prob);
                }
            }
        }
    }

    double LaserRange(State state, int dir) {
        Coord rob = floor_.GetCell(rob_.get(state.state_id)), opp = floor_.GetCell(
                opp_.get(state.state_id));
        int d = 1;
        while (true) {
            Coord coord = Coord.Muliply(Coord.Add(rob,Compass.DIRECTIONS[dir]), d);
            if (floor_.GetIndex(coord) == -1 || coord == opp)
                break;
            d++;
        }
        int x = Compass.DIRECTIONS[dir].x, y = Compass.DIRECTIONS[dir].y;

        return d * sqrt(x * x + y * y);
    }

    private String BenchmarkMap() {
        int height = 7;
        int width = 11;
        int obstacles = 8;

        StringBuilder map = new StringBuilder(new String(new char[height * (width + 1) -1]).replace('\0','.'));
        map.setLength(height * (width + 1) -1);

        for (int h = 1; h < height; h++) {
            map.setCharAt(h * (width +1) -1, '\n');
        }

        int[] obstaclesList  = {1+2*(width+1), 3+4*(width+1), 3+0*(width+1), 5+0*(width+1), 6+4*(width+1), 9+4*(width+1), 9+1*(width+1), 10+6*(width+1)};
        for (int i = 0; i < obstacles; i++) {
            int p = obstaclesList[i];
            assert (map.charAt(p) != '\n' && map.charAt(p) != '#');
            map.setCharAt(p,'#');
        }
        return "mapSize = " + height + " " + width + "\n" + map;
    }

    private String RandomMap(int height, int width, int obstacles) {
        StringBuilder map = new StringBuilder(new String(new char[height*(width +1) -1]).replace('\0','.'));
//        map.append('.');
        for (int h = 1; h < height; h++)
            map.setCharAt(h * (width +1) -1, '\n');

        for (int i = 0; i < obstacles;) {
            Random random = new Random();
            int p = random.nextInt(map.length());
            if (map.charAt(p) != '\n' && map.charAt(p) != '#') {
                map.setCharAt(p, '#');
                i++;
            }
        }
        return "mapSize = " + height + " " + width+ "\n" + map;
    }
    int RobOppIndicesToStateIndex(int rob, int opp) {
        return rob * floor_.NumCells() + opp;
    }

    HashMap<Integer, Double> OppTransitionDistribution(int state) {
        Coord rob = floor_.GetCell(rob_.get(state)), opp = floor_.GetCell(opp_.get(state));
        double temp;
        HashMap<Integer, Double> distribution = new HashMap<>();

        if (opp.x == rob.x) {
            int index =
                    floor_.Inside(Coord.Add(opp,new Coord(1, 0))) ?
                            floor_.GetIndex(Coord.Add(opp , new Coord(1, 0))) : floor_.GetIndex(opp);
            temp = distribution.get(index)!=null?distribution.get(index):0;
            distribution.put(index, temp + 0.2);

            index =
                    floor_.Inside(Coord.Add(opp , new Coord(-1, 0))) ?
                            floor_.GetIndex(Coord.Add(opp , new Coord(-1, 0))) : floor_.GetIndex(opp);
            temp = distribution.get(index)!=null?distribution.get(index):0;
            distribution.put(index, temp + 0.2);
        } else {
            int dx = opp.x > rob.x ? 1 : -1;
            int index =
                    floor_.Inside(Coord.Add(opp , new Coord(dx, 0))) ?
                            floor_.GetIndex(Coord.Add(opp , new Coord(dx, 0))) : floor_.GetIndex(opp);
            temp = distribution.get(index)!=null?distribution.get(index):0;
            distribution.put(index, temp + 0.4);
        }

        if (opp.y == rob.y) {
            int index =
                    floor_.Inside(Coord.Add(opp , new Coord(0, 1))) ?
                            floor_.GetIndex(Coord.Add(opp , new Coord(0, 1))) : floor_.GetIndex(opp);
            temp = distribution.get(index)!=null?distribution.get(index):0;
            distribution.put(index, temp + 0.2);

            index =
                    floor_.Inside(Coord.Add(opp , new Coord(0, -1))) ?
                            floor_.GetIndex(Coord.Add(opp , new Coord(0, -1))) : floor_.GetIndex(opp);
            temp = distribution.get(index)!=null?distribution.get(index):0;
            distribution.put(index, temp + 0.2);
        } else {
            int dy = opp.y > rob.y ? 1 : -1;
            int index =
                    floor_.Inside(Coord.Add(opp , new Coord(0, dy))) ?
                            floor_.GetIndex(Coord.Add(opp , new Coord(0, dy))) : floor_.GetIndex(opp);
            temp = distribution.get(index)!=null?distribution.get(index):0;
            distribution.put(index, temp + 0.4);
        }
        int i = floor_.GetIndex(opp);
        temp = distribution.get(i)!=null?distribution.get(i):0;
        distribution.put(i, temp + 0.2);
        return distribution;
    }
    private int NextRobPosition(int rob, int opp, int a) {
        Coord pos = Coord.Add(floor_.GetCell(rob) , Compass.DIRECTIONS[a]);
        if(a != TagAction() && (floor_.Inside(pos) && pos != (floor_.GetCell(opp))))
            return floor_.GetIndex(pos);
        return rob;
    }
    private void ReadConfig(Scanner iss) {

        while(iss.hasNext()) {
            String key = iss.next();
            String val = iss.next();
            if(key.equals("mapSize")) {
                int nrows = iss.nextInt();
                int ncols = iss.nextInt();
                floor_ = new Floor(nrows, ncols);
                for (int y = 0; y < nrows; y++) {
                    String line = iss.next();
                    for (int x = 0; x < ncols; x++) {
                        if(line.charAt(x) !='#') {
                            floor_.AddCell(x, y);
                        }
                    }
                }
                floor_.ComputeDistances();
            } else if (key.equals("width-height-obstacles")){
                int h = iss.nextInt();
                int w = iss.nextInt();
                int o = iss.nextInt();
                Scanner randomMapScanner = new Scanner(RandomMap(h, w, o));
                ReadConfig(randomMapScanner);
            } else {
                System.out.println("Map not perfect");
            }
        }
    }
    int TagAction() {
        return 4;
    }

    // endregion

    //region MDP Functions
    @Override
    public int NumStates() {
        return floor_.NumCells() * floor_.NumCells();
    }

    @Override
    public int NumActions() {
        return 5;
    }

    @Override
    public Vector<State> TransitionProbability(int s, int a) {
        return transition_probabilities_.get(s).get(a);
    }

    @Override
    public double Reward(int s, int a) {
        final LaserTagState state = states_.get(s);
        double reward = 0;
        if (a == TagAction()) {
            if (rob_.get(state.state_id) == opp_.get(state.state_id)) {
                reward = TAG_REWARD;
            } else {
                reward = -TAG_REWARD;
            }
        } else {
            reward = -1;
        }
        return reward;
    }
    //endregion

    //region BeliefMDP
    @Override
    public AjanBelief Tau(AjanBelief belief, int action, long obs) {
          Vector<State> particles  = belief.particles();
          double sum = 0;
        for (int i = 0; i < particles.size(); i++) {
            LaserTagState state = (LaserTagState) particles.get(i);
            Vector<State> distribution = transition_probabilities_.get(GetIndex(state)).get(action);

            for (int j = 0; j < distribution.size(); j++) {
                State next = distribution.get(j);
                double p = state.weight * next.weight;
                p*= ObsProb(obs, states_.get(next.state_id), action);
                double temp = probs.get(next.state_id)!=null?probs.get(next.state_id):0;
                probs.add(next.state_id, temp+p);
                sum += p;
            }
        }

        Vector<State> new_particles = new Vector<>(NumStates());
        for (int i = 0; i < NumStates(); i++) {
            if (probs.get(i) > 0) {
                State new_particle = states_.get(i); // TODO: have to do copy in cpp end
                new_particle.weight = probs.get(i)/sum;
                new_particles.add(new_particle);
                probs.set(i,0.0);
            }
        }
        return new AjanBelief(new_particles,this,null);
    }

    @Override
    public void Observe(AjanBelief belief, int action, HashMap<Long, Double> obs) {
        System.out.println("Exit: Too many observations!");
    }

    @Override
    public double StepReward(AjanBelief belief, int action) {
        Vector<State> particles = belief.particles();
        double sum = 0;

        for (int i = 0; i < particles.size(); i++) {
            State particle = particles.get(i);
            LaserTagState state = (LaserTagState) particle;
            double reward = 0;
            if (action == TagAction()) {
                if (Objects.equals(rob_.get(state.state_id), opp_.get(state.state_id))) {
                    reward = TAG_REWARD;
                } else {
                    reward = -TAG_REWARD;
                }
            } else {
                reward = -1;
            }
            sum += state.weight * reward;
        }
        return sum;
    }
    //endregion

    //region StateIndexer
    @Override
    public int GetIndex(State state) {
        return state.state_id;
    }
    @Override
    public State GetState(int index) {
        return states_.get(index);
    }
    //endregion

    //region StatePolicy
    @Override
    public int GetAction(State state) {
         return default_action_.get(GetIndex(state));
    }
    //endregion

    //region MMAPInferencer

    @Override
    public State GetMMAP(Vector<State> particles) {
        Coord rob = MostLikelyRobPosition(particles);
        Coord opp = MostLikelyOpponentPosition(particles);
        int state_id = RobOppIndicesToStateIndex(floor_.GetIndex(rob), floor_.GetIndex(opp));
        return states_.get(state_id);
    }
    //endregion

    //region POMDP
    @Override
    public boolean Step(State state, double random_num, int action, double reward_p, long obs_p) {
        currentObservation = obs_p;
        currentReward = reward_p;
        currentAction = action;
        currentState = (LaserTagState) state;
        Random random = new Random((long) random_num);
        boolean terminal = Step(state, random.nextDouble(), action, currentReward);

        if(terminal) {
            currentObservation = same_loc_obs_;
        } else {
            if(Objects.equals(rob_.get(state.state_id), opp_.get(state.state_id))) {
                currentObservation = same_loc_obs_;
            } else {
                Vector<Vector<Double>> distribution = reading_distributions_.get(state.state_id);
                currentObservation = 0;
                for (int dir = 0; dir<NBEAMS; dir++) {
                    double mass = random.nextDouble();
                    int reading = 0;
                    for(; reading<distribution.get(dir).size(); reading++) {
                        mass -= distribution.get(dir).get(reading);
                        if(mass < Globals.TINY)
                            break;
                    }
                    currentObservation = SetReading_(currentObservation, reading, dir);
                }
            }
        }
        return terminal; // TODO: Fetch the current state variables on the cpp end
    }

    @Override
    public boolean Step(State state, double random_num, int action, double reward) {
        currentReward = reward;
        currentAction = action;
        currentState = (AjanAgentState) state;

        Random random = new Random((long) random_num);
        random_num = random.nextDouble();

        LaserTagState state1 = (LaserTagState) state;

        boolean terminal = false;

        if(action == TagAction()) {
            double distance = Coord.ManhattanDistance(floor_.GetCell(rob_.get(state1.state_id)), floor_.GetCell(opp_.get(state1.state_id)));
            if (distance<=1) {
                currentReward = TAG_REWARD;
                terminal = true;
            } else {
                currentReward = -TAG_REWARD;
            }
        } else {
            currentReward = -1;
        }
        Vector<State> distribution = transition_probabilities_.get(state.state_id).get(action);
        double sum = 0;
        for (int i = 0; i < distribution.size(); i++) {
            State next = distribution.get(i);
            sum += next.weight;
            if (sum >= random_num) {
                state.state_id = next.state_id;
                break;
            }
        }
        return terminal;
    }

    @Override
    public double ObsProb(long obs, State state, int action) {

        if (Objects.equals(rob_.get(state.state_id), opp_.get(state.state_id)))
            return obs == same_loc_obs_?1:0;

        double prod = 1.0;
        for (int dir = 0; dir < NBEAMS; dir++) {
            int reading = GetReading_(obs, dir);
            if (reading >= LaserRange(state, dir) / unit_size_)
                return 0;
            double prob_mass = reading_distributions_.get(state.state_id).get(dir).get(reading);
            prod *= prob_mass;
        }
        return prod;
    }

    @Override
    public State CreateStartState(String type) {
        Random random = new Random();
        int n = random.nextInt(states_.size());
        return states_.get(n);
    }

    @Override
    public AjanBelief InitialBelief(State start, String type) {
        Vector<State> particles =  new Vector<>();
        int N = floor_.NumCells();
        double wgt = 1.0 / N / N;
        for (int rob = 0; rob < N; rob++) {
            for (int opp = 0; opp < N; opp++) {
                LaserTagState state = new LaserTagState(RobOppIndicesToStateIndex(rob, opp),wgt);
                particles.add(state);
            }
        }
        return new AjanBelief(particles, this, null);
    }

    @Override
    public double GetMaxReward() {
        return TAG_REWARD;
    }

    @Override
    public ValuedAction GetBestAction() {
        return new ValuedAction(0, -1);
    }

    @Override
    public TagSHRPolicy CreateScenarioLowerBound(String bound_name, String particle_bound_name, long cppReference) {
        //TODO: Implement AjanAgent::CreateScenarioUpperBound function to call JNI
        /*
         * Based on the name given, initialize TrivialParticleLowerBound,RandomPolicy or custom upperbound. If the same_loc_obs_ is not equal to number of cells on the floor, then use custom policy.
         * else, compute the default actions based on MDP or SP and use MMAPStatePolicy or ModeStatePolicy or MajorityActionPolicy.
         */
        return new TagSHRPolicy(cppReference);
    }

    @Override
    public TagSPParticleUpperBound CreateParticleUpperBound(String name, long cppReference ) {
        //TODO: Implement AjanAgent::CreateParticleUpperBound function to call JNI
        /*
         * Based on the name given, initialize TrivialParticleUpperBound,MDPUpperBound or custom upperbound
         */
        return new TagSPParticleUpperBound(this, cppReference);
    }

    public String Test(String bound_name, String particle_bound_name,long cppAddress){
        System.out.println("Test called"+bound_name+" "+particle_bound_name+" "+cppAddress);
        return "retrunedValue";
    }
    @Override
    public void PrintState(State s) {
        LaserTagState state = (LaserTagState) s;

        int aindex = rob_.get(state.state_id);
        int oindex = opp_.get(state.state_id);

        for (int y = floor_.num_rows()-1; y >= 0; y--) {
            for (int x = 0; x < floor_.num_cols(); x++) {
                int index = floor_.GetIndex(new Coord(x, y));
                if (index == Floor.INVALID)
                    System.out.print("#");
                else if (index == aindex && index == oindex)
                    System.out.print("Q");
                else if (index == aindex)
                    System.out.print("R");
                else if (index == oindex)
                    System.out.print("O");
                else
                    System.out.print(".");
            }
            System.out.println();
        }
    }

    @Override
    public void PrintObs(State state, long obs) {
        for (int i = 0; i < NBEAMS; i++)
            System.out.print(GetReading_(obs, i)+ " ");
        System.out.println();
    }

    @Override
    public void PrintAction(int action) {
        switch(action) {
            case 0: System.out.print("North"); break;
            case 1: System.out.println("East"); break;
            case 2: System.out.println("South"); break;
            case 3: System.out.println("West"); break;
            case 4: System.out.println("Tag"); break;
            default: System.out.println("Wrong action");
        }
    }

    @Override
    public void PrintBelief(AjanBelief belief) {

        System.err.println("PrintBelief Not Implemented");
//                Vector<State> particles =belief.particles();
//
//        int max_prob_id=-1;
//        double max_prob=0;
//        float rob_pos_map[11][7];
//        float opp_pos_map[11][7];
//        for(int i=0;i<11;i++)
//            for(int j=0;j<7;j++)
//            {
//                rob_pos_map[i][j]=0;
//                opp_pos_map[i][j]=0;
//            }
//        for (int i = 0; i < particles.size(); i++) {
//            State particle = particles.get(i);
//            if(particle.weight > max_prob){
//                max_prob = particle.weight;
//                max_prob_id = i;
//            }
//            int rob= rob_.get(particle.state_id);
//            int opp= opp_.get(particle.state_id);
//            Coord rob_pos=floor_.GetCell(rob);
//            Coord opp_pos=floor_.GetCell(opp);
//            rob_pos_map[rob_pos.x][rob_pos.y]+=particle.weight;
//            opp_pos_map[opp_pos.x][opp_pos.y]+=particle.weight;
//        }
//
//        int rob= rob_.get(particles.get(max_prob_id).state_id);
//        int opp= opp_.get(particles.get(max_prob_id).state_id);
//        System.out.print("Maximum likelihood robot position:");
//        System.out.println(floor_.GetCell(rob));
//
//        System.out.print("Maximum likelihood target position:");
//        System.out.println(floor_.GetCell(opp));
//
//        System.out.println("Robot position belief:");
//        for(int j=0;j<7;j++){
//            for(int i=0;i<11;i++){
//                cout.precision(3);
//                cout.width(6);
//                cout  << rob_pos_map[i][6-j] << "  ";
//            }
//           System.out.println();
//        }
//        System.out.println("Target position belief:");
//        for(int j=0;j<7;j++){
//            for(int i=0;i<11;i++){
//                cout.precision(3);
//                cout.width(6);
//                cout << opp_pos_map[i][6-j] << "  ";
//            }
//            System.out.println();
//        }
    }

    //endregion
    // region Problem-Specific
    public void ComputeDefaultActions(String type) {
        if (Objects.equals(type, MDP_)) {
            Vector<ValuedAction> policy = this.ComputeOptimalPoliciesUsingVIAndReturnPolicy(this.agentModelPointer);
            int num_states = NumStates();
            default_action_.ensureCapacity(num_states);

            for (int s = 0; s < num_states; s++) {
                default_action_.add(s, policy.get(s).action);
            }
        } else if (Objects.equals(type, SP)) {
            // Follow the shortest path from the robot to the opponent
            default_action_.ensureCapacity(NumStates());
            for (int s = 0; s < NumStates(); s++) {
                default_action_.add(s, 0);
                if (Objects.equals(rob_.get(s), opp_.get(s))) {
                    default_action_.add(s, TagAction());
                } else {
                    double cur_dist = floor_.Distance(rob_.get(s), opp_.get(s));
                    for (int a = 0; a < 4; a++) {
                        int next = NextRobPosition(rob_.get(s), opp_.get(s), a);
                        double dist = floor_.Distance(next, opp_.get(s));

                        if (dist < cur_dist) {
                            default_action_.add(s, a);
                            break;
                        }
                    }
                }
            }
        } else {
            System.err.println("Unsupported default action type "+ type );
        }
    }
    Coord MostLikelyOpponentPosition(Vector<State> particles) {
        for (int i = 0; i < particles.size(); i++) {
            LaserTagState tagstate = (LaserTagState) particles.get(i);
            double temp = opp_probs.get(opp_.get(tagstate.state_id)) !=null?opp_probs.get(opp_.get(tagstate.state_id)):0;
            opp_probs.add(opp_.get(tagstate.state_id), temp+ tagstate.weight);
        }

        double maxWeight = 0;
        int opp = -1;
        for (int i = 0; i < opp_probs.size(); i++) {
            if (opp_probs.get(i) > maxWeight) {
                maxWeight = opp_probs.get(i);
                opp = i;
            }
            opp_probs.add(i, 0.0);
        }

        return floor_.GetCell(opp);
    }

    Coord MostLikelyRobPosition(Vector<State> particles) {
        double maxWeight = 0;
        int rob = -1;
        for (int i = 0; i < particles.size(); i++) {
            LaserTagState tagstate = (LaserTagState) particles.get(i);
            int id = rob_.get(tagstate.state_id);
            double temp = rob_probs.get(id) !=null?rob_probs.get(id):0;
            rob_probs.add(id, temp + tagstate.weight);
            if (rob_probs.get(id) > maxWeight) {
                maxWeight = rob_probs.get(id);
                rob = id;
            }
        }

        for (int i = 0; i < rob_probs.size(); i++) {
            rob_probs.add(i, 0.0);
        }
        return floor_.GetCell(rob);
    }
    //endregion

}
