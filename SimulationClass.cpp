#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "SimulationClass.h"
#include "constants.h"
#include "random.h"


SimulationClass::SimulationClass()
{
  closingTime = INITAIL_SIM_PARA_INT;
  riderArriMean = INITAIL_SIM_PARA_DB;
  riderArriStddev = INITAIL_SIM_PARA_DB;
  carArriMin = INITAIL_SIM_PARA_INT;
  carArriMax = INITAIL_SIM_PARA_INT;
  percOfSFP = INITAIL_SIM_PARA_DB;
  percOfFP = INITAIL_SIM_PARA_DB;
  numOfSFPAdm = INITAIL_SIM_PARA_INT;
  numOfFPAdm = INITAIL_SIM_PARA_INT;
  currentTime = SIM_START_TIME;
  numOfSFPLine = INIT_NUM_IN_LINE;
  numOfFPLine = INIT_NUM_IN_LINE;
  numOfSTDLine = INIT_NUM_IN_LINE;
  longestSFPLine = INIT_NUM_IN_LINE;
  longestFPLine = INIT_NUM_IN_LINE;
  longestSTDLine = INIT_NUM_IN_LINE;
  currentRiderNum = INIT_NUM_IN_LINE;
  currentTrainNum = INIT_NUM_IN_LINE;
}

bool SimulationClass::checkRiderLeft()
{
  bool noMoreRiders;
  noMoreRiders = (numOfSFPLine == INIT_NUM_IN_LINE) &&
    (numOfFPLine == INIT_NUM_IN_LINE) &&
    (numOfSTDLine == INIT_NUM_IN_LINE);
  return (!noMoreRiders);
}


bool SimulationClass::readParas(string filename)
{
  bool isValid = true;
  ifstream inFile;
  int totalSeatsNum = theRide.getNumOfSeats();

  inFile.open(filename.c_str());

  inFile >> closingTime;
  if (closingTime <= 0) 
  {
    isValid = false;
    cout << "closing time should be greater than 0" << endl;
  }

  inFile >> riderArriMean;
  if (riderArriMean <= 0)
  {
    isValid = false;
    cout << "rider arrival mean should be greater than 0" << endl;
  }

  inFile >> riderArriStddev;
  if (riderArriStddev < 0)
  {
    isValid = false;
    cout << "rider arrival Stddev should be no less than 0" << endl;
  }

  inFile >> carArriMin;
  if (carArriMin < 0)
  {
    isValid = false;
    cout << "car arrival min should be no less than 0" << endl;
  }

  inFile >> carArriMax;
  if (carArriMax <= 0)
  {
    isValid = false;
    cout << "car arrival max should be greater than 0" << endl;
  }
  
  if (carArriMin > carArriMax) 
  {
    isValid = false;
    cout << "car arrival max should be no less than car arrival min" << endl;
  }

  inFile >> percOfSFP;
  if (percOfSFP > MAX_UNI_DISTRIBUTION || percOfSFP < MIN_UNI_DISTRIBUTION) 
  {
    isValid = false;
    cout << "percentage of SFP riders should range from [0,100]" << endl;
  }

  inFile >> percOfFP;
  if (percOfFP > MAX_UNI_DISTRIBUTION || percOfFP < MIN_UNI_DISTRIBUTION)
  {
    isValid = false;
    cout << "percentage of FP riders should range from [0,100]" << endl;
  }

  if ((percOfFP + percOfSFP) > MAX_UNI_DISTRIBUTION) 
  {
    isValid = false;
    cout << "the percentage sum of FP"
      << " and SFP riders can't exeed 100" << endl;
  }

  inFile >> numOfSFPAdm;
  if (numOfSFPAdm > totalSeatsNum || numOfSFPAdm < 0) 
  {
    isValid = false;
    cout << "the num of SFP riders admitted "
      << "should range from [0,max seat num]" << endl;
  }
  
  inFile >> numOfFPAdm;
  if (numOfFPAdm > totalSeatsNum || numOfFPAdm < 0)
  {
    isValid = false;
    cout << "the num of FP riders admitted" <<
      " should range from [0,max seat num]" << endl;
  }

  if ((numOfFPAdm + numOfSFPAdm) > totalSeatsNum)
  {
    isValid = false;
    cout << "the num sum of FP and SFP riders"
      << " can't exeed max seats num" << endl;
  }
  inFile.close();
  return(isValid);
}

int SimulationClass::getClosingTime() 
{
  return(closingTime);
}

