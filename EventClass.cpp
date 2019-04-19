#include <iostream>
using namespace std;

#include "EventClass.h"
#include "constants.h"


EventClass::EventClass()
{
  time = INITAIL_TIME;
  type = INITAIL_TYPE;
  order = FIRST_ORDER;
}

EventClass::EventClass(int inTime, int inType, int inOrder)
{
  time = inTime;
  type = inType;
  order = inOrder;
}

const int EventClass::getTime() const
{
  return(time);
}

const int EventClass::getType() const
{
  return(type);
}

const int EventClass::getOrder() const
{
  return(order);
}

bool EventClass::operator>=(const EventClass &rhs) const
{
  bool noLessThan = false;
  if (time >= rhs.time)
  {
    noLessThan = true;
  }
  return (noLessThan);
}


