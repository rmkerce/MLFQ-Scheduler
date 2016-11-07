#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct process {
	bool done;
	bool first_time_execution;
	int id;
	int waiting;
	int * burstarray;
	int current_burst;
	int current_I_O;
	int * I_O_time;
	int databank_length;
	int response;
	int priority;
	int end_time;
	int arrival_time = 0;
	process *next;
};

//will initalize the process and will read the CPU burst and I/O time and place them into the corresponding process
process * Initialize_process_databank();

//print out put of:
//current time being executed, the time it being to be executed, the CPU burst of the process being executed,
//three ready queue based on the prioirty level they are in and shows their arrival time
// any process that are in the waiting queue in order by the amount of I/O time they have left and the time they will
//leave the waiting queue also their level priority
//any completed process in order by their ID number
void print_screen_MLFQ(process * Q1, process * Q2, process * Q3, process * waiting, process* executing, int clock, process* complete);

//simulate the MLFQ alogrithm with the 9 processes
void MLFQ(process * p);

int main()
{
	process *p = new process;
	p = Initialize_process_databank();
	MLFQ(p);

	return 0;
}

process * Initialize_process_databank()
{
	process *P1 = new process;         //Declare and initialize 9 pointers to hold the 9 processes
	P1->done = false;
	P1->first_time_execution = true;
	P1->id = 1;
	P1->waiting = 0;
	P1->response = -1;
	P1->priority = 1;
	P1->end_time = -1;
	P1->arrival_time = 0;

	process *P2 = new process;
	P2->done = false;
	P2->first_time_execution = true;
	P2->id = 2;
	P2->waiting = 0;
	P2->response = -1;
	P2->priority = 1;
	P2->end_time = -1;
	P2->arrival_time = 0;

	process *P3 = new process;
	P3->done = false;
	P3->first_time_execution = true;
	P3->id = 3;
	P3->waiting = 0;
	P3->response = -1;
	P3->priority = 1;
	P3->end_time = -1;
	P3->arrival_time = 0;

	process *P4 = new process;
	P4->done = false;
	P4->first_time_execution = true;
	P4->id = 4;
	P4->waiting = 0;
	P4->response = -1;
	P4->priority = 1;
	P4->end_time = -1;
	P4->arrival_time = 0;

	process *P5 = new process;
	P5->done = false;
	P5->first_time_execution = true;
	P5->id = 5;
	P5->waiting = 0;
	P5->response = -1;
	P5->priority = 1;
	P5->end_time = -1;
	P5->arrival_time = 0;

	process *P6 = new process;
	P6->done = false;
	P6->first_time_execution = true;
	P6->id = 6;
	P6->waiting = 0;
	P6->response = -1;
	P6->priority = 1;
	P6->end_time = -1;
	P6->arrival_time = 0;

	process *P7 = new process;
	P7->done = false;
	P7->first_time_execution = true;
	P7->id = 7;
	P7->waiting = 0;
	P7->response = -1;
	P7->priority = 1;
	P7->end_time = -1;
	P7->arrival_time = 0;

	process *P8 = new process;
	P8->done = false;
	P8->first_time_execution = true;
	P8->id = 8;
	P8->waiting = 0;
	P8->response = -1;
	P8->priority = 1;
	P8->end_time = -1;
	P8->arrival_time = 0;

	process *P9 = new process;
	P9->done = false;
	P9->first_time_execution = true;
	P9->id = 9;
	P9->waiting = 0;
	P9->response = -1;
	P9->priority = 1;
	P9->end_time = -1;
	P9->arrival_time = 0;

	P1->next = P2;						//the 9 pointers are connected to each other by a linked list
	P2->next = P3;
	P3->next = P4;
	P4->next = P5;
	P5->next = P6;
	P6->next = P7;
	P7->next = P8;
	P8->next = P9;
	P9->next = 0;

	process *head = P1;

	ifstream arraylist;					//the CPU burst and I/O time are in a text file 
	arraylist.open("array.txt");
	int BURST_time;						//variable to hold the the char to convert it to an int so mathematical operations can be performed on it
	int burst_array_counter = 0;
	int I_O_time;
	int I_O_counter = 0;
	string input;
	string values;
	int array_switch = 0;
	int array_length = 0;
	int seperators = 0;
	while (head && !(arraylist.eof()))
	{
		getline(arraylist, input);
		for (unsigned int a = 0; a < input.length(); a++) //count the amount of commas there is
		{												  //to determine the array length of the 
			if (input[a] == ',')                          //CPU burst array and I/O time array
				seperators++;
		}
		array_length = (seperators / 2) + 1;
		head->burstarray = new int[array_length];         //initialize array length of set of CPU burst of processes
		head->I_O_time = new int[array_length];           //initialize array length of set of I/O time of processes
		head->databank_length = array_length;
		for (unsigned int i = 0; i < input.length(); i++)
		{
			if (input[i] <= 0x39 && input[i] >= 0x30)        //since value of CPU burst and I/O time are in a string, 
			{												 //the string is read one by one to seperate the values from 
				values = values + input[i];					 //commas
			}
			if (input[i] == ',' && values != "")            //if we reach a comma that means that the value has been collected
			{
				if (array_switch == 0)                   // if array switch is 0 that mean that the value that was just read 
				{                                        //is a CPU burst 
					BURST_time = atoi(values.c_str());
					head->burstarray[burst_array_counter] = BURST_time;
					burst_array_counter++;
					array_switch = 1;
					values = "";
				}
				else if (array_switch == 1)            //and if its a 1 that means its a I/O time .
				{
					I_O_time = atoi(values.c_str());
					head->I_O_time[I_O_counter] = I_O_time;
					I_O_counter++;
					array_switch = 0;
					values = "";
				}
			}
		}
		head->I_O_time[I_O_counter] = 0; //set the last I/O time of the process to be 0
		I_O_counter = 0;
		array_length = 0;
		burst_array_counter = 0;
		array_switch = 0;
		head = head->next;
		seperators = 0;
	}
	arraylist.close();
	return P1;
}