EventClass SimulationClass::generateNewRider()
{
  int val;
  int priority;
  string type;
  int comingTime;
  val = getUniform(MIN_UNI_DISTRIBUTION, MAX_UNI_DISTRIBUTION);
  comingTime = getNormal(riderArriMean, riderArriStddev) + currentTime;
  if(comingTime)
  if (val > MIN_UNI_DISTRIBUTION && val <= percOfSFP)
  {
    priority = SFP_RIDER_ARRI;
    type = "SFP";
  }
  else if (val >(MAX_UNI_DISTRIBUTION - percOfFP)
    && val <= MAX_UNI_DISTRIBUTION)
  {
    priority = FP_RIDER_ARRI;
    type = "FP";
  }
  else
  {
    priority = STD_RIDER_ARRI;
    type = "STD";
  }
  currentRiderNum++;
  EventClass riderEvent(comingTime, priority, currentRiderNum);
  cout << "Determine the next rider: No." << currentRiderNum << " rider (";
  cout << type << ") will arrive at " << comingTime << endl;
  if (comingTime > closingTime) 
  {
    cout << "The new rider will come after closing time: Decline" << endl;
  }
  return(riderEvent);
}

EventClass SimulationClass::generateNewTrain()
{
  int comingTime;
  currentTrainNum++;
  comingTime = getUniform(carArriMin, carArriMax) + currentTime;
  EventClass trainEvent(comingTime, TRAIN_ARRI, currentTrainNum);
  cout << "Determine the next train : No." << currentTrainNum
    << " train will arrive at " << comingTime << endl;
  return(trainEvent);
}

void SimulationClass::insertEvent(const EventClass &inEvent)
{
  eventList.insertValue(inEvent);
}

EventClass SimulationClass::handleEvent()
{
  EventClass outEvent;
  string type;
  eventList.removeFront(outEvent);
  currentTime = outEvent.getTime();
  cout << endl;
  cout << "Time: " << currentTime << " -- Handle first element in list: ";
  if (outEvent.getType() == TRAIN_ARRI)
  {
    cout << "No." << outEvent.getOrder() << " train " << "arrives" <<endl;
  }
  else
  {
    if (outEvent.getType() == SFP_RIDER_ARRI)
    {
      type = "SFP";
    }
    else if (outEvent.getType() == FP_RIDER_ARRI)
    {
      type = "FP";
    }
    else if (outEvent.getType() == STD_RIDER_ARRI)
    {
      type = "STD";
    }
    cout << "No." << outEvent.getOrder() << " rider " << "arrives"
      << " priority: " << type << endl;
  }
  return(outEvent);
}

void SimulationClass::fillTrain()
{
  int i;
  int waitingTime;
  int numOfSeats = theRide.getNumOfSeats();
  int numOfSTDGetOn;
  int numOfSFPGetOn;
  int numOfFPGetOn;
  int numOfSTDAdm;
  numOfSTDAdm = numOfSeats - numOfSFPAdm - numOfFPAdm;
  EventClass riderEvent;

  if (numOfSFPAdm <= numOfSFPLine) 
  {
    numOfSFPGetOn = numOfSFPAdm;
    numOfSeats = numOfSeats - numOfSFPAdm;    
  }
  else
  {
    numOfSFPGetOn = numOfSFPLine;
    numOfSeats = numOfSeats - numOfSFPLine;    
  }

  if (numOfFPAdm <= numOfFPLine)
  {
    numOfFPGetOn = numOfFPAdm;
    numOfSeats = numOfSeats - numOfFPAdm;
  }
  else
  {
    numOfFPGetOn = numOfFPLine;
    numOfSeats = numOfSeats - numOfFPLine;
  }

  if (numOfSTDAdm <= numOfSTDLine)
  {
    numOfSTDGetOn = numOfSTDAdm;
    numOfSeats = numOfSeats - numOfSTDAdm;
  }
  else
  {
    numOfSTDGetOn = numOfSTDLine;
    numOfSeats = numOfSeats - numOfSTDLine;    
  }

  if (numOfSeats != 0) 
  {
    if (numOfSeats <= (numOfSFPLine - numOfSFPGetOn))
    {
      numOfSFPGetOn = numOfSFPGetOn + numOfSeats;
      numOfSeats = INIT_NUM_IN_LINE;
    }
    else
    {
      numOfSeats = numOfSeats - (numOfSFPLine - numOfSFPGetOn);
      numOfSFPGetOn = numOfSFPLine;
    }
  }

  if (numOfSeats != 0)
  {
    if (numOfSeats <= (numOfFPLine - numOfFPGetOn))
    {
      numOfFPGetOn = numOfFPGetOn + numOfSeats;
      numOfSeats = INIT_NUM_IN_LINE;
    }
    else
    {
      numOfSeats = numOfSeats - (numOfFPLine - numOfFPGetOn);
      numOfFPGetOn = numOfFPLine;
    }
  }

  if (numOfSeats != 0)
  {
    if (numOfSeats <= (numOfSTDLine - numOfSTDGetOn))
    {
      numOfSTDGetOn = numOfSTDGetOn + numOfSeats;
      numOfSeats = INIT_NUM_IN_LINE;
    }
    else
    {
      numOfSeats = numOfSeats - (numOfSTDLine - numOfSTDGetOn);
      numOfSTDGetOn = numOfSTDLine;
    }
  }

  numOfSFPLine = numOfSFPLine - numOfSFPGetOn;
  numOfFPLine = numOfFPLine - numOfFPGetOn;
  numOfSTDLine = numOfSTDLine - numOfSTDGetOn;

  for (i = 1; i <= numOfSFPGetOn; i++)
  {
    SFPQueue.dequeue(riderEvent);
    waitingTime = currentTime - riderEvent.getTime();
    SFPWaitingTime.insertValue(waitingTime);
    AllWaitingTime.insertValue(waitingTime);
  }

  for (i = 1; i <= numOfFPGetOn; i++)
  {
    FPQueue.dequeue(riderEvent);
    waitingTime = currentTime - riderEvent.getTime();
    FPWaitingTime.insertValue(waitingTime);
    AllWaitingTime.insertValue(waitingTime);
  }

  for (i = 1; i <= numOfSTDGetOn; i++)
  {
    STDQueue.dequeue(riderEvent);
    waitingTime = currentTime - riderEvent.getTime();
    STDWaitingTime.insertValue(waitingTime);
    AllWaitingTime.insertValue(waitingTime);
  }
  cout << "The train is filled up with " << numOfSFPGetOn
    << " SFP riders, " << numOfFPGetOn << " FP riders and "
    << numOfSTDGetOn << " STD riders" << endl;
}

