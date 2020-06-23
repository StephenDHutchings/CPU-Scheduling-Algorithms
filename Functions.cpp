#include "Functions.h"
//Stephen Hutchings

using namespace std;


void OS_Queue::insert_PCB(int pid, int arrival_Time, int CPU_Burst_Time)
{
	//Creates and inserts a new PCB at the back of the queue

	PCB *temp = new PCB;
	temp->pid = pid;
	temp->arrival_Time = arrival_Time;
	temp->CPU_Burst_Time = CPU_Burst_Time;
	temp->CPU_Modified_Burst = CPU_Burst_Time;
	
	if (front == NULL)
	{
		front = back = temp;
	}

	else
	{
		back->next = temp;
		back = temp;
	}

	temp = NULL;
	//delete temp;
}

void OS_Queue::delete_PCB()
{
	//De-allocates the queue

	PCB *deletion = NULL;
	if (front == NULL)
	{
		cout << "The queue is empty" << endl;
	}

	else
	{
		while (front != NULL)
		{
			deletion = front;
			front = front->next;
			delete deletion;
		}
	}
}

OS_Queue::~OS_Queue()
{
	//OS_Queue destructor

	while (front != NULL)
	{
		PCB *temp = front;
		front = front->next;
		delete temp;
	}
}

void OS_Queue::display_Queue()
{

	//Function to display the queue from front to back

	PCB *temp = front;
	if (temp == NULL)
	{
		cout << "The queue is empty" << endl;
	}

	else
	{
		cout << "Starting from the front of the queue: " << endl;
		while (temp != NULL)
		{
			cout << "The pid is: " << temp->pid << endl;
			cout << "The arrival time is " << temp->arrival_Time << endl;
			cout << "The CPU burst time is " <<temp->CPU_Burst_Time << endl;
			cout << "The completion time is " << temp->completion_Time << endl;
			cout << endl;

			temp = temp->next;
		}
	}
}

void OS_Queue::read_File(string fileName)
{
	//Read in the input from the specified file name
	//Place the input into a PCB struct and place it into the OS_Queue object

	ifstream infile;
	int pid = 0, arrival_Time = 0, CPU_Burst = 0;
	int priority = 0;

	infile.open(fileName);

	if (infile.is_open())
	{
		cout << "File was opened" << endl << endl;
	}

	else
	{
		cout << "File was unable to be opened" << endl << endl;
	}

	while (infile >> pid >> arrival_Time >> CPU_Burst)
	{
		insert_PCB(pid, arrival_Time, CPU_Burst);
	}

	infile.close();
}

void OS_Queue::swapPCB(struct PCB *a, struct PCB *b)
{
	//Swaps one PCB with another
	//Used for sorting

	int pid = 0, arrival_Time = 0, CPU_Burst = 0;

	pid = a->pid;
	arrival_Time = a->arrival_Time;
	CPU_Burst = a->CPU_Burst_Time;
	a->pid = b->pid;
	a->arrival_Time = b->arrival_Time;
	a->CPU_Burst_Time = b->CPU_Burst_Time;
	a->CPU_Modified_Burst = b->CPU_Burst_Time;
	a->completion_Time = b->arrival_Time;
	b->pid = pid;
	b->arrival_Time = arrival_Time;
	b->CPU_Burst_Time = CPU_Burst;
	b->CPU_Modified_Burst = CPU_Burst;
	b->completion_Time = arrival_Time;
}