//MLFQ Algorithm Execution
void MLFQ(process * p)
{
	bool added_process = false;
	process * head = p;
	process * WQ = 0;
	process * Q1 = 0;
	process * Q2 = 0;
	process * Q3 = 0;
	process * hold = 0;
	process * complete = 0;
	process * executing = 0;
	process * holdQ1, *holdQ3, *holdQ2, *holdQW;
	int clock = 0;
	double idle = 0;
	Q1 = head;

START:
	if (Q1 != 0)
	{
		Q1->current_burst = Q1->burstarray[0];						//for the first process of the ready queue it
		Q1->current_I_O = Q1->I_O_time[0];							//take the begining CPU burst and I/Otime of the array and set
		for (int i = 0; i < Q1->databank_length - 1; i++)			 //it to the current CPU burst and I/O of the process
		{
			Q1->burstarray[i] = Q1->burstarray[i + 1];
			Q1->I_O_time[i] = Q1->I_O_time[i + 1];
		}
		Q1->burstarray[Q1->databank_length - 1] = 0;
		Q1->I_O_time[Q1->databank_length - 1] = 0;
		Q1->databank_length--;
		executing = Q1;												 //now it take the first process of the ready queue and gives it to the 
		Q1 = Q1->next;												//executing queue and the ready queue go to the next process in the 
		executing->next = 0;										//queue and set that to be the next process ready to be exectued
		if (executing->first_time_execution == true)				//this will set the response time of each of the processes
		{
			executing->first_time_execution = false;
			executing->response = clock;

		}
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		for (int i = 0; i < 7; i++)										//loop will run for 7 time units or less depend on processes CPU vurst
		{
			clock++;
			executing->current_burst--;

			holdQ1 = Q1;
			while (holdQ1 != 0)									//for the three different queue priority level it will go to each of the 
			{													//process and increment the wait time by 1 time unut
				holdQ1->waiting++;
				holdQ1 = holdQ1->next;
			}
			holdQ2 = Q2;
			while (holdQ2 != 0)
			{
				holdQ2->waiting++;
				holdQ2 = holdQ2->next;
			}
			holdQ3 = Q3;
			while (holdQ3 != 0)
			{
				holdQ3->waiting++;
				holdQ3 = holdQ3->next;
			}
			holdQW = WQ;
			while (holdQW != 0)							//for all of the process in the waiting queue the I/O time gets decremented by one time unit
			{
				holdQW->current_I_O--;
				if (holdQW->current_I_O == 0)			//if a process finishes it io time it will be added to the back of its corresponding 
				{										//priority level queue
					if (holdQW->priority == 1)
					{
						if (Q1 == 0)
						{
							Q1 = WQ;
							WQ = WQ->next;
							Q1->next = 0;
						}
						else
						{
							hold = Q1;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
						holdQW = WQ;
					}
					else if (holdQW->priority == 2)
					{
						if (Q2 == 0)
						{
							Q2 = WQ;
							WQ = WQ->next;
							Q2->next = 0;
						}
						else
						{
							hold = Q2;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
						holdQW = WQ;
					}
					else if (holdQW->priority == 3)
					{
						if (Q3 == 0)
						{
							Q3 = WQ;
							WQ = WQ->next;
							Q3->next = 0;
						}
						else
						{
							hold = Q3;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
						holdQW = WQ;
					}

				}
				else
				{
					holdQW = holdQW->next;
				}
			}
			if (executing->current_burst == 0)					//will exit if CPU burst is finish before 7 time units
			{
				goto Q1timeup;
			}
		}
	Q1timeup:
		if (executing->current_burst > 0)				//if there is stil some time in the CPU burst the process will be down grade to qa lower prioirty
		{
			executing->arrival_time = clock;
			executing->priority = 2;
			if (Q2 == 0)
			{
				Q2 = executing;
			}
			else
			{
				hold = Q2;
				while (hold != 0 && hold->next != 0)
				{
					hold = hold->next;
				}

				hold->next = executing;
				executing = executing->next;
			}
		}
		else if (executing->current_burst == 0 && executing->current_I_O == 0 && executing->burstarray[0] == 0 && executing->I_O_time[0] == 0)
		{
			executing->end_time = clock;							//process will be added into the complete queue in order
			if (complete == 0)
			{
				complete = executing;
			}
			else
			{
				hold = complete;
				while (hold != 0 && hold->id<executing->id)
				{
					hold = hold->next;
				}
				if (hold == complete)
				{
					executing->next = complete;
					complete = executing;
				}
				else
				{
					holdQ1 = complete;
					while (holdQ1 != 0 && holdQ1->next != hold)
					{
						holdQ1 = holdQ1->next;
					}
					holdQ1->next = executing;
					executing->next = hold;

				}
			}

		}
		else if (WQ == 0)						//	if process has finished it CPU burst within the 7 time units then
		{										// it would be added to the waiting queue in order by it I/O time
			WQ = executing;
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		else
		{
			hold = WQ;
			while (hold != 0 && hold->current_I_O <= executing->current_I_O)
			{
				hold = hold->next;
			}
			if (hold == WQ)
			{
				executing->next = WQ;
				WQ = executing;
			}
			else
			{
				holdQW = WQ;
				while (holdQW != 0 && holdQW->next != hold)
				{
					holdQW = holdQW->next;
				}
				executing->next = hold;
				holdQW->next = executing;
			}
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		goto START;
	}
	else if (Q2 != 0)								// the program will enter this state if all process of prioirty 
	{												//1 are either complete or in waiting queue.
		if (Q2->current_burst <= 0)						//this check if the current burst has been deplete or not becuase
		{												//the process could have been pre-emptive by a process of level 1 priority
			Q2->current_burst = Q2->burstarray[0];
			Q2->current_I_O = Q2->I_O_time[0];
			for (int i = 0; i < Q2->databank_length - 1; i++)  //if CPU has been depleted it set the next current burst and I/O from the  
			{													//next values in the array
				Q2->burstarray[i] = Q2->burstarray[i + 1];
				Q2->I_O_time[i] = Q2->I_O_time[i + 1];			//if there is still some burst time left then it will skip this part 
			}
			Q2->burstarray[Q2->databank_length - 1] = 0;
			Q2->I_O_time[Q2->databank_length - 1] = 0;
			Q2->databank_length--;
		}
		executing = Q2;
		Q2 = Q2->next;
		executing->next = 0;
		if (executing->first_time_execution == true)          //This is purely a check to make sure the process has never been executed before 
		{													  //as priority 1 and the response time would be set there upon first execution
			executing->first_time_execution = false;
			executing->response = clock;

		}
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		for (int i = 0; i < 14; i++)							//now the time quantum for level 2 priority is 14
		{
			clock++;
			executing->current_burst--;							//process in ready queue will have their wait time incremeneted 
			holdQ2 = Q2;
			while (holdQ2 != 0)
			{
				holdQ2->waiting++;
				holdQ2 = holdQ2->next;
			}
			holdQ3 = Q3;
			while (holdQ3 != 0)
			{
				holdQ3->waiting++;
				holdQ3 = holdQ3->next;
			}
			holdQW = WQ;									// all process in ready queue will have their I/O time decremented
			while (holdQW != 0)
			{
				holdQW->current_I_O--;
				if (holdQW->current_I_O == 0)				// any process that have their I/O time depleted will be added to the ready queue
				{											//of their corresponding priority levels
					if (holdQW->priority == 1)
					{
						if (Q1 == 0)
						{
							Q1 = WQ;
							WQ = WQ->next;
							Q1->next = 0;
						}
						else
						{
							hold = Q1;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 2)
					{
						if (Q2 == 0)
						{
							Q2 = WQ;
							WQ = WQ->next;
							Q2->next = 0;
						}
						else
						{
							hold = Q2;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 3)
					{
						if (Q3 == 0)
						{
							Q3 = WQ;
							WQ = WQ->next;
							Q3->next = 0;
						}
						else
						{
							hold = Q3;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					holdQW = WQ;
				}
				else
				{
					holdQW = holdQW->next;
				}
			}
			if (Q1 != 0 && executing->current_burst>0)  // checks if any process of level 1 priority have been added to the queue
			{											//it will enter this part only if the process being executed still has burst time
				executing->arrival_time = clock;		//to pre-empt it
				if (Q2 == 0)
				{
					Q2 = executing;

				}
				else
				{
					hold = Q2;
					while (hold->next != 0)
					{
						hold = hold->next;
					}
					hold->next = executing;
					executing = executing->next;
				}
				goto START;
			}
			if (executing->current_burst == 0)			//if the CPU burst is complete before or at 14 time unit it will go to Q2TIMEUP
			{											
				goto Q2TIMEUP;
			}


		}
	Q2TIMEUP:
		if (executing->current_burst > 0)				//if process still has time left on the current burst the process will 
		{												//downgrade to level 3 priority
			executing->arrival_time = clock;
			executing->priority = 3;
			if (Q3 == 0)
			{
				Q3 = executing;
			}
			else
			{
				hold = Q3;
				while (hold != 0 && hold->next != 0)
				{
					hold = hold->next;
				}

				hold->next = executing;
				executing = executing->next;
			}
		}
		else if (executing->current_burst == 0 && executing->current_I_O == 0 && executing->burstarray[0] == 0 && executing->I_O_time[0] == 0)
		{
			executing->end_time = clock;				//if process complete all CPU bursts it will set ending time and will be placed in the complete queue
			if (complete == 0)
			{
				complete = executing;
			}
			else
			{
				hold = complete;
				while (hold != 0 && hold->id<executing->id)
				{
					hold = hold->next;
				}
				if (hold == complete)
				{
					executing->next = complete;
					complete = executing;
				}
				else
				{
					holdQ1 = complete;
					while (holdQ1 != 0 && holdQ1->next != hold)
					{
						holdQ1 = holdQ1->next;
					}
					holdQ1->next = executing;
					executing->next = hold;

				}
			}

		}
		else if (WQ == 0)								//places process in waiting queue in order		
		{
			WQ = executing;
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		else
		{
			hold = WQ;
			while (hold != 0 && hold->current_I_O <= executing->current_I_O)
			{
				hold = hold->next;
			}
			if (hold == WQ)
			{
				executing->next = WQ;
				WQ = executing;
			}
			else
			{
				holdQW = WQ;
				while (holdQW != 0 && holdQW->next != hold)
				{
					holdQW = holdQW->next;
				}
				executing->next = hold;
				holdQW->next = executing;
			}
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		goto START;
	}
	else if (Q3 != 0)										
	{
		if (Q3->current_burst <= 0)							//check if there is still CPU burst that might have been
		{													// left over from before because the process got pre-empted
			Q3->current_burst = Q3->burstarray[0];
			Q3->current_I_O = Q3->I_O_time[0];
			for (int i = 0; i < Q3->databank_length - 1; i++)
			{
				Q3->burstarray[i] = Q3->burstarray[i + 1];
				Q3->I_O_time[i] = Q3->I_O_time[i + 1];
			}
			Q3->burstarray[Q3->databank_length - 1] = 0;
			Q3->I_O_time[Q3->databank_length - 1] = 0;
			Q3->databank_length--;
		}
		executing = Q3;
		Q3 = Q3->next;
		executing->next = 0;
		if (executing->first_time_execution == true)
		{
			executing->first_time_execution = false;
			executing->response = clock;

		}
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		for (int CPU = 0; CPU < executing->current_burst;)
		{																//process will run until its current CPU burst is deplete, or
			clock++;													//if another process of higher priority comes into the ready queue

			holdQ3 = Q3;
			while (holdQ3 != 0)											//increment all processes in ready queue by 1 time unit
			{
				holdQ3->waiting++;
				holdQ3 = holdQ3->next;
			}
			holdQW = WQ;												//decrement all I/O time by 1 
			while (holdQW != 0)											//check to see if any processes are finished with I/O and send them to 
			{															//ready queue of corresponding priority
				holdQW->current_I_O--;
				if (holdQW->current_I_O == 0)
				{
					if (holdQW->priority == 1)
					{
						if (Q1 == 0)
						{
							Q1 = WQ;
							WQ = WQ->next;
							Q1->next = 0;
						}
						else
						{
							hold = Q1;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 2)
					{
						if (Q2 == 0)
						{
							Q2 = WQ;
							WQ = WQ->next;
							Q2->next = 0;
						}
						else
						{
							hold = Q2;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 3)
					{
						if (Q3 == 0)
						{
							Q3 = WQ;
							WQ = WQ->next;
							Q3->next = 0;
						}
						else
						{
							hold = Q3;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					holdQW = WQ;
				}
				else
				{
					holdQW = holdQW->next;
				}
			}
			executing->current_burst--;
			if ((Q1 != 0 || Q2 != 0) && executing->current_burst>0)					//check if any higher priority level queue enter the ready queue 
			{																		//also to see if the process has complete its burst or not to either 
																					//pre-empt it or send it to waiting queue
				executing->arrival_time = clock;
				if (Q3 == 0)
				{
					Q3 = executing;

				}
				else
				{
					hold = Q3;
					while (hold->next != 0)
					{
						hold = hold->next;
					}
					hold->next = executing;
					executing = executing->next;
				}
				goto START;

			}
		}
		if (executing->current_burst == 0 && executing->current_I_O == 0 && executing->burstarray[0] == 0 && executing->I_O_time[0] == 0)
		{
			executing->end_time = clock;			//adds process to the complete queue for output later
			if (complete == 0)
			{
				complete = executing;
			}
			else
			{
				hold = complete;
				while (hold != 0 && hold->id<executing->id)
				{
					hold = hold->next;
				}
				if (hold == complete)
				{
					executing->next = complete;
					complete = executing;
				}
				else
				{
					holdQ1 = complete;
					while (holdQ1 != 0 && holdQ1->next != hold)
					{
						holdQ1 = holdQ1->next;
					}
					holdQ1->next = executing;
					executing->next = hold;

				}
			}

		}
		else if (WQ == 0)			//add process to the waiting queue in order 
		{
			WQ = executing;
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		else
		{
			hold = WQ;
			while (hold != 0 && hold->current_I_O <= executing->current_I_O)
			{
				hold = hold->next;
			}
			if (hold == WQ)
			{
				executing->next = WQ;
				WQ = executing;
			}
			else
			{
				holdQW = WQ;
				while (holdQW != 0 && holdQW->next != hold)
				{
					holdQW = holdQW->next;
				}
				executing->next = hold;
				holdQW->next = executing;
			}
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		goto START;
	}
	else if (WQ != 0)								//the program is in idle at this point and will stay idle until another process shows up
	{
		holdQW = WQ;
		executing = 0;
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
	idleloop:
		holdQW = WQ;
		clock++;
		idle++;
		while (holdQW != 0)
		{

			holdQW->current_I_O--;
			if (holdQW->current_I_O == 0)
			{
				if (holdQW->priority == 1)
				{
					if (Q1 == 0)
					{
						Q1 = WQ;
						WQ = WQ->next;
						Q1->next = 0;
					}
					else
					{
						hold = Q1;
						while (hold->next != 0)
						{
							hold = hold->next;
						}
						hold->next = WQ;
						WQ = WQ->next;
						hold->next->next = 0;
					}
				}
				else if (holdQW->priority == 2)
				{
					if (Q2 == 0)
					{
						Q2 = WQ;
						WQ = WQ->next;
						Q2->next = 0;
					}
					else
					{
						hold = Q2;
						while (hold->next != 0)
						{
							hold = hold->next;
						}
						hold->next = WQ;
						WQ = WQ->next;
						hold->next->next = 0;
					}
				}
				else if (holdQW->priority == 3)
				{
					if (Q3 == 0)
					{
						Q3 = WQ;
						WQ = WQ->next;
						Q3->next = 0;
					}
					else
					{
						hold = Q3;
						while (hold->next != 0)
						{
							hold = hold->next;
						}
						hold->next = WQ;
						WQ = WQ->next;
						hold->next->next = 0;
					}
				}
				holdQW = WQ;
			}
			else
			{
				holdQW = holdQW->next;
			}
		}
		if (Q1 == 0 && Q2 == 0 && Q3 == 0)				//program will stay in idle until a process comes out of the waiting queue
		{
			goto idleloop;
		}
		goto START;
	}
	else if (complete != 0)
	{
									//at this point now all process have been complete and displays the last run time 
		double averageWT = 0;		//also calculates the CPU utilization, turnaround time, response time, and wait time 
		double averageRT = 0;
		double averageTT = 0;
		double timecalc = 0;
		double timeidle = 0;
		executing = 0;
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		cout << "---------------------------------------------------------" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "Current Time: " << clock << endl << endl;
		cout << "Process Completed" << endl << endl;
		cout << "\tProcess" << "\t\tRT" << "\t\tWT" << "\t\tTT" << endl;
		while (complete != 0)
		{

			cout << "\tP" << complete->id << "\t\t" << complete->response << "\t\t" << complete->waiting << "\t\t" << complete->end_time << endl;
			averageWT = averageWT + complete->waiting;
			averageRT = averageRT + complete->response;

			averageTT = averageTT + complete->end_time;
			complete = complete->next;

		}
		averageWT = averageWT / 9;
		averageRT = averageRT / 9;
		averageTT = averageTT / 9;
		timeidle = 1 - idle / clock;
		cout << endl << "Average Response Time:" << averageRT << endl;
		cout << endl << "Average Wait Time:" << averageWT << endl;
		cout << endl << "Average Turnaround Time:" << averageTT << endl;
		cout << endl << "CPU utilization:" << timeidle * 100 << "%" << endl << endl;

	}
}

void print_screen_MLFQ(process * Q1, process * Q2, process * Q3, process * waiting, process* executing, int clock, process * complete)
{
	cout << "---------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "Current Time: " << clock << endl;							//displays current time
	if (executing != 0)													//displays the current process executing or if it's idle
	{
		cout << "Now Running: P" << executing->id << "\t\tBurst:" << executing->current_burst << endl;
		cout << "---------------------------------------------------------" << endl;
	}
	else if (executing == 0)
	{
		cout << "Now Running: idle" << "\t\tBurst: n/a" << endl;
		cout << "---------------------------------------------------------" << endl;
	}

	cout << "Ready Queue with Priority 1:" << endl;
	cout << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;				//Display all process in the ready queue of the 3 priority whether its empty 
	if (Q1 != 0)																	//or not
	{

		while (Q1 != 0)
		{
			cout << "\t\tP" << Q1->id << "\t\t" << Q1->burstarray[0] << "\t\t" << Q1->arrival_time << endl;
			Q1 = Q1->next;
		}
	}
	else if (Q1 == 0)
	{
		cout << "\t\t[empty]" << endl;
	}
	cout << "Ready Queue with Priority 2:" << endl;
	cout << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (Q2 != 0) //Displays Current burst and arrival time for processes in Q2
	{

		while (Q2 != 0)
		{
			if (Q2->current_burst > 0)
			{
				cout << "\t\tP" << Q2->id << "\t\t" << Q2->current_burst << "\t\t" << Q2->arrival_time << endl;
				Q2 = Q2->next;
			}
			else
			{
				cout << "\t\tP" << Q2->id << "\t\t" << Q2->burstarray[0] << "\t\t" << Q2->arrival_time << endl;
				Q2 = Q2->next;
			}
		}
	}
	else if (Q2 == 0)
	{
		cout << "\t\t[empty]" << endl;
	}
	cout << "Ready Queue with Priority 3:" << endl;
	cout << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (Q3 != 0) //Displays Current burst and arrival time for processes in Q3
	{

		while (Q3 != 0)
		{
			if (Q3->current_burst > 0)
			{
				cout << "\t\tP" << Q3->id << "\t\t" << Q3->current_burst << "\t\t" << Q3->arrival_time << endl;
				Q3 = Q3->next;
			}
			else
			{
				cout << "\t\tP" << Q3->id << "\t\t" << Q3->burstarray[0] << "\t\t" << Q3->arrival_time << endl;
				Q3 = Q3->next;
			}
		}
	}
	else if (Q3 == 0)
	{
		cout << "\t\t[empty]" << endl;
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "Waiting Queue:" << endl;
	cout << "\tProcess" << "\t\tI/O" << "\t\tArrival" << "\t\tPriority" << endl;
	if (waiting == 0)															//display all processes in waiting queue, or if its empty
	{
		cout << "\t\t[empty]" << endl;
	}
	else if (waiting != 0)
	{
		while (waiting != 0)
		{
			cout << "\tP" << waiting->id << "\t\t" << waiting->current_I_O << "\t\t" << waiting->arrival_time << "\t\tQ" << waiting->priority << endl;
			waiting = waiting->next;
		}
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "Completed Queues:" << endl;
	cout << "\t\tProcess" << endl;
	if (complete == 0)										//displays all completed process for the user				
	{
		cout << "\t\t[empty]" << endl;
	}
	else if (complete != 0)
	{
		while (complete != 0)
		{
			cout << "\t\tP" << complete->id << endl;
			complete = complete->next;
		}
	}
	cout << "---------------------------------------------------------" << endl << endl << endl;
}
