PROMPT:

Write a program that handles the basic data structures (i.e. the devices and their queues) in an operating system.
The program should have two stages of operation, the "sys gen" section, and the "running" section. During sys gen, the system installer (me) species how many devices of each type (printers and disks) are in the system. Also, your program ask user how much memory our system has. You may assume that there is only one CPU.
During the running section you will have to handle system calls issued by the process currently controlling the CPU as well as interrupts that signal various system events. These calls and interrupts will actually be indicated by keyboard input. Capital letters will be interrupts, lower case will indicate system calls. All I/O queues will be FIFO. CPU should be scheduled using preemptive priority scheduling (with no priority elevation). All interrupts will be handled "atomically" (one can not interrupt an interrupt handling routine) and will return control to the interrupted process.

An "A" entered on the keyboard indicates the arrival of a process. System asks how much memory this process will need and what is its priority. Priority is a non-negative integer number and the lower is the number, the higher is the priority. Allocate memory using "worst-fit" approach. The handling routine should create a PCB for this process, generate a PID, and enqueue the PCB into the Ready Queue. If the CPU is not occupied, the first process in the Ready Queue should be passed to the CPU. The process in the CPU can issue system calls. One of these is "t", which indicate that the process is terminating. The OS should recycle the PCB (but not the PID), in other words reclaim the now unused memory.

Each non-CPU device has a "name" consisting of a letter and an integer. The process currently in the CPU will request "printer 1" by issuing a "p1" on the keyboard, and Printer 1 will signal an interrupt indicating completion of the task at the head of its queue with a "P1" being entered at the keyboard. Similarly, "d3" to request disk 3 and "D3" to signal D3's completion. On such a "task completed" interrupt the PCB for that process should be moved to the back of the Ready Queue. After a system call (e.g. "p3") is made, you should prompt the process (that's me) for parameters. These should include the filename and file size. The PCB for this process and the associated information should be enqueued to the appropriate device queue.

Finally, an "S" on the keyboard indicates a "Snapshot" interrupt (simulating a Big Button on the Sys-op's console). The handling routine should wait for the next keyboard input and, if "r", show the PIDs of the processes in the Ready Queue, if "i", show the printers and disks specific information (this information for each printer and each disk includes I/O queue, the name of the file and its size). If "S" interrupt is followed by "m", show the current state of memory (show where each process is located in memory)

Q: How does this program work?
A: To compile program: g++ -o project1 project1.cpp
   To run program: ./project1

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
