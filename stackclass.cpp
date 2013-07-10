#include "stackclass.h"
#include <iostream>
using namespace std;

class StackUnderFlowException 
{
    public:
        StackUnderFlowException() 
        {
            cout << "Stack underflow" << endl;
        }
};




          
    stackclass:: stackclass() 
    {            
          top = NULL;
          count = 0;        
    }        
    
    void stackclass::Push(event* present)
    { 
        event* temp = new event();
        temp->timestamp = present->timestamp;
		temp->originalsource = present->originalsource;
	    temp->nextevent = NULL;
	    temp->pastevent = top;
	    //temp->serialnumber = present->serialnumber;
        //temp->link = top;

		
       if ( isEmpty() ) {
           // Add the first element
           top= temp;
       }
       else {
           // Append to the list
           top->nextevent = temp;
           top = temp;
		  // cout<<"haha"<<rear->timestamp;
       }

        //top = temp;     
        count++;          
    }        
            
    event* stackclass:: Pop()
    {            
        if ( top == NULL ) 
            {            
                throw new StackUnderFlowException();            
            }        


		 event* ret = new event;

	     *ret = *top;
		 event* tmp = top;
	   
		 top = top->pastevent;

		 if(top != NULL)
		 {
			 top->nextevent = NULL;
		 }


	   //cout<<front->timestamp;
         count--;
         delete tmp;
         return ret;   
            
	   /*
	   int ret = top->data;    
            Node* temp = top->link;
            delete top;
            top = temp;
            count--;
            return ret;   
			*/

    }        
    
    event* stackclass:: Top() 
    {            
        //return top->data;        
		if ( isEmpty() )
           throw new StackUnderFlowException();

       //return front->data;
	   return top;
    }
    
    int stackclass:: Size() 
    {
        return count;
    }
    
    bool stackclass:: isEmpty() 
    {
        return ( top == NULL ) ? true : false;
    }


	void stackclass::print()
	{
		if(count==0)
		{
			cout<<"Empty"<<endl;
			return;
		}

		event* gg = new event;

		gg = top;
		for(int kk=1; kk<count+1;kk++)
		{
			cout<<gg->timestamp<<" ";
			gg = gg->pastevent;
		}
		cout<<endl;


		return;
	}



	void stackclass::deletethis(event* deleteevent)
	{
		if(deleteevent->nextevent==NULL  && deleteevent->pastevent==NULL )
	   {
			//front = NULL;
			//rear = NULL;
		    top = NULL;
			count=0;
			delete deleteevent;
			return;
	   }

		if(deleteevent->nextevent != NULL && deleteevent->pastevent==NULL)
	   {
		   //front = front->nextevent;
		   //front->pastevet=NULL;
		   deleteevent->nextevent->pastevent = NULL;
		   delete deleteevent;
		   count--;
		   return;
	   }

		if(deleteevent->nextevent == NULL && deleteevent->pastevent != NULL)
	   {
		   //rear = rear->pastevent;
		   //rear->nextevent = NULL;
		   top = top->pastevent;
		   top->nextevent=NULL;
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

/*
int main()
{    
    ListStack s; 
    try {
        if ( s.isEmpty() ) 
            {
            cout << "Stack is empty" << endl;    
            }
        // Push elements    
        s.Push(100);    
        s.Push(200);    
        // Size of stack
        cout << "Size of stack = " << s.Size() << endl;
        // Top element    
        cout << s.Top() << endl;    
        // Pop element    
        cout << s.Pop() << endl;
      // Pop element    
        cout << s.Pop() << endl;
      // Pop element    
        cout << s.Pop() << endl;
    }
    catch (...) {
        cout << "Some exception occured" << endl;
    }
}

*/

/*
OUTPUT:-
Stack is empty
Size of stack = 2
200
200
100
Stack underflow
Some exception occured
*/
