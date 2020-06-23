
#ifndef Functions_H
#define Functions_H

//Stephen Hutchings

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//Struct to hold information about the PCB
struct PCB
{
	int pid = 0;
	int arrival_Time = 0;
	int CPU_Burst_Time = 0;
	int CPU_Modified_Burst = 0;
	int context_Switches = 0;	
	float completion_Time = 0.00;
	float waiting_Time = 0.00;
	float turn_Around_Time = 0.00;
	float response_Time = 0.00;
	bool completed = false;
	bool context_Switch = false;
	bool done = false;
	bool round_Robin = false;
	bool computation = false;
	bool response = false;
	bool SRTF = false;
	struct PCB *next = NULL;
};

//Queue class to run the the necessary functions and utilize the PCB
class OS_Queue
{
public:
	PCB *front = NULL, *back = NULL;
	OS_Queue() { front = back = NULL; }
	void insert_PCB(int pid, int arrival_Time, int CPU_Burst_Time);
	void delete_PCB();
	~OS_Queue();
	void display_Queue();
	void read_File(string fileName);
	void swapPCB(struct PCB *a, struct PCB *b);
	void sort_Queue();
	void FCFS_Algorithm();
	void display_FCFS_Results();	
	PCB* SJF_Comparison(float time);
	void SJF_Algorithm();
	void display_SJF_Results();
	void RR_Algorithm(int time_Quantum);
	void display_RR_Results(int time_Quantum);
	PCB * SRJF_Comparison(float time);
	void SRJF_Algorithm();
	void display_SRJF_Results();
};

void run_Program();
#endif