void OS_Queue::sort_Queue()
{
	//Sort on the OS_Queue object
	int swapped, i;
	struct PCB *ptr1 = NULL;
	struct PCB *lptr = NULL;

	// Checking for empty list
	if (front == NULL)
	{

	}

	else
	{
		do
		{
			swapped = 0;
			ptr1 = front;

			while (ptr1->next != lptr)
			{
				if (ptr1->arrival_Time > ptr1->next->arrival_Time)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1;
		} while (swapped);
	}
}

void OS_Queue::FCFS_Algorithm()
{
	//FCFS algorithm 

	PCB *temp = NULL;
	int total_context = 0;
	float average_Burst = 0.00, average_Waiting = 0.00, average_Turn = 0.00, average_Response = 0.00, number_Processes = 0.00, time = 0.00;

	temp = front;

	while (temp != NULL)
	{

		if (temp->response == false)
		{
			//Setting the response time

			temp->response = true;
			temp->response_Time = time - temp->arrival_Time;
		}

		while (temp->CPU_Modified_Burst != 0)
		{
			temp->CPU_Modified_Burst--;
			time++;
		}

		number_Processes++;

		//Calculating the different metrics
		temp->completion_Time = time;
		temp->waiting_Time = temp->completion_Time - (temp->arrival_Time + temp->CPU_Burst_Time);
		temp->turn_Around_Time = temp->waiting_Time + temp->CPU_Burst_Time;

		average_Response = average_Response + temp->response_Time;
		average_Turn = average_Turn + temp->turn_Around_Time;
		average_Waiting = average_Waiting + temp->waiting_Time;
		average_Burst = average_Burst + temp->CPU_Burst_Time;
		total_context = total_context + temp->context_Switches;

		temp = temp->next;
	}

	display_FCFS_Results();

	cout << endl;
	cout << "Average CPU burst time = " << (average_Burst / number_Processes) << " ms" << endl;
	cout << "Average waiting time = " << (average_Waiting / number_Processes) << " ms" << endl;
	cout << "Average turn-around time = " << (average_Turn / number_Processes) << " ms" << endl;
	cout << "Average response time = " << (average_Response / number_Processes) << " ms" << endl;
	cout << "Total number of context switches = " << total_context << endl;
	cout << endl;
}

void OS_Queue::display_FCFS_Results()
{
	PCB *temp = NULL;
	const char separator = ' ';
	const int pid_Width = 5, arrival_Width = 9, burst_Width = 7, complete_Width = 8;
	const int wait_Width = 9, turn_Width = 8, response_Width = 10, context_Width = 8;

	cout << "************************************************************************" << endl;
	cout << "*******************Scheduling Algorithm : FCFS *************************" << endl;
	cout << "************************************************************************" << endl;
	cout << endl;
	cout << "_________________________________________________________________________" << endl;
	cout << "| Pid | Arrival | CPU-  | Finish | Waiting | Turn   | Response | No. of |" << endl;
	cout << "|     |         | Burst |        |  time   | around |   time   | Context|" << endl;
	cout << "|_____|_________|_______|________|_________|________|__________|________|" << endl;

	temp = front;

	while (temp != NULL)
	{
		cout << left << "|" << setw(pid_Width) << setfill(separator) << temp->pid  << "|";
		cout << left << setw(arrival_Width) << setfill(separator) << temp->arrival_Time << "|";
		cout << left << setw(burst_Width) << setfill(separator) << temp->CPU_Burst_Time << "|";
		cout << left << setw(complete_Width) << setfill(separator) << temp->completion_Time << "|";
		cout << left << setw(wait_Width) << setfill(separator) << temp->waiting_Time << "|";
		cout << left << setw(turn_Width) << setfill(separator) << temp->turn_Around_Time << "|";
		cout << left << setw(response_Width) << setfill(separator) << temp->response_Time << "|";
		cout << left << setw(context_Width) << setfill(separator) <<temp->context_Switches << "|";
		cout << endl;
		cout << "_________________________________________________________________________" << endl;

		temp = temp->next;
	}

	cout << endl;

}

PCB* OS_Queue::SJF_Comparison(float time)
{
	//Finds the process with the shortest burst time and returns a pointer to that PCB struct

	PCB *temp = NULL;
	PCB *next_Job = NULL;
	int shortest_Burst = 1000000;

	temp = front;

	while (temp != NULL)
	{
		if (temp->CPU_Modified_Burst < shortest_Burst && temp->arrival_Time <= time && temp->CPU_Modified_Burst != 0)
		{
			next_Job = temp;
			shortest_Burst = temp->CPU_Modified_Burst;
		}
		
		else
		{
		}

		temp = temp->next;
	}

	return next_Job;
}

void OS_Queue::SJF_Algorithm()
{
	//Shortest job first algorithm

	PCB *SJ = NULL;
	PCB *temp = NULL;
	int total_context = 0, jobs = 0;
	float average_Burst = 0.00, average_Waiting = 0.00, average_Turn = 0.00, average_Response = 0.00, number_Processes = 0.00, time = 0.00;

	temp = front;

	while (temp != NULL)
	{
		jobs++;
		temp = temp->next;
	}

	temp = front;
	
	while (jobs != 0)
	{
		SJ = SJF_Comparison(time);

		if (SJ == NULL)
		{
			time++;
		}

		else
		{
			if (SJ->response == false)
			{
				SJ->response = true;
				SJ->response_Time = time - SJ->arrival_Time;
			}

			while (SJ->CPU_Modified_Burst != 0)
			{
				SJ->CPU_Modified_Burst--;
				time++;
			}

			jobs--;
			number_Processes++;

			SJ->completion_Time = time;
			SJ->waiting_Time = SJ->completion_Time - (SJ->arrival_Time + SJ->CPU_Burst_Time);
			SJ->turn_Around_Time = SJ->waiting_Time + SJ->CPU_Burst_Time;

			average_Response = average_Response + SJ->response_Time;
			average_Turn = average_Turn + SJ->turn_Around_Time;
			average_Waiting = average_Waiting + SJ->waiting_Time;
			average_Burst = average_Burst + SJ->CPU_Burst_Time;
			total_context = total_context + SJ->context_Switches;
		}
	}

	display_SJF_Results();

	cout << "Average CPU burst time = " << (average_Burst / number_Processes) << " ms" << endl;
	cout << "Average waiting time = " << (average_Waiting / number_Processes) << " ms" << endl;
	cout << "Average turn-around time = " << (average_Turn / number_Processes) << " ms" << endl;
	cout << "Average response time = " << (average_Response / number_Processes) << " ms" << endl;
	cout << "Total number of context switches = " << total_context << endl;
	cout << endl;
}

void OS_Queue::display_SJF_Results()
{
	//displays SJF results 

	PCB *temp = NULL;
	const char separator = ' ';
	const int pid_Width = 5, arrival_Width = 9, burst_Width = 7, complete_Width = 8;
	const int wait_Width = 9, turn_Width = 8, response_Width = 10, context_Width = 8;

	cout << "************************************************************************" << endl;
	cout << "*******************Scheduling Algorithm : SJF **************************" << endl;
	cout << "************************************************************************" << endl;
	cout << endl;
	cout << "_________________________________________________________________________" << endl;
	cout << "| Pid | Arrival | CPU-  | Finish | Waiting | Turn   | Response | No. of |" << endl;
	cout << "|     |         | Burst |        |  time   | around |   time   | Context|" << endl;
	cout << "|_____|_________|_______|________|_________|________|__________|________|" << endl;

	temp = front;

	while (temp != NULL)
	{
		cout << left << "|" << setw(pid_Width) << setfill(separator) << temp->pid << "|";
		cout << left << setw(arrival_Width) << setfill(separator) << temp->arrival_Time << "|";
		cout << left << setw(burst_Width) << setfill(separator) << temp->CPU_Burst_Time << "|";
		cout << left << setw(complete_Width) << setfill(separator) << temp->completion_Time << "|";
		cout << left << setw(wait_Width) << setfill(separator) << temp->waiting_Time << "|";
		cout << left << setw(turn_Width) << setfill(separator) << temp->turn_Around_Time << "|";
		cout << left << setw(response_Width) << setfill(separator) << temp->response_Time << "|";
		cout << left << setw(context_Width) << setfill(separator) << temp->context_Switches << "|";
		cout << endl;
		cout << "_________________________________________________________________________" << endl;

		temp = temp->next;
	}

	cout << endl;

}

void OS_Queue::RR_Algorithm(int time_Quantum)
{
	//Round robin algorithm 

	PCB *temp = NULL;
	PCB *check = NULL;
	int total_context = 0, jobs = 0;
	float average_Burst = 0.00, average_Waiting = 0.00, average_Turn = 0.00, average_Response = 0.00, number_Processes = 0.00, time = 0.00;

	temp = front;

	while (temp != NULL)
	{
		jobs = jobs + 1;
		temp = temp->next;
	}

	temp = front;

	while (jobs != 0)
	{
		if (temp->arrival_Time <= time)
		{
			while (temp->CPU_Modified_Burst != 0 && temp->done == false && temp->round_Robin == false)
			{
				if (temp->response == false)
				{
					temp->response = true;
					temp->response_Time = time - temp->arrival_Time;
				}

				for (int i = 0; i < time_Quantum; i++)
				{
					temp->CPU_Modified_Burst = temp->CPU_Modified_Burst - 1;
					time = time + 1;

					if (temp->CPU_Modified_Burst == 0)
					{
						temp->done = true;
						jobs = jobs - 1;
						temp->completed = true;
						break;
					}
				}

				temp->round_Robin = true;

				if (temp->CPU_Modified_Burst == 0)
				{

				}

				else
				{
					if (jobs > 2)
					{
						temp->context_Switches = temp->context_Switches + 1;
						time = time + 0.5;
					}
				}
			}

			temp->round_Robin = false;

			if (temp->CPU_Modified_Burst == 0 && temp->completed == true && temp->computation == false)
			{
				number_Processes++;

				temp->completion_Time = time;
				temp->waiting_Time = temp->completion_Time - (temp->arrival_Time + temp->CPU_Burst_Time);
				temp->turn_Around_Time = temp->waiting_Time + temp->CPU_Burst_Time;

				average_Response = average_Response + temp->response_Time;
				average_Turn = average_Turn + temp->turn_Around_Time;
				average_Waiting = average_Waiting + temp->waiting_Time;
				average_Burst = average_Burst + temp->CPU_Burst_Time;
				total_context = total_context + temp->context_Switches;

				temp->computation = true;
			}

			check = temp;
			check = check->next;

			if (check != NULL)
			{
				temp = temp->next;
			}

			else
			{
				temp = front;
			}

			check = NULL;
		}

		else
		{
			time++;
		}
	}

	display_RR_Results(time_Quantum);

	cout << endl;
	cout << "Average CPU burst time = " << (average_Burst / number_Processes) << " ms" << endl;
	cout << "Average waiting time = " << (average_Waiting / number_Processes) << " ms" << endl;
	cout << "Average turn-around time = " << (average_Turn / number_Processes) << " ms" << endl;
	cout << "Average response time = " << (average_Response / number_Processes) << " ms" << endl;
	cout << "Total number of context switches = " << total_context << endl;
	cout << endl;
}

void OS_Queue::display_RR_Results(int time_Quantum)
{
	//Displays the results of the RR algorithm

	PCB *temp = NULL;
	const char separator = ' ';
	const int pid_Width = 5, arrival_Width = 9, burst_Width = 7, complete_Width = 8;
	const int wait_Width = 9, turn_Width = 8, response_Width = 10, context_Width = 8;

	cout << "************************************************************************" << endl;
	cout << "*******************Scheduling Algorithm : RR " << "Time Quantum = " << time_Quantum << "***********" << endl;
	cout << "************************************************************************" << endl;
	cout << endl;
	cout << "_________________________________________________________________________" << endl;
	cout << "| Pid | Arrival | CPU-  | Finish | Waiting | Turn   | Response | No. of |" << endl;
	cout << "|     |         | Burst |        |  time   | around |   time   | Context|" << endl;
	cout << "|_____|_________|_______|________|_________|________|__________|________|" << endl;

	temp = front;

	while (temp != NULL)
	{
		cout << left << "|" << setw(pid_Width) << setfill(separator) << temp->pid << "|";
		cout << left << setw(arrival_Width) << setfill(separator) << temp->arrival_Time << "|";
		cout << left << setw(burst_Width) << setfill(separator) << temp->CPU_Burst_Time << "|";
		cout << left << setw(complete_Width) << setfill(separator) << temp->completion_Time << "|";
		cout << left << setw(wait_Width) << setfill(separator) << temp->waiting_Time << "|";
		cout << left << setw(turn_Width) << setfill(separator) << temp->turn_Around_Time << "|";
		cout << left << setw(response_Width) << setfill(separator) << temp->response_Time << "|";
		cout << left << setw(context_Width) << setfill(separator) << temp->context_Switches << "|";
		cout << endl;
		cout << "_________________________________________________________________________" << endl;

		temp = temp->next;
	}

	cout << endl;
}

PCB* OS_Queue::SRJF_Comparison(float time)
{
	//Returns a pointer to the PCB within the OS_Queue with the shortest remaining time left

	PCB *temp = NULL;
	PCB *next_Job = NULL;
	int shortest_Burst = 1000000;

	temp = front;

	while (temp != NULL)
	{
		if ((temp->CPU_Modified_Burst < shortest_Burst) && (temp->arrival_Time <= time) && (temp->CPU_Modified_Burst != 0))
		{
			next_Job = temp;
			shortest_Burst = temp->CPU_Modified_Burst;
		}

		else
		{
		}

		temp = temp->next;
	}

	return next_Job;
}

void OS_Queue::SRJF_Algorithm()
{
	//SRJF algorithm

	PCB *check = NULL;
	PCB *SRTF = NULL;
	PCB *temp = NULL;
	int total_context = 0, jobs = 0;
	float average_Burst = 0.00, average_Waiting = 0.00, average_Turn = 0.00, average_Response = 0.00, number_Processes = 0.00, time = 0.00;

	temp = front;

	while (temp != NULL)
	{
		jobs++;
		temp = temp->next;
	}

	temp = front;

	while (jobs != 0)
	{
		SRTF = SRJF_Comparison(time);

		if (SRTF == NULL)
		{
			time = time + 1;
		}

		else 
		{
			while (SRTF->CPU_Modified_Burst != 0 && SRTF->done == false)
			{
				if (SRTF->response == false)
				{
					SRTF->response = true;
					SRTF->response_Time = time - SRTF->arrival_Time;
				}

				SRTF->CPU_Modified_Burst--;
				time++;

				if (SRTF->CPU_Modified_Burst == 0)
				{
					SRTF->done = true;
					SRTF->completed = true;
					break;
				}

				check = SRJF_Comparison(time);

				if (check != SRTF)
				{
					SRTF->context_Switches = SRTF->context_Switches + 1;
					time = time + 0.5;
					SRTF = check;
				}
			}

			if (SRTF->CPU_Modified_Burst == 0 && SRTF->completed == true && SRTF->computation == false)
			{
				number_Processes++;

				SRTF->completion_Time = time;
				SRTF->waiting_Time = SRTF->completion_Time - (SRTF->arrival_Time + SRTF->CPU_Burst_Time);
				SRTF->turn_Around_Time = SRTF->waiting_Time + SRTF->CPU_Burst_Time;

				average_Response = average_Response + SRTF->response_Time;
				average_Turn = average_Turn + SRTF->turn_Around_Time;
				average_Waiting = average_Waiting + SRTF->waiting_Time;
				average_Burst = average_Burst + SRTF->CPU_Burst_Time;
				total_context = total_context + SRTF->context_Switches;

				SRTF->computation = true;
				jobs = jobs - 1;
			}

			check = temp;
			check = check->next;

			if (check != NULL)
			{
				temp = temp->next;
			}

			else
			{
				temp = front;
			}

			check = NULL;
		}
	}


	display_SRJF_Results();

	cout << "Average CPU burst time = " << (average_Burst / number_Processes) << " ms" << endl;
	cout << "Average waiting time = " << (average_Waiting / number_Processes) << " ms" << endl;
	cout << "Average turn-around time = " << (average_Turn / number_Processes) << " ms" << endl;
	cout << "Average response time = " << (average_Response / number_Processes) << " ms" << endl;
	cout << "Total number of context switches = " << total_context << endl;
	cout << endl;
}

void OS_Queue::display_SRJF_Results()
{
	//Displays the results of the SRJF algorithm

	PCB *temp = NULL;
	const char separator = ' ';
	const int pid_Width = 5, arrival_Width = 9, burst_Width = 7, complete_Width = 8;
	const int wait_Width = 9, turn_Width = 8, response_Width = 10, context_Width = 8;

	cout << "************************************************************************" << endl;
	cout << "*******************Scheduling Algorithm : SRTF *************************" << endl;
	cout << "************************************************************************" << endl;
	cout << endl;
	cout << "_________________________________________________________________________" << endl;
	cout << "| Pid | Arrival | CPU-  | Finish | Waiting | Turn   | Response | No. of |" << endl;
	cout << "|     |         | Burst |        |  time   | around |   time   | Context|" << endl;
	cout << "|_____|_________|_______|________|_________|________|__________|________|" << endl;

	temp = front;

	while (temp != NULL)
	{
		cout << left << "|" << setw(pid_Width) << setfill(separator) << temp->pid << "|";
		cout << left << setw(arrival_Width) << setfill(separator) << temp->arrival_Time << "|";
		cout << left << setw(burst_Width) << setfill(separator) << temp->CPU_Burst_Time << "|";
		cout << left << setw(complete_Width) << setfill(separator) << temp->completion_Time << "|";
		cout << left << setw(wait_Width) << setfill(separator) << temp->waiting_Time << "|";
		cout << left << setw(turn_Width) << setfill(separator) << temp->turn_Around_Time << "|";
		cout << left << setw(response_Width) << setfill(separator) << temp->response_Time << "|";
		cout << left << setw(context_Width) << setfill(separator) << temp->context_Switches << "|";
		cout << endl;
		cout << "_________________________________________________________________________" << endl;

		temp = temp->next;
	}

	cout << endl;

}

void run_Program()
{
	cout << std::setprecision(2) << std::fixed;
	string menu_Input = " ";

	while (menu_Input != "exit" && menu_Input != "Exit")
	{
		string fileName = " ";
		int scheduling_Algorithm = 0, time_Quantum = 0;
		OS_Queue ready_Queue;

		cout << "This program will test different CPU scheduling algorithms " << endl;
		cout << "Please enter your command in the following way: " << endl;
		cout << "Input_File_Name Algorith_Number Time_Quantum " << endl;
		cout << "Algorithm Number: 0 - FCFS, 1 - SJF, 2 - SRJF, 3 - RR" << endl;
		cout << "If the time quantum is not applicable, please enter 0 for that field" << endl;

		cin >> fileName >> scheduling_Algorithm >> time_Quantum;

		if (scheduling_Algorithm == 0)
		{
			ready_Queue.read_File(fileName);
			ready_Queue.FCFS_Algorithm();
		}

		else if (scheduling_Algorithm == 1)
		{
			ready_Queue.read_File(fileName);
			ready_Queue.SJF_Algorithm();
		}

		else if (scheduling_Algorithm == 2)
		{
			ready_Queue.read_File(fileName);
			ready_Queue.SRJF_Algorithm();
		}

		else if (scheduling_Algorithm == 3)
		{
			ready_Queue.read_File(fileName);
			ready_Queue.RR_Algorithm(time_Quantum);
		}

		ready_Queue.delete_PCB();

		cout << "To exit the simulation enter exit" << endl;
		cout << "Enter any other key to run the simulation again with different perameters" << endl;
		cin >> menu_Input;
		cout << endl;
	}
}
