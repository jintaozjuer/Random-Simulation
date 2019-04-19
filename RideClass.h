#ifndef _RIDECLASS_H_
#define _RIDECLASS_H_

#include <iostream>
#include <string>
using namespace std;

class RideClass
{
  private:
    int numOfSeats;
    string nameOfAttraction;

  public:
    //innitialize the attributes to be 20 and "Space Mountain"
    RideClass();

    //initialize the attributes as desired
    RideClass(int inNum, string inName);
    
    //access to number of seats
    int getNumOfSeats();

    //access to attraction name
    string getNameOfAttraction();
    
    //modify number of seats
    void changeNumOfSeats(int inNum);
    
    //modify attraction name
    void changeNameOfAttraction(string inString);

};

#endif 