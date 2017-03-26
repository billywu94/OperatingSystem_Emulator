#ifndef ____process__
#define ____process__
#include <iostream>
#include <string>
using namespace std;

class process{
private:
    int process_id; //PID
    int priority; //process Priority
    int file_size; //size of file
    string file_name; //name of file
    int memory_amount; //amount of memory process needs
    unsigned int free_space; //this variable keeps track of the amount of free space that is available in memory
    
public:
    process(): process_id(0), priority(0), file_size(0), memory_amount(0), free_space(0) {}
    
    process(int pid, int priority_value, int mem): process_id(pid), priority(priority_value), memory_amount(mem) {}
    
    int getProcessID(){
        return process_id;
    }
    
    int getPriority(){
        return priority;
    }
    
    int getSize(){
        return file_size;
    }
    
    string getName(){
        return file_name;
    }
    
    int getMem(){
        return memory_amount;
    }
    
    int getSpace(){
        return free_space;
    }
    
    void setSize(int &size){
        file_size = size;
    }
    
    void setName(string &name){
        file_name = name;
    }
    
    void setSpace(unsigned int &available){
        free_space = available;
    }
    
};

#endif