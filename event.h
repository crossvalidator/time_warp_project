// this is the header file for an event
// in my code, an event is the smallest unit
// it essentially represents a message bundle
// throughout the code, i will be using these events
// LPs will pass events to each other


class event {
public:
  float timestamp;
  int originalsource;
  event * nextevent;
  event * pastevent;
 
  
} ;


