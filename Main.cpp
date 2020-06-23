#include "Functions.h"

/*
Stephen Hutchings
10-30-2018
Program to simulate different CPU scheduling algorithms through an input file detailing processes
CPU scheduling algorithms are First Come First Serve (FCFS), Shortest Job First (SJF), Shortest Remaining Job First (SRJF), and Round Robin (RR)
CPU scheduling algorithms are evaluated on metrics including average turn-around-time, average waiting time, and average response time
Information given about the processes include:
	PID: unique process ID (int)
	arrival time: time when the process arrives (int)
	CPU burst time: time needed for the process to complete CPU operations (int)

Information gathered about the processes include:
	Time of completion, waiting time, turn around time, response time, number of context switches

Simulation Environment:
	One CPU, processes need only CPU operations, processes have same priority, processes are stored in a ready queue
	Context switching occurs a cost of 0.5 ms
	Context switching only occurs when a current running process is moved back into the ready queue
	FCFS is used for tie-breaking situations (processes reach ready queue at the same time)

Output of simulation is a Gannt chart
*/

int main()
{

	run_Program();
}
