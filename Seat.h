#include <iostream>
using namespace std;
#include "Customer.h"

#ifndef SEAT_H_
#define SEAT_H_

class Seat {
  private: 
    int number;
    bool taken;
    Customer customer;
  public: 
    Seat();
    Seat(int n);

    //print functions
    string basicInfo() const;
    string fullSeatInfo() const;
//this friend function will print out the seat information upon using the ostream cout << operator. 
    friend ostream& operator << (ostream& os, Seat s);

    //set functions
    void setCustomer(Customer c);
    void cancelCustomer();

    //get functions
    bool getTaken() const;
    Customer& getCustomer();
    int getNumber() const;
    
  
};


#endif