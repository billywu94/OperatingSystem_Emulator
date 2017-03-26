Billy Wu
340 Assignment 1:

Q: How does this program work?
A: To compile program: g++ -o project1 project1.cpp   To run program: ./project1

Key:
  A: Arrival of new process, enter amount of space process needs, and its priority
  S: Snapshot
     - i: snapshot of I/O Queues
     - r: snapshot of Ready Queue
     - m: snapshot of where process is located in memory
  p1: requesting a specific printer, enter size of file and the file’s name
  d1: requesting a specific disk, enter size of file and file’s name
  P1: signals completion of process in front of specific printer’s queue
  D1: signals completion of process in front of specific disk’s queue

The main file is project1.cpp
The language the source is written in: C++