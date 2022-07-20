#include <iostream>
#include <sstream>
using namespace std;
#include "Seat.h"

//this placeholder customer will be used when the seat is not taken by any real customer. 
Customer nullCustomer = Customer();

Seat::Seat() {
  number = 0;
  taken = false;
  customer = nullCustomer;
}

Seat::Seat(int n) {
  number = n;
  taken = false;
  customer = nullCustomer;
}

//print functions

string Seat::basicInfo() const {
  stringstream ss;
  if (taken) {
    ss << "Taken";
  } else {
    ss << "Available";
  }
  return ss.str();
}

string Seat::fullSeatInfo() const {
  stringstream ss;
  if (taken) {
    ss << "Taken" << endl;
    ss << customer.customerInfo();
  } else {
    ss << "Available" << endl;
  }
  return ss.str();
}


//set functions
void Seat::setCustomer(Customer c) {
  customer = c;
  taken = true;
}

void Seat::cancelCustomer() {
  customer = nullCustomer;
  taken = false;
}


//get functions
bool Seat::getTaken() const{
  return taken;
}

Customer& Seat::getCustomer() {
  return customer;
}

int Seat::getNumber() const {
  return number;
}

ostream& operator << (ostream& os, Seat s) {
  os << s.fullSeatInfo();
  return os;
}