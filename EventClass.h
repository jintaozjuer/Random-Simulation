#ifndef _EVENTCLASS_H_
#define _EVENTCLASS_H_

class EventClass
{
  private:
    int time;
    int type;
    int order;

  public:
    //innitialize attributes to be 0
    EventClass();

    //set the attributes to be the desired
    EventClass(int inTime, int inType, int inOrder);
    
    //access to time
    const int getTime() const;

    //access to type
    const int getType() const;

    //access to order;
    const int getOrder() const;
    
    //overload ">="
    bool operator>=(const EventClass &rhs) const;

};

#endif 
