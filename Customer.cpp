#include <iostream>
#include <sstream>
using namespace std;
#include "Customer.h"

Customer::Customer() {
  name = "Unknown";
  address = "Unknown";
  phone = "Unknown";
}

Customer::Customer(string n, string a, string p) {
  name = n;
  address = a;
  phone = p;
}


//print functions
string Customer::customerInfo() const {
  stringstream ss;
  ss << "..." << endl;
  ss << "Name: " << name << endl;
  ss << "Address: " << address << endl;
  ss << "Phone: " << phone << endl;
  ss << "..." << endl;
  return ss.str();
}


//set functions
void Customer::setName(string n) {
  name = n;
}
void Customer::setAddress(string a) {
  address = a;
}
void Customer::setPhone(string p) {
  phone = p;
}


//get functions
string Customer::getName() const {
  return name;
}

string Customer::getAddress() const {
  return address;
}

string Customer::getPhone() const {
  return phone;
}