#include <iostream>
using namespace std;

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
  private: 
    string name;
    string address;
    string phone;
  public: 
    Customer();
    Customer(string n, string a = "Unknown", string p = "Unknown");

    //print functions
    string customerInfo() const;

    //set functions
    void setName(string n);
    void setAddress(string a);
    void setPhone(string p);

    //get functions
    string getName() const;
    string getAddress() const;
    string getPhone() const;
};


#endif