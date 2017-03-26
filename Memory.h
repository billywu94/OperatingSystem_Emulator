#ifndef _Memory_h
#define _Memory_h
#include<iostream>
#include<list>
#include"Process.h"
using namespace std;

template<typename Obj>
class Memory{
private:
    list<Obj> memory_container;
    Obj process_obj;
    unsigned int difference;
public:
    
    Memory(): difference(0) {}
    Memory(unsigned int size){
        Obj start(-1,0,0); //dummy process object
        Obj end(-1,0,size); //dummy process object
        memory_container.push_front(start);
        memory_container.push_back(end);
        difference = memory_container.back().getMem() - memory_container.front().getMem();
        memory_container.back().setSpace(difference); //initialize the amount of space available in memory
        unsigned int available_space = 0;
        memory_container.front().setSpace(available_space); //initialize available space remaining
    }
    
    unsigned int getSize(){
        return memory_container.size();
    }
    
    //this function acts as worst fit approach, looks for the place in memory that has the largest hole
    unsigned int searchForLargestSpace(){
        typename std::list<Obj>::iterator it;
        difference = memory_container.front().getSpace();
        for(it = memory_container.begin(); it != memory_container.end(); ++it){
            if((*it).getSpace() > difference){
                difference = (*it).getSpace();
            }
         }
        return difference;
    }
    
    void insert(Obj &process_obj){
        unsigned int available_space = 0;
        unsigned int temp = searchForLargestSpace(); //before insertion look for the place in memory that has the most space available
        typename std::list<Obj>::iterator it;
        it = memory_container.begin();

        if(memory_container.size() == 2 && (process_obj.getMem() <= temp)){ //base case
            process_obj.setSpace(available_space);
            memory_container.insert(++it,process_obj); //insert process between front and back of list
            difference = memory_container.back().getMem() - process_obj.getMem();
            memory_container.back().setSpace(difference);
        }
        else if(memory_container.size() > 2 && (process_obj.getMem() <= temp)){
            for(it = memory_container.begin(); it != memory_container.end(); ++it){
                if((*it).getSpace() == temp){
                    process_obj.setSpace(available_space); //initialize available space remaining
                    memory_container.insert(it,process_obj);
                    difference = (*it).getSpace() - process_obj.getMem();
                    (*it).setSpace(difference);
                }
            }
        }
        else{
            cout <<"Not enough memory for process" << endl;
            cout <<"this is the largest amount we have: " << temp << endl;
            cout <<"this is how much mem process needs: " << process_obj.getMem() << endl;
        }
    }
    
    void remove(Obj process_obj){
        unsigned int temporary = 0;
        typename std::list<Obj>::iterator itr;
        for(itr = memory_container.begin(); itr != memory_container.end(); ++itr){
            if(((*itr).getPriority() == process_obj.getPriority()) && ((*itr).getProcessID() == process_obj.getProcessID()) && ((*itr).getMem() == process_obj.getMem())){
                temporary = (*itr).getMem() + (*itr).getSpace() + (*++itr).getSpace();
                itr = --itr;
                itr = memory_container.erase(itr);
                (*itr).setSpace(temporary);
            }
        }
    }
    
    void print(){
        unsigned int sum = 0;
        typename std::list<Obj>::iterator it, it1;
        if(memory_container.size() == 2){
            cout <<"There are currently no processes in the memory " << endl;
        }else{
            for(it = it1 = memory_container.begin(); it != memory_container.end(); ++it){
                sum = sum + (*it1).getMem() + (*it1).getSpace();
                if((*it).getProcessID() != -1){ //Prints out everything in the memory container except for the 2 dummy process objects
                    cout<<"The process with ID # " << (*it).getProcessID() << " with a priority of " << (*it).getPriority() << " is located between: " << sum + (*it).getSpace() << " and " <<(*it).getSpace()-1 + sum + (*it).getMem()<< " in memory" << endl;
                    ++it1;
                }
            }
        }
    }
};

#endif