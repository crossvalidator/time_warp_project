// stackclass.h
// this is the header file for stackclass.cpp
// it declares stackclass as a class
// it essentially represents a stack data strcture
// the member function names are self explanatory





#ifndef event_h
#define event_h
#include "event.h"
#endif 




class stackclass
{  
//private:
public:
   event* top;   // refers to the top pf teh stack
   //event* rear;
   int count;    // refers to the size of the stack

//public:
   stackclass();
   void Push(event* present);
   event* Pop();
   event* Top();
   int Size();
   bool isEmpty();
   void print();
   void deletethis(event* deleteevent);
};
