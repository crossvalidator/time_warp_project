//Queueclass.h
// declares a class Queueclass
// rest is self explanatory


#ifndef event_h
#define event_h
#include "event.h"
#endif 

//#include "event.h"

class Queue
{  

public:
   event* front;
   event* rear;
   int count;


   Queue();
   void Enqueue(event* present);
   event* Dequeue();
   event* Front();
   int Size();
   bool isEmpty();
   void print();
   void deletethis(event* deleteevent);

};
