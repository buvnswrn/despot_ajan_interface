package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.util;

public class Random {
    public static Random RANDOM = new Random(0);
    static java.util.Random random;
    int RAND_MAX = 2147483647;
    long seed_;
    Random() {
        seed_=0;
        random = new java.util.Random(seed_);
    }

    Random(double seed){
        seed_= (long) seed;
        random = new java.util.Random(seed_);
    }

    public Random(long seed){
        seed_=seed;
        random = new java.util.Random(seed_);
    }

    long seed() {
        return seed_;
    }

    long NextUnsigned(){
        return random.nextLong();
    }

    double NextDouble(double min, double max){
        return random.nextDouble() *(max - min) + min;
    }

    public double NextDouble(){
        return random.nextDouble();
    }

    public int NextInt(int n) {
        // return (int) (n * ((double) rand_r(&seed_) / RAND_MAX));
        return random.nextInt(n);
    }

    int NextInt(int min, int max) {
        return random.nextInt() % (max - min) + min;
    }

}
