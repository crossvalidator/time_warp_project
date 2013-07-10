//main.cpp

// first part has all include statements and declaration of some global variables like queues and stacks of LPs

// second part has class LogicalProcessor which contains all the functions for each LP behavior

// third part has the main() function where MPI and threads are initiated and combined appropriately 


#include "heapoverall.h"
#include "Queueclass.h"
#include "exponentialrandomvariable.h"
#include "stackclass.h"


//#include <list>
#include <mpi.h>
#include <iostream>

//#include<process.h>
#using <mscorlib.dll>
#include<random>

//#include <dos.h>
#include <stdio.h>
#include<math.h>
#include <conio.h>
#include<time.h>
#include<cstdlib>
#include <iomanip>
#include <windows.h>


using namespace System;
using namespace System::Threading;
using System::Random;

using namespace std;


Queue ip1Q;
Queue op1Q;
Queue ip2Q;
Queue op2Q;
Queue ip3Q;
stackclass state3stack;
stackclass op3stack;
Queue ip4Q;
Queue op4Q;
stackclass state4stack;

Heap* myheap = new Heap();

float pt1 = 0.2;
float pt2 = 1.6;
float pt3 = 1.7;
float pt4 = 1.0;
int initialheapsize = 7;

int whentoend =0;

ref class LogicalProcessor
{ // class begins

public:

	// Setting up mutexes 

				
	static Mutex^ ip1Q_Mutex = gcnew Mutex;  /* Creating Mutex for LP 1 input buffer */

	static Mutex^ ip2Q_Mutex = gcnew Mutex;  /* Creating Mutex for LP 2 input buffer */

	static Mutex^ ip3Q_Mutex = gcnew Mutex;  /* Creating Mutex for LP 3 input buffer */

	static Mutex^ op1Q_Mutex = gcnew Mutex;  /* Creating Mutex for LP 1 output buffer */

	static Mutex^ op2Q_Mutex = gcnew Mutex;  /* Creating Mutex for LP 2 output buffer */

	static Mutex^ state3stack_Mutex = gcnew Mutex;  /* Creating Mutex for LP 3 state stack */

	static Mutex^ op3stack_Mutex = gcnew Mutex;  /* Creating Mutex for LP 3 output stack */

	static Mutex^ myheap_Mutex = gcnew Mutex;  // Creating Mutex for heap pointer ..not sure if this will work

	static Mutex^ ip4Q_Mutex = gcnew Mutex;  /* Creating Mutex for LP 4 input buffer */

	static Mutex^ op4Q_Mutex = gcnew Mutex;  /* Creating Mutex for LP 4 output buffer */

	static Mutex^ state4stack_Mutex = gcnew Mutex;  /* Creating Mutex for LP 4 output buffer */


		
	/****************************************************************************************************************/


	/*******************************************************************************************/

	/* Lp_One */

	static void Lp_One(Object^ name)
	{
	    
		event* temp1 = new event;
		event* increasetimestamp1 = new event;
		char ww;
		float firstsleep = rand();
		
		while(1)
		{ // while(1) loop begins
			//cout<<"LP1"<<endl;
			Thread::Sleep(rand()-firstsleep); // sleeping time of processor is kept as the difference of two rand numbers

			//cout<<"IP queue of LP1 is"<<" ";
			//ip1Q.print();

			//cout<<"OP queue of LP1 is"<<" ";
			//op1Q.print();

			//cout<<"haha";
			//cin>>ww;
			//cout<<endl;

            myheap_Mutex->WaitOne(); // checking if the mutex for heap is accessed by anyone else
			

			if (myheap->size()>0)
			{
				temp1->timestamp = myheap->deletemin();
			    temp1->originalsource = 1;
				//temp1->serialnumber = 0; /// have to decide on this parameter - if i decide to use it, i will have to modify heap class
				temp1->nextevent = NULL;
				temp1->pastevent = NULL;
				ip1Q.Enqueue(temp1);
				//cout<<"LP1 picked up \t"<<temp1->timestamp<<endl;
			}

			else
			{
				cout<<"heap is empty - as seen by LP1"<<endl;
				  myheap_Mutex->ReleaseMutex(); // not sure about this
				return;
			}


            myheap_Mutex->ReleaseMutex(); // releasing the mutex for heap

		   // cout<<"IP queue of LP1 is"<<" ";
			//ip1Q.print();

			Thread::Sleep(rand()-firstsleep); // sleeping time of LP1 should be random


			if (ip1Q.count>0)
			{
				increasetimestamp1 = ip1Q.Dequeue();
				increasetimestamp1->timestamp = increasetimestamp1->timestamp + pt1; //pt1 is processing time of LP1
				op1Q.Enqueue(increasetimestamp1);
			}


			ip3Q_Mutex->WaitOne();

			if (op1Q.count >0)
			{
				ip3Q.Enqueue(op1Q.Dequeue());
			}

			ip3Q_Mutex->ReleaseMutex();


			//cout<<"IP queue of LP1 is"<<" ";
			//ip1Q.print();

			//cout<<"OP queue of LP1 is"<<" ";
			//op1Q.print();
		
		} // end of while(1) loop - end of LP1's activity


		//inputQueue_Lp_One_Mutex->WaitOne();

		//cout<<endl<<endl<<"Lp_One"<<endl;

		//Thread::Sleep(1000);

		//inputQueue_Lp_One_Mutex->ReleaseMutex();
	} // end of LP 1

	/****************************************************************************************************************/

	/* LP_Two */

	static void Lp_Two(Object^ name)
	{
		
		//event * temp = new event;
		
		event* temp2 = new event;
		event* increasetimestamp2 = new event;

		//float pt2 = 0; // can change this 
		float secondsleep = rand();
		char re;

		while(1)
		{
			//cout<<"LP2"<<endl;
			//cout<<"hihi"<<endl;
			
			Thread::Sleep(rand()-secondsleep);  // should be random

			//cout<<"IP queue of LP2 is"<<" ";
			//ip2Q.print();

			//cout<<"OP queue of LP2 is"<<" ";
			//op2Q.print();

			//cin>>re;
			//cout<<endl;

			myheap_Mutex->WaitOne();
			//ip1Q_Mutex->WaitOne();

			if (myheap->size()>0)
			{
				temp2->timestamp = myheap->deletemin();
			    temp2->originalsource = 2;
				//temp2->serialnumber = 0; /// have to decide on this parameter - if i decide to use it, i will have to modify heap class
				temp2->nextevent = NULL;
				temp2->pastevent = NULL;
				ip2Q.Enqueue(temp2);
				//cout<<"LP2 picked up \t"<<temp2->timestamp<<endl;
			}

			else
			{
				cout<<"heap is empty as seen by LP2"<<endl;;
			    myheap_Mutex->ReleaseMutex(); // not sure about this
				return;
			}

							
		   // ip1Q_Mutex->ReleaseMutex();
		    myheap_Mutex->ReleaseMutex(); // not sure about this

		   // cout<<"IP queue of LP2 is"<<" ";
			//ip2Q.print();

			//Thread::Sleep(rand()-secondsleep); 

			if (ip2Q.count>0)
			{
				increasetimestamp2 = ip2Q.Dequeue();
				increasetimestamp2->timestamp = increasetimestamp2->timestamp + pt2; // pt2 = processing time of 2
				// may add one more sleeping time here
				// Thread::Sleep(10);
				op2Q.Enqueue(increasetimestamp2);  // processor 2's processing time should be added here
			}


			/*

			if (ip2Q.count>0)
				op2Q.Enqueue(ip2Q.Dequeue());  // processor 2's processing time should be added here
            */

			ip3Q_Mutex->WaitOne();

			if (op2Q.count >0)
			{

				ip3Q.Enqueue(op2Q.Dequeue());
			}

			ip3Q_Mutex->ReleaseMutex();

			//cout<<"IP queue of LP2 is"<<" ";
			//ip2Q.print();

			//cout<<"OP queue of LP2 is"<<" ";
			//op2Q.print();
		
		} // end of while(1) loop - end of LP2's activity



			//inputQueue_Lp_One_Mutex->WaitOne();
		//cout<<endl<<endl<<"Lp_Two"<<endl;
		//Thread::Sleep(1000);
		//inputQueue_Lp_One_Mutex->ReleaseMutex();
	} // end of lp 2


	/****************************************************************************************************************/

	/* LP_Three */

	static void Lp_Three(Object^ name)
	{
		
		int position = 0, dest = 1, tag = 50, src = 0; MPI_Status  status;
		float buf[2];
		//Queue ip3Q;
		//stackclass state3stack;
		//stackclass op3stack;

		event* temp = new event;
		event* increasetimestamp3 = new event;
		event* antimessage = new event;
		char yy;
		//float pt3 = 2.0; // can chaneg this

		float thirdsleep = rand();

		while(1)
		{
			cout<<"LP3"<<endl;
			
			//cin>>yy;
			//cout<<endl;

			Thread::Sleep(rand()-thirdsleep);

			while (ip3Q.count==0)
			{
				//cout<<"haha";

				if(whentoend ==1)
				{
					return;
				}
			}



			
			ip3Q_Mutex->WaitOne();

			
			cout<<"********************************************************"<<endl;
			cout<<"IP queue of LP3 is"<<" ";
			ip3Q.print();

			cout<<"state stack of LP3 is"<<" ";
			state3stack.print();

			cout<<"OP stack of LP3 is"<<" ";
			op3stack.print();

			cout<<"********************************************************"<<endl;
			

			ip3Q_Mutex->ReleaseMutex();
			



			// stopping the output queues of lp 1 and lp 2 before accessing ip  queue of lp 3
			//op1Q_Mutex->WaitOne();
			//op1Q_Mutex->WaitOne();


			ip3Q_Mutex->WaitOne();

			temp = ip3Q.Dequeue(); // event taken from input queue of LP 3

			*increasetimestamp3 = *temp;

			increasetimestamp3->timestamp = increasetimestamp3->timestamp + pt3; // processing time of LP3

			increasetimestamp3->timestamp = -1*(increasetimestamp3->timestamp); // processing time of LP3


			// now this event will be pushed into the state stack of event 3
			// for that following routinge will be used

			ip3Q_Mutex->ReleaseMutex();

			//op1Q_Mutex->ReleaseMutex();
			//op1Q_Mutex->ReleaseMutex();

			if (state3stack.count == 0)    // checking if the state stack is empty
			{
				state3stack.Push(temp);
				//op3stack.Push(temp); // need to add processing time and chnag ethe sign of the timestamp
				op3stack.Push(increasetimestamp3);
				buf[1]=increasetimestamp3->timestamp;
				buf[1] = -1*(buf[1]);
				buf[2] = increasetimestamp3->originalsource;

				MPI_Send(buf, 2, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);

				// mpi message passing will have to be added here, passed message will have processor 3's processing time added to it
			}
		 
			else                        // state stack is not empty
			{

				if(temp->timestamp <= state3stack.Top()->timestamp)
				{ 
					// roll back will be required 

					// events rolled back from the state stack will be first stored 
					// in a temporary stack and then they will be passed over to the ip queue

					
					cout<<"********************************************************"<<endl<<"Roll back is taking place here because a smaller event has been detected"<<endl<<"********************************************************"<<endl;
					//cout<<"********************************************************"<<endl;
					//cout<<"roll back taking place"<<endl;
					//cout<<"********************************************************"<<endl;

					// since roll back will be reqquired, i will freeze the ip queue of ip 3 till i get all the events to be rolled back 
					// in temporary stack, this will reduce further losses
					// after that i will activate ip queue of lp3 but disable output queueus of lp1 and lp2

			

					stackclass tempstacktoip;
					stackclass tempstacktompi;

					ip3Q_Mutex->WaitOne(); // this ensures minimum events to be rolled back
			
					int temporarycounter = state3stack.count;

					while (temporarycounter>0)
					{
				
						if(state3stack.count>0 && temp->timestamp <= state3stack.Top()->timestamp )  // have to check if this is okay??
						{
							tempstacktoip.Push(state3stack.Pop());
							tempstacktompi.Push(op3stack.Pop());
						}
					temporarycounter =temporarycounter-1;
					}

					/*
					state3stack.Push(temp);

					//temp->timestamp = temp->timestamp + pt3; // pt3 = processing time 3



					//op3stack.Push(temp);  // may add the processing time here - haven't done it yet

					op3stack.Push(increasetimestamp3);

					buf[1] = increasetimestamp3->timestamp;
					buf[1] = -1*buf[1];
					buf[2] = increasetimestamp3->originalsource;
					MPI_Send(buf, 2, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);

					*/

					//ip3Q_Mutex->ReleaseMutex();
					//op1Q_Mutex->WaitOne();
					//op2Q_Mutex->WaitOne();

					//ip3Q_Mutex->ReleaseMutex();
					
					// now i will be blocking op queues of lp1 and lp2

			

					// now the temporary stack will be emptied in ip queue and mpi respectively


					//ip3Q_Mutex->WaitOne();

					int count1 = tempstacktoip.count;
		    
					for(int hh=1; hh<count1 + 1; hh++)
					{
						ip3Q.Enqueue(tempstacktoip.Pop());

						antimessage = tempstacktompi.Pop();
						buf[1]=antimessage->timestamp;
						buf[2]=antimessage->originalsource;
						MPI_Send(buf, 2, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
						// send tempstacktompi.Pop() through mpi 
						//temp still has to be sent through mpi - it will be sent after the stacked out anti messages
					}


					state3stack.Push(temp);

					//temp->timestamp = temp->timestamp + pt3; // pt3 = processing time 3



					//op3stack.Push(temp);  // may add the processing time here - haven't done it yet

					op3stack.Push(increasetimestamp3);

					buf[1] = increasetimestamp3->timestamp;
					buf[1] = -1*buf[1];
					buf[2] = increasetimestamp3->originalsource;
					MPI_Send(buf, 2, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);






						//op1Q_Mutex->ReleaseMutex();
						//op2Q_Mutex->ReleaseMutex();
						// rollling back done 
						// yes, i have to add proper mutexes yet
						ip3Q_Mutex->ReleaseMutex();
			
				}// end of loop corresponding to roll back

				else  // no rolling back required
				{
					state3stack.Push(temp);
					op3stack.Push(increasetimestamp3);
					buf[1] = increasetimestamp3->timestamp;
					buf[1] = -1*(buf[1]);
					buf[2] = increasetimestamp3->originalsource;
					MPI_Send(buf, 2, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);


					// message to processor to using MPI will be insterted here
				}  // LP3's responsibilities end here huh.

			} // end of loop corresponding to non empty stack
			


			ip3Q_Mutex->WaitOne();
			cout<<"********************************************************"<<endl;
			cout<<"IP queue of LP3 is"<<" ";
			ip3Q.print();

			cout<<"state stack of LP3 is"<<" ";
			state3stack.print();

			cout<<"OP stack of LP3 is"<<" ";
			op3stack.print();

			cout<<"********************************************************"<<endl;

			ip3Q_Mutex->ReleaseMutex();

		} // end of while(1) loop

			
		

		
			//inputQueue_Lp_One_Mutex->WaitOne();
		//cout<<endl<<endl<<"Lp_Three"<<endl;
		//Thread::Sleep(1000);
		//inputQueue_Lp_One_Mutex->ReleaseMutex();
	} // end of LP 3 function


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	static void Lp_Four(Object^ name)
	{

		float c=0;
		int cc;
		int s;
		//float pt4 = 1.0;
		event* anticheck = new event;
		event* increasetimestamp4 = new event;
		event* tempevent = new event;
		char kk;



		////// data structures for annihilate////
		int ipsize;
		int stacksize; 
		int success1 = 0;
		int counter, savecounter, subcounter;
		//float c = 0;
		//counter = ip4Q.Size();
		event* tt = new event;
		event* nn = new event;
		//event* anticheck = new event;
		//int cc;
		///////////////////////////////////////////////////
		////////////////////////////////////////


		int emergency=0;

		char kya;


		while(1)
		{

			if(ip4Q.Size()==0 && state4stack.Size()==initialheapsize)
			{
				whentoend =1;
				//cout<<" I am here456"<<endl;
				cout<<endl<<"All events have been processed. Simulation is over. Thank you."<<endl;
				return;

			}
			


			if(ip4Q.Size()>0)
			{
				//ip4Q_Mutex->WaitOne(); // not sure of this will work

				Thread::Sleep(250); 

				ip4Q_Mutex->WaitOne(); // not sure of this will work

				cout<<"********************************************************"<<endl;
				cout<<"IP queue of LP4 is"<<" ";
				ip4Q.print();

				cout<<"Stack of LP4 is"<<" ";
				state4stack.print();

				cout<<"********************************************************"<<endl;
				//cout<<"OP queue of LP4 is"<<" ";
				//op4Q.print();
			

				counter = ip4Q.Size();
				stacksize = state4stack.Size();
				
				//annihilatemessage();

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// annihilate routine // brace yopurselves gentlemen //////////////////////////////////////////////////////////
				while(counter>0)  // this loop finds the latest anti message in the input queue of 4, if one is present of course
				{
					success1 =0;

				    tt = ip4Q.rear;
					c = tt->timestamp;
		 			savecounter =0;
					emergency =0;
				    while(counter>0)
					{
	
						if(c<0)
						{ // found a negative eleemnt
							savecounter = counter;
							counter = 0;
						}
						else
						{
							tt = tt->pastevent;
							if(tt==NULL)
							{
								c=0;
							}
							else
							{
								c = tt->timestamp;
							}

							counter--;
						}
		
					} // while counter>0 inside loop ends - we have found the first negative elelemnt of the queueu if any 

					if(tt==NULL || savecounter==0)
					{
						cout<<"********************************************************"<<endl<<"no need to annihilate here any more since no event with negative timestamp found anymore"<<endl<<"********************************************************"<<endl;
						//cout<<"no need to annihilate any further"<<endl;
						//cout<<"********************************************************"<<endl;
						counter = -10;
						//return;
					}

					else
					{

						if(savecounter>1)
						{ //
							subcounter = savecounter-1;

							nn = tt->pastevent;

							while(subcounter>0)
							{
								if(c+ nn->timestamp == 0)
								{
									//ip4Q.deletethis(tt);

									ip4Q.deletethis(nn);
									ip4Q.deletethis(tt);

									success1 =1;
									subcounter =0;
									cout<<"********************************************************"<<endl<<"Annihilation taking place in queue"<<endl<<"********************************************************"<<endl;
									//cout<<"Annihilation taking place in queue"<<endl;
									//cout<<"********************************************************"<<endl;
								}
								else
								{
									nn = nn->pastevent;	
									subcounter--;
								}

							}
						}

						if(success1==0)
						{
							//search in input queue unsuccessful 
							// search in stack now

							//s = state4stack.Size();
							stacksize = state4stack.Size();

							cc=stacksize;

							if(stacksize>0)
							{
								anticheck = state4stack.top;
								//////////////////////
								while(cc>0)
								{
									if(anticheck->timestamp + c == 0)
									{
										cout<<"********************************************************"<<endl<<"Annihilation taking place in stack"<<endl<<"********************************************************"<<endl;
										//cout<<"Annihilation taking place in stack"<<endl;
										//cout<<"********************************************************"<<endl;
										state4stack.deletethis(anticheck);
										ip4Q.deletethis(tt);
										//cc = state4stack.Size()+3;
										cc=0;
										success1=1;
									}
									else
									{
										cc=cc-1;
										anticheck=anticheck->pastevent;
									}

								} // while cc loop ends
								////////////////////////

								if(success1 ==0)
								{
									cout<<"********************************************************"<<endl<<"BIG ZOL"<<endl<<"********************************************************"<<endl;
									//cout<<"BIG ZOL"<<endl;
									//cout<<"********************************************************"<<endl;

									emergency =1;

									cin>>kya;

									//return;
								}


							} // if stacksize>o loop ends

							else
							{
								cout<<"********************************************************"<<endl<<"BIG PAIN"<<endl<<"********************************************************"<<endl;
								//cout<<"BIG PAIN"<<endl;
								//cout<<"********************************************************"<<endl;
								//return;

								cin>>kya;

								emergency =1;
							}




						} // loop of if success1 == 0 ends

						if (emergency ==0)
						{
							counter = ip4Q.Size();
						}
						else
						{
							counter = -12;
						}

	
					} // end of else loop corresponding to if NULL


				}//loop corresponding to going through differetn negative elements of the queuue

				//////////annihilate routine ends////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Thread::Sleep(200); 
				//anticheck = ip4Q.front;

				//c = ip4Q.rear->timestamp;
				//cc = 0;
				//int success1 =0;

			/*
				if(c<0)
				{

					while(cc<ip4Q.Size())
					{
						if(anticheck->timestamp + c == 0)
						{
							cout<<"Annihilation taking place in queue"<<endl;
							ip4Q.deletethis(anticheck);
							ip4Q.deletethis(ip4Q.rear);
							cc = ip4Q.Size()+3;
							success1=1;
						}
						else
						{
							cc=cc+1;
							anticheck=anticheck->nextevent;
						}

					} // while cc loop ends

					if(success1==0)
					{
						//search in input queue unsuccessful 
						// search in stack now

						s = state4stack.Size();
						cc=0;

						if(s>0)
						{
							anticheck = state4stack.top;
							//////////////////////
							while(cc<state4stack.Size())
							{
								if(anticheck->timestamp + c == 0)
								{
									cout<<"Annihilation taking place in stack"<<endl;
									state4stack.deletethis(anticheck);
									ip4Q.deletethis(ip4Q.rear);
									cc = state4stack.Size()+3;
									success1=1;
								}
								else
								{
									cc=cc+1;
									anticheck=anticheck->pastevent;
								}

							} // while cc loop ends
					////////////////////////

							if(success1 ==0)
							{
								cout<<"BIG ZOL"<<endl;


								return;
							}


						} // if s>o loop ends

						else
						{
							cout<<"BIG PAIN"<<endl;
							return;
						}




					} // loop of if success == 0 ends

				}  //loop of if c<0 ends

				*/

			
				if(ip4Q.Size()>0)
				{
					tempevent = ip4Q.Dequeue();

					cout<<"I have found "<<tempevent->timestamp<<endl;

					*increasetimestamp4 = *tempevent;

					increasetimestamp4->timestamp = increasetimestamp4->timestamp + pt4;
					//increasetimestamp4 = ip4Q.Dequeue();

					state4stack.Push(tempevent);



					op4Q.Enqueue(increasetimestamp4);

					ip4Q_Mutex->ReleaseMutex();
				}

				else
				{

					ip4Q_Mutex->ReleaseMutex();
				}



				ip4Q_Mutex->WaitOne();
				cout<<"********************************************************"<<endl;
				cout<<"IP queue of LP4 is"<<" ";
				ip4Q.print();

				cout<<"Stack of LP4 is"<<" ";
				state4stack.print();

				cout<<"********************************************************"<<endl;

				ip4Q_Mutex->ReleaseMutex();


			}//if input queuue size >0 loop ends
		
		}//end of while 1 loop


		
	}// end of LP4


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	static void PP_Two(Object^ name)
	{

		int position = 0, dest = 1, tag = 50, src = 0; MPI_Status  status;
		float buf[2];
				// int MPI_Recv (void message, int count , MPI Datatype datatype, int source, int tag , MPI_Comm comm, MPI_Status status);	 			
				//MPI_Recv(buf, 3, MPI_INT, src, tag, MPI_COMM_WORLD, &status);

		event* incomingevent = new event;

		while(1)
		{
			if(whentoend ==1)
			{
				//cout<<"I am here123"<<endl;
				return;
			}
			MPI_Recv(buf, 2, MPI_FLOAT, src, tag, MPI_COMM_WORLD, &status);

			incomingevent->timestamp = buf[1];

			incomingevent->originalsource = buf[2];
			incomingevent->nextevent = NULL;
			incomingevent->pastevent = NULL;
			//incomingevent->serialnumber = 0;

			cout<<"********************************************************"<<endl<<"PP Two received and forwarded"<<"	"<<buf[1]<<endl<<"********************************************************"<<endl;
			
			//cout<<"PP Two received and forwarded"<<"	"<<buf[1]<<endl;

			//cout<<"********************************************************"<<endl;


			/*
			while(ip4Q.Size()>0)
			{

			}
			*/


			ip4Q_Mutex->WaitOne();

			ip4Q.Enqueue(incomingevent);

			ip4Q_Mutex->ReleaseMutex();


		}

		
		//MPI_Recv(void *buf, 3, MPI_Datatype float, 0, float timestamp,
          //   MPI_Comm comm)

	}



}; // end of logical processor class


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main(int argc, char* argv[])
{

	srand(time(0));
	
	int iProcessRank;
	int iProcessCount;
	MPI_Init(&argc, &argv);  // Initializing the MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &iProcessRank);
	MPI_Comm_size(MPI_COMM_WORLD, &iProcessCount);

	if(iProcessRank == 0)
	{
		//srand(time(0));
		int i=0;
		//int initialheapsize = ;
		float sum=0.0;

		for(i=1; i<initialheapsize+1;i++)   // for loop for building the heap
		{ 
			sum = sum + exponentialrandomvariable(2, 1);
			myheap->insert(sum);
			myheap->print();
		}


		Thread^ newThread_Logical_Process_One = gcnew 
			Thread(gcnew ParameterizedThreadStart(&LogicalProcessor::Lp_One));
		Thread^ newThread_Logical_Process_Two = gcnew 
			Thread(gcnew ParameterizedThreadStart(&LogicalProcessor::Lp_Two));
		Thread^ newThread_Logical_Process_Three = gcnew 
			Thread(gcnew ParameterizedThreadStart(&LogicalProcessor::Lp_Three));

		newThread_Logical_Process_One->Start("Lp_One");
		newThread_Logical_Process_Two->Start("Lp_Two");
		newThread_Logical_Process_Three->Start("Lp_Three");


		newThread_Logical_Process_One->Join();
		newThread_Logical_Process_Two->Join();
		newThread_Logical_Process_Three->Join();
	}
	else
	{
		Thread^ newThread_Logical_Process_Four = gcnew 
			Thread(gcnew ParameterizedThreadStart(&LogicalProcessor::Lp_Four));
		Thread^ newThread_Physical_Process_Two = gcnew 
			Thread(gcnew ParameterizedThreadStart(&LogicalProcessor::PP_Two));
		

		newThread_Physical_Process_Two->Start("PP_Two");
		newThread_Logical_Process_Four->Start("LP_Four");

		newThread_Logical_Process_Four->Join();
		newThread_Physical_Process_Two->Join();
	}
	MPI_Finalize();

	cout<<endl<<"All events have been processed. Simulation is over. Thank you."<<endl;
	delete myheap;
	getch();
}