void SimulationClass::waitInLine(EventClass inRiderEvent)
{
  if (inRiderEvent.getTime() <= closingTime) 
  {
    if (inRiderEvent.getType() == STD_RIDER_ARRI)
    {
      STDQueue.enqueue(inRiderEvent);
      numOfSTDLine++;
      if (longestSTDLine <= numOfSTDLine)
      {
        longestSTDLine = numOfSTDLine;
      }
      cout << "No." << inRiderEvent.getOrder()
        << " rider gets into STD line" << endl;
    }
    else if (inRiderEvent.getType() == FP_RIDER_ARRI)
    {
      FPQueue.enqueue(inRiderEvent);
      numOfFPLine++;
      if (longestFPLine <= numOfFPLine)
      {
        longestFPLine = numOfFPLine;
      }
      cout << "No." << inRiderEvent.getOrder()
        << " rider gets into FP line" << endl;
    }
    else
    {
      SFPQueue.enqueue(inRiderEvent);
      numOfSFPLine++;
      if (longestSFPLine <= numOfSFPLine)
      {
        longestSFPLine = numOfSFPLine;
      }
      cout << "No." << inRiderEvent.getOrder()
        << " rider gets into SFP line" << endl;
    }
  }  
}

void SimulationClass::printEventList()
{
  cout << "Current Events Lists:" << endl;
  eventList.printForward();
}

void SimulationClass::printRidersInLine()
{
  cout << "There are: " << endl;
  cout << numOfSFPLine << " riders in the SFP line" << endl;
  cout << numOfFPLine << " riders in the FP line" << endl;
  cout << numOfSTDLine << " riders in the STD line" << endl;
}


double SimulationClass::calWaitingAvg(SortedListClass<int> &inTimeList)
{
  int num;
  double sum = 0;
  double average;
  int outTime = 0;
  num = inTimeList.getNumElems();
  int i;
  if (num == 0)
  {
    average = 0;
  }
  else 
  {
    for (i = 0; i < num; i++)
    {
      inTimeList.getElemAtIndex(i, outTime);
      sum = sum + (double)outTime;
    }
    average = sum / num;
  }
  return(average);
}

double SimulationClass::calWaitingSquareDev(SortedListClass<int>&inTimeList,
  double average)
{
  int num;
  double sum = 0;
  double squareDev;
  int outTime = 0;
  num = inTimeList.getNumElems();
  int i;
  if (num == 0)
  {
    squareDev = 0;
  }
  else 
  {
    for (i = 0; i < num; i++)
    {
      inTimeList.getElemAtIndex(i, outTime);
      sum = sum + ((double)outTime - average) * ((double)outTime - average);
    }
    squareDev = sum / num;
  }
  return(squareDev);
}

