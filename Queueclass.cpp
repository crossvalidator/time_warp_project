//this is the implementation of Queue with event class and it works
#include "Queueclass.h"

#include <iostream>
//#include "event.h"

using namespace std;

class QueueisEmptyError
{
public:
   QueueisEmptyError()
   {
       cout << "Queue is empty error" << endl;
   }
};


   Queue::Queue()
   {
       front = NULL;
       rear = NULL;
       count = 0;
   }      
 
   void Queue::Enqueue(event* present)
   {
       // Create a new node
       event* tmp = new event();
       tmp->timestamp= present->timestamp;
       tmp->originalsource = present->originalsource;
	   tmp->nextevent = NULL;
	   tmp->pastevent = rear;
	   //tmp->serialnumber = present->serialnumber;

       if ( isEmpty() ) {
           // Add the first element
           front = rear = tmp;
       }
       else {
           // Append to the list
           rear->nextevent = tmp;
           rear = tmp;
		  // cout<<"haha"<<rear->timestamp;
       }

       count++;
   }      

   event* Queue::Dequeue()
   {          
       if ( isEmpty() )
           throw new QueueisEmptyError();

       //int ret = front->data;
       //Node* tmp = front;

	   /* this works -- the next code snippet works too gosh
	   event* ret = new event;

	   ret->timestamp = front->timestamp;
	   ret->originalsource = front->originalsource;
	   ret->nextevent = front->nextevent;
	   ret->pastevent = front->pastevent;
	   ret->serialnumber = front->serialnumber;
	   */

	   event* ret = new event;

	   *ret = *front;

	   //cout <<ret->timestamp;
	   event* tmp = front;
	   //cout<<tmp->timestamp;

       // Move the front pointer to next node
       front = front->nextevent;
	   //cout<<front->timestamp;

	   if(front ==NULL)
	   {
		   rear = NULL;
		   count--;
		   return ret;
	   }

	    front->pastevent = NULL;
        count--;
       delete tmp;
       return ret;   
   }      
 
   event* Queue::Front()
   {          
       if ( isEmpty() )
           throw new QueueisEmptyError();

       //return front->data;
	   return front;

   }
 
   int Queue::Size()
   {
       return count;
   }

   bool Queue::isEmpty()
   {
       return count == 0 ? true : false;
   }


   void Queue::print()
{
   // vector<int>::iterator pos = heap.begin();
	//vector<float>::iterator pos = heap.begin();
   // cout << "Heap = ";
   // while ( pos != heap.end() ) {
     //   cout << *pos << " ";
       // ++pos;
   // }
    //cout << endl;

	if(count==0)
	{
			cout<<"Empty"<<endl;
			return;
	}

	event* tt = new event;
	tt = front;

	if(tt == NULL)
	{
		cout<<"Empty"<<endl;
	}

	for(int kk=1; kk<count+1;kk++)
	{
		cout<<tt->timestamp<<" ";
		tt = tt->nextevent;
	}
	cout<<endl;


	return;


}

   void Queue::deletethis(event* deleteevent)
   {
	   // ideally i should search for this deleteevent - 
	   // but i will assume that the user has already found it

	   if(deleteevent->nextevent==NULL  && deleteevent->pastevent==NULL )
	   {
			front = NULL;
			rear = NULL;
			count=0;
			delete deleteevent;
			return;
	   }
	   
	   if(deleteevent->nextevent != NULL && deleteevent->pastevent==NULL)
	   {
		  front = front->nextevent;
		  front->pastevent=NULL;
		  delete deleteevent;
		   count--;


		   //event* ret = new event;

	   //*ret = *front;

	   //cout <<ret->timestamp;
	 //  event* tmp = front;
	   //cout<<tmp->timestamp;

       // Move the front pointer to next node
      // front = front->nextevent;
	   //cout<<front->timestamp;
       //count--;
       //delete tmp;
       //return ret;






		   return;
	   }
			 
	   if(deleteevent->nextevent == NULL && deleteevent->pastevent != NULL)
	   {
		   rear = rear->pastevent;
		   rear->nextevent = NULL;
		   delete deleteevent;
		   count--;
		   return;
	   }

	   if(deleteevent->nextevent != NULL && deleteevent->pastevent != NULL)
	   {
		   deleteevent->pastevent->nextevent = deleteevent->nextevent;
		   deleteevent->nextevent->pastevent = deleteevent->pastevent;
		   delete deleteevent;
		   count--;
		   return;
	   }




   }




