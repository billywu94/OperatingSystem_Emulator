#ifndef ____OS__
#define ____OS__
#include <iostream>
#include <vector>
#include <string>
#include"Process.h"
using namespace std;
template<typename Obj>
class OS{
private:
    vector<Obj> array;
    bool flag;
public:
    OS(): flag(true){}
    
    void insert(Obj a){
        array.push_back(a);
        flag = false;
    }
    
    bool isEmpty(){
        if(flag == true)
            return true;
    }
    
    Obj getProcess(){ //returns the process from CPU
        return array[0];
    }
    
    void removeProcess(){ //removes the process from CPU
        flag = true;
        array.pop_back();
    }
    
    void setFunction(string &file_name, int &file_size){ //set file name and size
        array[0].setName(file_name);
        array[0].setSize(file_size);
    }
    
    void print(){
        
        for(int i = 0; i < array.size(); ++i){
        cout<<"This is in the cpu (pid): " << i << array[i].getProcessID() << endl;
        cout<<"This is in the cpu (priority): "<< i << array[i].getPriority() << endl;
        }
    }
    
    int getSize(){ //return size of CPU
        return array.size();
    }

};


#endif /* defined(____OS__) */
