#include <iostream>
#include <string>
using namespace std;

#include "RideClass.h"
#include "constants.h"

RideClass::RideClass()
{
  numOfSeats = DEFAULT_SEATS_NUM;
  nameOfAttraction = DEFAULT_ATRRACTION_NAME;
}

RideClass::RideClass(int inNum, string inName)
{
  numOfSeats = inNum;
  nameOfAttraction = inName;
}

int RideClass::getNumOfSeats()
{
  return(numOfSeats);
}

string RideClass::getNameOfAttraction()
{
  return(nameOfAttraction);
}

void RideClass::changeNumOfSeats(int inNum)
{
  numOfSeats = inNum;
}

void RideClass::changeNameOfAttraction(string inString)
{
  nameOfAttraction = inString;
}