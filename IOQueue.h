#ifndef _IOQueue_h
#define _IOQueue_h
#include"Process.h"
#include"OS.h"
#include<vector>
#include<iostream>
using namespace std;

template<typename Obj>
class IOQueue{
private:
    Obj process_obj; //process
    vector<Obj> io_queue; //this vector stores the file name and file size
    int queue_number;
    
public:
    IOQueue(int number): queue_number(number) {}
    
    int getNum(){
        return queue_number;
    }
    
    bool isEmpty(){
        if(io_queue.size() == 0)
            return true;
        else
            return false;
    }
    
    void insert(Obj process_obj){
        io_queue.push_back(process_obj); //inserts process to back of queue
    }
    
    Obj remove(){
        Obj temporary = io_queue[0];  //removes from the front
	
	if(io_queue.size() == 1){
		io_queue.pop_back();
	}else{
        for(int i = 0; i < io_queue.size(); ++i){
            for(int j = i + 1; j < io_queue.size(); ++j){
                io_queue[i] = io_queue[j];
            	if(j == io_queue.size()-1){
               	io_queue.pop_back();
                }
            }
        }
	}
        
        return temporary;
    }
    
    void print(){
        if(io_queue.size() == 0){
            cout <<"The queue is empty" << endl;
        }else{
            for(int i = 0; i < io_queue.size(); ++i){
                cout << i << ": " <<"This is the PID #: " << io_queue[i].getProcessID() << endl;
                cout << i << ": " <<"This is the file name: " << io_queue[i].getName() <<  endl;
                cout << i << ": " <<"This is the file size: " << io_queue[i].getSize() <<  endl;
            }
        }
    }
};

#endif
