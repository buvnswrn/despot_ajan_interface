package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.DESPOT.core;

import java.lang.ref.Cleaner;
import java.util.ArrayList;
import java.util.Vector;

public class History implements Cleaner.Cleanable {
    // One possibility is to just maintain the history address and then get the values using the methods
    public long historyPointer;
    private static final Cleaner cleaner = Cleaner.create();

    public History(long historyPointer){
        this.historyPointer = historyPointer;
        cleaner.register(this, ()->History.deleteHistory(historyPointer));
    }

    void Add(int action, long obs){
        Add_(historyPointer, action, obs);
    }

    void RemoveLast() {
        RemoveLast_(historyPointer);
    }
    int Action(int t) {
        return Action_(historyPointer, t);
    }
    long Observation(int t) {
        return Observation_(historyPointer, t);
    }
    int Size() {
        return Size_(historyPointer);
    }
    void Truncate(int d) {
        Truncate_(historyPointer, d);
    }
    int LastAction() {
        return LastAction_(historyPointer);
    }
    long LastObservation() {
        return LastObservation_(historyPointer);
    }
    History Suffix(int s) {
        return Suffix_(historyPointer, s);
    }

//    @Override
//    protected void finalize() throws Throwable {
//        try {
//            deleteHistory(historyPointer); // Warn: Memory related problems can occur here if the method is not executed
//        } finally {
//            super.finalize();
//        }
//    }

    native void Add_(long historyPointer, int action, long obs);
    native void RemoveLast_(long pointer);
    native int Action_(long pointer,int t);
    native long Observation_(long pointer,int t);
    native int Size_(long pointer);
    native void Truncate_(long pointer,int d);
    native int LastAction_(long pointer);
    native long LastObservation_(long pointer);
    native History Suffix_(long pointer,int s);
    native static void deleteHistory(long historyPtr);

    @Override
    public void clean() {
//            deleteHistory(historyPointer); // Warn: Memory related problems can occur here if the method is not executed
    }

}
