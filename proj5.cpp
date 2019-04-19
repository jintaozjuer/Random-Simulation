#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "constants.h"
#include "random.h"
#include "SimulationClass.h"
#include "operator.h"

//programmmer: Tao Jin
//Date: April 8 2018
//Purpose: Design and develop an event-driven simulation 
//on the operation of a park.

int main(int argc, char* argv[])
{
  //checking the command arguments
  if (argc != CORRECT_CLA_NUM) {
    cout << "Usage: " << "./parkSimulation.exe "
      << "<simParams.txt>" << endl;
    return(1);
  }

  //checking whether the file can be opened
  string filename = argv[1];
  ifstream inFile;
  inFile.open(filename.c_str());
  if (inFile.fail())
  {
    cout << "Error: Unable to open the file" << endl;
    cout << "Please check your filename and try again" << endl;
    return(2);    
  }
  inFile.close();

  SimulationClass theSim;
  bool isValidParas;
  isValidParas = theSim.readParas(filename);
  if (!isValidParas) 
  {
    cout << "Invalid simulation parameters, "
      << "so the simulation fails" << endl;
    return(3);
  }
  else 
  {
    cout << "Valid simulation parameters, " <<
      "and file reads successfully" << endl;
  }

  int seed;
  cout << "Please enter a seed(integer)" << endl;
  cin >> seed;
  setSeed(seed);
  cout << "Simulation begins" << endl;
  cout << endl;

  EventClass riderEvent;
  EventClass trainEvent;
  EventClass currentEvent;
  cout << "Time:0 -- Determine the first rider "
    << "and the first train" << endl;
  riderEvent = theSim.generateNewRider();
  trainEvent = theSim.generateNewTrain();
  bool nonEmptyLine = true;
  bool notClosingTime = true;
  int closingTime;
  closingTime = theSim.getClosingTime();
  if (closingTime > riderEvent.getTime())
  {
    theSim.insertEvent(riderEvent);
    theSim.insertEvent(trainEvent);
    theSim.printEventList();
    theSim.printRidersInLine();
    while (notClosingTime || nonEmptyLine)
    {
      currentEvent = theSim.handleEvent();
      if (currentEvent.getType() == TRAIN_ARRI)
      {
        theSim.fillTrain();
        if (theSim.checkRiderLeft() || notClosingTime)
        {
          trainEvent = theSim.generateNewTrain();
          theSim.insertEvent(trainEvent);
        }
        else
        {
          nonEmptyLine = false;
        }
      }
      else
      {
        theSim.waitInLine(currentEvent);
        riderEvent = theSim.generateNewRider();
        if (riderEvent.getTime() <= closingTime) 
        {
          theSim.insertEvent(riderEvent);
        }
        else 
        {
          notClosingTime = false;
        } 
      }
      theSim.printEventList();
      theSim.printRidersInLine();
    }
    cout << endl;
    cout << "SIMULATION ENDS" << endl;
    cout << "Now print simulation statistics:" << endl;
    theSim.printSimulationStatistics();
  }
  else 
  {
    cout << "Simulation fails because the first rider "
      << "comes after the closing time" << endl;
  }
  system("pause");
  return(0);
}