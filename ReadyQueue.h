#ifndef _ReadyQueue_h
#define _ReadyQueue_h
#include <vector>
#include <iostream>
#include "Process.h"
using namespace std;

template<typename Obj>
class ReadyQueue: public process{
private:
    vector<Obj> readyQ_;
    Obj process_object;
    int min_value;
public:
    ReadyQueue(): min_value(0) {}
    
    void insert(Obj process_object){ //note: to implement using a more efficient method, sort by priority value
        readyQ_.push_back(process_object);
    }
    
    bool isEmpty(){
        if(readyQ_.empty() == true)
            return true;
    }
    
    int getMin(){
        return min_value;
    }
    
    //searches for the process with the highest priority and returns that process to be inserted into the cpu
    Obj insertCPU(){
        min_value = readyQ_.front().getPriority();
        for(int i = 1; i < readyQ_.size(); ++i){
            if(readyQ_[i].getPriority() < min_value){
                min_value = readyQ_[i].getPriority();
            }
        }
        for(int j = 0; j < readyQ_.size(); ++j){
            if(readyQ_[j].getPriority() == min_value)
                return readyQ_[j];
        }
    }
    
    //removes the process with the highest priority out of the ready queue
    void remove(){
        if(readyQ_.size() == 1){ //if there is only 1 process in the ready queue, remove it
            readyQ_.pop_back();
        }else{
            for(int i = 0; i < readyQ_.size(); ++i){
                if(readyQ_[i].getPriority() == min_value){
                    for(int j = i+1; j < readyQ_.size(); ++j){
                        readyQ_[i] = readyQ_[j];
                        if(j == readyQ_.size()-1) readyQ_.pop_back();
                    }
                }else if (readyQ_.back().getPriority() == min_value){ //if the process with the highest priority is in the back of the queue remove it from the back
                    readyQ_.pop_back();
                }
            }
        }
        min_value = readyQ_.front().getPriority(); //reset min value
    }
    
    void print(){
        if(readyQ_.size() == 0){
            cout << "The ready queue is empty" <<endl;
        }
        for(int i = 0; i < readyQ_.size(); ++i){
            cout<<i <<": " <<"This is the process ID: " << readyQ_[i].getProcessID() << endl;
            cout<<i <<": " <<"This is the priority: " << readyQ_[i].getProcessID() << endl;

        }
    }
    
    int getSize(){
        return readyQ_.size();
    }
    
    
};

#endif
