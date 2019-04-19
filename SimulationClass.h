#ifndef _SIMULATIONCLASS_H_
#define _SIMULATIONCLASS_H_

#include "RideClass.h"
#include "SortedListClass.h"
#include "EventClass.h"
#include "FIFOQueueClass.h"

class SimulationClass
{
  private:
    RideClass theRide;
    SortedListClass<EventClass> eventList;
    FIFOQueueClass<EventClass> SFPQueue;
    FIFOQueueClass<EventClass> FPQueue;
    FIFOQueueClass<EventClass> STDQueue;
    SortedListClass<int> SFPWaitingTime;
    SortedListClass<int> FPWaitingTime;
    SortedListClass<int> STDWaitingTime;
    SortedListClass<int> AllWaitingTime;
    int closingTime;
    double riderArriMean;
    double riderArriStddev;
    int carArriMin;
    int carArriMax;
    double percOfSFP;
    double percOfFP;
    int numOfSFPAdm;
    int numOfFPAdm;
    int currentTime;
    int numOfSFPLine;
    int numOfFPLine;
    int numOfSTDLine;
    int longestSFPLine;
    int longestFPLine;
    int longestSTDLine;
    int currentRiderNum;
    int currentTrainNum;

  public:
    //initialize simulation paras to be 0
    SimulationClass();

    //decide whether there are still riders
    bool checkRiderLeft();

    //reading paras from file, if vail data, return true
    bool readParas(string filename);

    //access to closing time
    int getClosingTime();

    //access to 
    //generate a new rider arrival event
    EventClass generateNewRider();

    //generate a new train arrival event
    EventClass generateNewTrain();

    //insert a new event
    void insertEvent(const EventClass &inEvent);
    
    //handle the latest event
    EventClass handleEvent();

    //riders get on the train
    void fillTrain();
    
    //let the new rider wait in its line by priority level 
    void waitInLine(EventClass inRiderEvent);

    //print event list
    void printEventList();
  
    //print the number of riders in each priority line
    void printRidersInLine();
    
    //calculate waiting time average
    double calWaitingAvg(SortedListClass<int> &inTimeList);

    //calculate waiting time square deviation
    double calWaitingSquareDev(SortedListClass<int> &inTimeList,
      double average);
    
    //calculate waiting time median
    double calWaitingMedian(SortedListClass<int> &inTimeList);
    
    //print simulation statistics
    void printSimulationStatistics();
};
#endif


