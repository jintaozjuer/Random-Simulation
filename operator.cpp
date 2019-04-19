#include <iostream>
#include <string>
using namespace std;

#include "operator.h"
#include "constants.h"
#include "EventClass.h"

ostream& operator<<(ostream &os, const EventClass &rhs)  
{
  string type;
  if (rhs.getType() == TRAIN_ARRI)
  {
    os << "Event: No." << rhs.getOrder() <<
      " train " << "arrives at " << rhs.getTime();
  }
  else
  {
    if (rhs.getType() == SFP_RIDER_ARRI)
    {
      type = "SFP";
    }
    else if (rhs.getType() == FP_RIDER_ARRI)
    {
      type = "FP";
    }
    else if (rhs.getType() == STD_RIDER_ARRI)
    {
      type = "STD";
    }
    os << "Event: No." << rhs.getOrder() << " rider " << "arrives at "
      << rhs.getTime() << " priority: " << type;
  }
  return (os);
}
