#include <iostream>
using namespace std;
#include "Seat.h"

#ifndef FLIGHT_H_
#define FLIGHT_H_

class Flight {
  private: 
    Seat *flight = new Seat[10];
    string origin;
    string destination;
    bool operating;
  public: 
    Flight();
    Flight(string o, string d);

    //this friend function will print out the flight information upon using the ostream cout << operator. 
    friend ostream& operator << (ostream& os, const Flight f);

    //get functions
    //the following getter function returns a Seat object by reference, such that modifications can be made to the original Seat object rather than a copy. 
    Seat& getSeat(int i) const;
    int takenSeats() const;
    bool getOperating() const;

    //set functions
    void setOrigin(string o);
    void setDestination(string d);
    void setOperating(bool b);

    //airline booking methods
    //these methods are grouped together for simplicity of access. main.cpp will only have to call these overarching methods during runtime, without having to manually access Seat or Customer. 
    string seatingInfo() const;
    string flightInfo() const;
    string flightInfoFormatted() const;
    string fullFlightInfo() const;
    string customersAlpha() const;
    string customersSeat() const;

    int selectSeat();

    void buySeat(int n);
    void cancelSeat(int n);
    void cancelFlight();
    void openFlight();
};

#endif