double SimulationClass::calWaitingMedian(SortedListClass<int> &inTimeList)
{
  int num;
  double median;
  int val1,val2;
  num = inTimeList.getNumElems();
  if (num == 0) 
  {
    median = 0;
  }
  else 
  {
    if (num % 2 == 0) 
    {
      inTimeList.getElemAtIndex(num / 2 - 1, val1);
      inTimeList.getElemAtIndex(num / 2, val2);
      median = ((double)val1 + (double)val2) / 2;
    }
    else 
    {
      inTimeList.getElemAtIndex((num - 1) / 2, val1);
      median = (double)val1;
    }
  }
  return(median);
}

void SimulationClass::printSimulationStatistics() 
{
  double avgOfSFPWaitingTime;
  double avgOfFPWaitingTime;
  double avgOfSTDWaitingTime;
  double avgOfAllWaitingTime;

  double squareDevOfSFPWaitingTime;
  double squareDevOfFPWaitingTime;
  double squareDevOfSTDWaitingTime;
  double squareDevOfAllWaitingTime;

  double medianOfSFPWaitingTime;
  double medianOfFPWaitingTime;
  double medianOfSTDWaitingTime;
  double medianOfAllWaitingTime;
 
  avgOfSFPWaitingTime = calWaitingAvg(SFPWaitingTime);
  avgOfFPWaitingTime = calWaitingAvg(FPWaitingTime);
  avgOfSTDWaitingTime = calWaitingAvg(STDWaitingTime);
  avgOfAllWaitingTime = calWaitingAvg(AllWaitingTime);

  squareDevOfSFPWaitingTime = calWaitingSquareDev(SFPWaitingTime,
    avgOfSFPWaitingTime);
  squareDevOfFPWaitingTime = calWaitingSquareDev(FPWaitingTime,
    avgOfFPWaitingTime);
  squareDevOfSTDWaitingTime = calWaitingSquareDev(STDWaitingTime,
    avgOfSTDWaitingTime);
  squareDevOfAllWaitingTime = calWaitingSquareDev(AllWaitingTime,
    avgOfAllWaitingTime);

  medianOfSFPWaitingTime = calWaitingMedian(SFPWaitingTime);
  medianOfFPWaitingTime = calWaitingMedian(FPWaitingTime);
  medianOfSTDWaitingTime = calWaitingMedian(STDWaitingTime);
  medianOfAllWaitingTime = calWaitingMedian(AllWaitingTime);
  
  cout << "The longest SFP line is: " << longestSFPLine << endl;
  cout << "The longest FP line is: " << longestFPLine << endl;
  cout << "The longest STD line is: " << longestSTDLine << endl;

  cout << "The average amount of SFP riders waiting time is: "
    << avgOfSFPWaitingTime << endl;
  cout << "The average amount of FP riders waiting time is: "
    << avgOfFPWaitingTime << endl;
  cout << "The average amount of STD riders waiting time is: "
    << avgOfSTDWaitingTime << endl;
  cout << "The average amount of All riders waiting time is: "
    << avgOfAllWaitingTime << endl;

  cout << "The median amount of SFP riders waiting time is: "
    << medianOfSFPWaitingTime << endl;
  cout << "The median amount of FP riders waiting time is: "
    << medianOfFPWaitingTime << endl;
  cout << "The median amount of STD riders waiting time is: "
    << medianOfSTDWaitingTime << endl;
  cout << "The median amount of All riders waiting time is: "
    << medianOfAllWaitingTime << endl;

  cout << "The square deviation of SFP riders waiting time is: "
    << squareDevOfSFPWaitingTime << endl;
  cout << "The square deviation of FP riders waiting time is: "
    << squareDevOfFPWaitingTime << endl;
  cout << "The square deviation of STD riders waiting time is: "
    << squareDevOfSTDWaitingTime << endl;
  cout << "The square deviation of All riders waiting time is: "
    << squareDevOfAllWaitingTime << endl;

  cout << "The total number of SFP riders are: "
    << SFPWaitingTime.getNumElems() << endl;
  cout << "The total number of FP riders are: "
    << FPWaitingTime.getNumElems() << endl;
  cout << "The total number of STD riders are: "
    << STDWaitingTime.getNumElems() << endl;
  cout << "The total number of riders are: "
    << currentRiderNum - 1 << endl;
  cout << "Train runs totally " << currentTrainNum
    << " times" << endl;
}


