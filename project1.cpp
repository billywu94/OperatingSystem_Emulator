#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include "OS.h"
#include "Process.h"
#include "ReadyQueue.h"
#include "IOQueue.h"
#include "Memory.h"
using namespace std;

int main(){

    int num_of_printers_, num_of_disks_;
    unsigned int memory_;
    cout << "How many printers are in the system? Please enter a integer" << endl;
    cin >> num_of_printers_;
    while(!cin){ //error handling
        cout <<"Please enter a integer" << endl;
        cin.clear();
        cin.ignore();
        cin >> num_of_printers_;
    }
    vector<IOQueue<process> > printers;
    vector<string> printer_buffer(num_of_printers_);
    vector<string> printer_complete(num_of_printers_);
    for(int i = 0; i < num_of_printers_; ++i){
        printers.push_back(IOQueue<process>(i));
    }
    //list of possible number of printers user may have
    for(int j = 0; j < printer_buffer.size(); ++j){
        string temp;
        ostringstream convert;
        convert << j+1;
        temp = convert.str();
        printer_buffer[j] = "p" + temp;
    }
    
    for(int k = 0; k < printer_complete.size(); ++k){
        string temporary;
        ostringstream convert_printer;
        convert_printer << k+1;
        temporary = convert_printer.str();
        printer_complete[k] = "P" + temporary;
    }
    
    cout << "How many disks are in the system? Please enter a integer" << endl;
    cin >> num_of_disks_;
    while(!cin){ //error handling
        cout <<"Please enter a integer" << endl;
        cin.clear();
        cin.ignore();
        cin >> num_of_disks_;
    }
    vector<IOQueue<process> > disks;
    vector<string> disk_buffer(num_of_disks_);
    vector<string> disk_complete(num_of_disks_);
    for(int l = 0; l < num_of_disks_; ++l){
        disks.push_back(IOQueue<process>(l));
    }
    //list of possible number of disks user may have
    for(int m = 0; m < disk_buffer.size(); ++m){
        string t;
        ostringstream convert;
        convert << m+1;
        t = convert.str();
        disk_buffer[m] = "d" + t;
    }
    
    for(int n = 0; n < disk_complete.size(); ++n){
        string temp;
        ostringstream convert;
        convert << n+1;
        temp = convert.str();
        disk_complete[n] = "D" + temp;
    }
    
    cout << "How much memory (bytes) is in the system? Please enter a integer" << endl;
    cin >> memory_;
    while(!cin){ //error handling
        cout <<"Please enter a integer" << endl;
        cin.clear();
        cin.ignore();
        cin >> memory_;
    }
    Memory<process> mem(memory_);
    
    OS<process> cpu;
    ReadyQueue<process> q;
    string interrupt;
    string system_call;
    string input;
    int result;
    int memory_amount;
    int priority_level;
    int id = 0;
    
    while(true){
        cout <<"Please press 'A' for a new process, press 'S' for snapshots, press 'P1' to signal completion of printer 1, press 'D1' to signal disk 1, etc. For system calls: press 't' to terminate process, 'p1' to request printer 1, 'd1' to request disk 1 etc" << endl;
        cin >> interrupt;
        if(interrupt == "A"){
            cout <<"how much memory(bytes) is required for new process?" << endl;
            cin >> memory_amount;
            while(!cin){
                cout <<"Please enter a integer" << endl;
                cin.clear();
                cin.ignore();
                cin >> memory_amount;
            }
            cout <<"what is the priority of the process? Please enter a non-negative integer." << endl;
            cin >> priority_level;
            while(!cin || priority_level < 0){
                cout <<"Not a valid level of priority. Please enter a non-negative integer" << endl;
                cin.clear();
                cin.ignore();
                cin >> priority_level;
            }
            process p(++id, priority_level, memory_amount);
            mem.insert(p);
            q.insert(p); //inserting process into ready queue
            if(cpu.isEmpty() == true){ //if the cpu is empty
                cpu.insert(q.insertCPU()); //inserting process from ready-queue into cpu
                q.remove(); //removes process from ready-queue
            }else if(q.insertCPU().getPriority() < cpu.getProcess().getPriority()){ //if there exists a process with higher priority, put that process in cpu(This is the preemptive approach)
                q.insert(cpu.getProcess());//inserts the process from cpu to the back of ready queue
                cpu.removeProcess(); //removes the process from cpu
                cpu.insert(q.insertCPU()); //inserts the process with the higher priority into the cpu
                q.remove();
            }
            
        }else if(interrupt == "S"){
            cout << "What would you like to see? Press 'r' to view ready queue, 'i' to view printer & disk info, 'm' to view current state of memory" << endl;
            cin >> system_call;
            if(system_call == "r"){
                q.print();
            }else if(system_call == "i"){
                for(int i = 0; i < num_of_printers_; ++i){
                    cout <<"This is printer queue # " << i+1 << ": ";
                    printers[i].print();
                    cout << endl;
                }
                for(int j = 0; j < num_of_disks_; ++j){
                    cout <<"This is disk queue # " << j+1 << ": ";
                    disks[j].print();
                    cout << endl;
                }

            }else if(system_call == "m"){
                mem.print();
            }else{
                while(system_call != "r" && system_call != "i" && system_call != "m"){
                    cout <<"Please enter a valid input" << endl;
                    cin >> system_call;
                }
                if(system_call == "r"){
                    q.print();
                }else if(system_call == "i"){
                    for(int i = 0; i < num_of_printers_; ++i){
                        cout <<"This is printer queue " << i+1 << ": ";
                        printers[i].print();
                        cout << endl;
                    }
                    for(int j = 0; j < num_of_disks_; ++j){
                        cout <<"This is disk queue " << j+1 <<": ";
                        disks[j].print();
                        cout << endl;
                    }
                }else if(system_call == "m"){
                    mem.print();
                }
            }
        }else if(interrupt == "t"){
            if(cpu.isEmpty() == true){
                cout <<"sorry, you cannot enter a system call while the cpu is empty" << endl;
            }else{
                mem.remove(cpu.getProcess());
                cpu.removeProcess();
                if(!q.isEmpty()){
                    cpu.insert(q.insertCPU());
                    q.remove();
                }
            }
        }
        else{
            //when making a request for printer if user input is a valid printer, request is successful and we insert process into that printer's queue
            for(int i = 0; i < num_of_printers_; ++i){
                if(interrupt == printer_buffer[i]){
                    if(cpu.isEmpty() == true){
                        cout <<"sorry, you cannot enter a system call while the cpu is empty" << endl;
                    }else{
                        cout << "You have requested printer # " << i+1 << endl;
                        cout << "What is the name of the file?" << endl;
                        cin >> input;
                        cout << "What is the size of the file?" << endl;
                        cin >> result;
                        cpu.setFunction(input,result); //sets file name and size
                        printers[i].insert(cpu.getProcess()); //insert process to printer's queue
                        cpu.removeProcess(); //removes the process from cpu
                        if(!q.isEmpty()){
                            cpu.insert(q.insertCPU()); //insert next process from ready queue into cpu
                            q.remove(); //remove the process that was just inserted in cpu
                        }
                    }
                }
            }//end for
            
            //if user input equals to any of these interrupts, signal completion of printer and return process back to ready queue
            for(int j = 0; j < num_of_printers_; ++j){
                if(interrupt == printer_complete[j]){
                    if(printers[j].isEmpty() == true){
                        cout <<"Printer is empty" << endl;
                    }else{
                        q.insert(printers[j].remove());
                        if(cpu.isEmpty() == true){
                            cpu.insert(q.insertCPU());
                            q.remove();
                        }else if(q.insertCPU().getPriority() < cpu.getProcess().getPriority()){ //if there exists a process with higher priority, put that process in cpu(This is the preemptive approach)
                            q.insert(cpu.getProcess());//inserts the process from cpu to the back of ready queue
                            cpu.removeProcess(); //removes the process from cpu
                            cpu.insert(q.insertCPU()); //inserts the process with the higher priority into the cpu
                            q.remove();
                        }
                    }
                }
            }
            //when making a request for disk if user input is a valid disk, request is successful and we insert process into that disk's queue
            for(int k = 0; k < num_of_disks_; ++k){
                if(interrupt == disk_buffer[k]){
                    if(cpu.isEmpty() == true){
                        cout <<"sorry, you cannot enter a system call while the cpu is empty" << endl;
                    }else{
                        cout << "You have requested disk # " << k+1 << endl;
                        cout << "What is the name of the file?" << endl;
                        cin >> input;
                        cout << "What is the size of the file?" << endl;
                        cin >> result;
                        cpu.setFunction(input,result); //sets file name and size
                        disks[k].insert(cpu.getProcess()); //insert process to disk's queue
                        cpu.removeProcess();//removes process from cpu
                        if(!q.isEmpty()){
                            cpu.insert(q.insertCPU()); //insert next process from ready queue into cpu
                            q.remove(); //remove the process that was just inserted in cpu
                        }
                    }
                }
            }//end for
            
            //if user input equals to any of these interrupts, signal completion of disk and return process back to ready queue
            for(int l = 0; l < num_of_disks_; ++l){
                if(interrupt == disk_complete[l]){
                    if(disks[l].isEmpty() == true){
                        cout <<"The disk is empty" << endl;
                    }else{
                        q.insert(disks[l].remove());
                        if(cpu.isEmpty() == true){
                            cpu.insert(q.insertCPU());
                            q.remove();
                        }else if(q.insertCPU().getPriority() < cpu.getProcess().getPriority()){ //if there exists a process with higher priority, put that process in cpu(This is the preemptive approach)
                            q.insert(cpu.getProcess());//inserts the process from cpu to the back of ready queue
                            cpu.removeProcess(); //removes the process from cpu
                            cpu.insert(q.insertCPU()); //inserts the process with the higher priority into the cpu
                            q.remove();
                        }
                    }
                }
            }
        }//end else
    }//end while
    return 0;
}
