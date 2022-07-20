#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
#include "Flight.h"

//below are highlight colours
#define RESET "\033[0m"
#define TEXT "\033[1;94m"   /* White */

Flight::Flight() {
  origin = "Unknown";
  destination = "Unknown";
  operating = true;
  for (int i=0; i<10; i++) {
    flight[i] = Seat(i+1);
  }
}

Flight::Flight(string o, string d) {
  origin = o;
  destination = d;
  operating = true;
  for (int i=0; i<10; i++) {
    flight[i] = Seat(i+1);
  }
}

//set functions


//get functions
Seat& Flight::getSeat(int i) const {
  return flight[i];
}

int Flight::takenSeats() const {
  int takenNum = 0;
  for (int i=0; i<10; i++) {
    if (flight[i].getTaken()) {
      takenNum += 1;
    }
  }
  return takenNum;
}

bool Flight::getOperating() const {
  return operating;
}

ostream& operator << (ostream& os, const Flight f) {
  os << f.flightInfoFormatted();
  return os;
}

//set functions
void Flight::setOrigin(string o) {
  origin = o;
}

void Flight::setDestination(string d) {
  destination = d;
}

void Flight::setOperating(bool b) {
  operating = b;
}

//airline booking methods
string Flight::seatingInfo() const {
  stringstream ss;
  for (int i=0; i<9; i++) {
    ss << "| Seat 0" << i+1 << " |" << ": ";
    ss << flight[i].basicInfo() << endl;
  } 
  ss << "| Seat " << 10 << " |" << ": ";
  ss << flight[9].basicInfo() << endl;
  return ss.str();
}

string Flight::flightInfo() const {
  stringstream ss;
  ss << origin << " to " << destination;
  if (!operating) {
    ss << " (cancelled)";
  }
  return ss.str();
}

string Flight::flightInfoFormatted() const {
  stringstream ss;
  ss << TEXT << "——————————————————" << endl;
  ss << "Flight Information" << endl;
  ss << "——————————————————" << RESET <<endl;
  ss << "Origin: " << origin << endl;
  ss << "Destination: " << destination << endl;
  ss << "Status: ";
  if (!operating) {
    ss << "Cancelled";
  } else {
    ss << "Operating";
  }
  return ss.str();
}

string Flight::fullFlightInfo() const {
  stringstream ss;
  ss << TEXT << "——————————————————" << endl;
  ss << "Flight Information" << endl;
  ss << "——————————————————" << RESET << endl;
  ss << " - " << flightInfo() << " - " << endl << endl;
  for (int i=0; i<9; i++) {
    ss << "| Seat 0" << i+1 << " |" << ": ";
    ss << flight[i].fullSeatInfo() << endl;
  } 
  ss << "| Seat " << 10 << " |" << ": ";
  ss << flight[9].fullSeatInfo() << endl;
  return ss.str();
}

string Flight::customersSeat() const {
  int n = takenSeats();
  Customer *customers = new Customer[n];
  int counter = 0;
  for (int i=0; i<10; i++) {
    if (flight[i].getTaken()) {
      customers[counter] = flight[i].getCustomer();
      counter++;
    }
  }
  stringstream ss;
  ss << TEXT << "————————————————————" << endl;
  ss << "Customer Information" << endl;
  ss << "————————————————————" << RESET << endl;
  for (int i=0; i<n; i++) {
    ss << customers[i].customerInfo() << endl;
  }
  return ss.str();
}

string Flight::customersAlpha() const {
  int n = takenSeats();
  Customer *customers = new Customer[n];
  int counter = 0;
  for (int i=0; i<10; i++) {
    if (flight[i].getTaken()) {
      customers[counter] = flight[i].getCustomer();
      counter++;
    }
  }

  //insertion sort the array in alphabetical order, based on customer names
  int current;
  //the sort iterates through every element of the list from the second onwards
  for (int i=1; i<n; i++) {
    Customer temp;
    current = i;
    //swaps are made downwards, until the current element is (appropriately) larger than the previous
    while (current > 0 && customers[i].getName() < customers[i-1].getName()) {
        temp = customers[i];
        customers[i] = customers[i-1];
        customers[i-1] = temp;
        current --;
    }
  }

  stringstream ss;
  ss << TEXT << "————————————————————" << endl;
  ss << "Customer Information" << endl;
  ss << "————————————————————" << RESET << endl;
  for (int i=0; i<n; i++) {
    ss << customers[i].customerInfo() << endl;
  }
  return ss.str();
}

int Flight::selectSeat() {
  cout << TEXT << "———————————————————" << endl;
  cout << "Seating Information" << endl;
  cout << "———————————————————" << RESET << endl;
  cout << seatingInfo() << endl;
  string input;
  int n;
  do {
    cout << "Please " << TEXT << "select a seat" << RESET << " to make a transaction (by entering the seat number from 1-10), or enter any other key to exit back to the main menu." << endl;
    getline(cin, input);
    try {
      n = stoi(input);
      if (1 <= n && n <= 10) {
         break;
      } else {
          return 1;
      }
    } 
    catch (exception& e) {
      return 1;
    }
  } while (true);
  n -= 1;
  cout << "The status of Seat " << n+1 << " is: " << flight[n].basicInfo() << endl;
  if (flight[n].getTaken()) {
    cancelSeat(n);
  } else {
    buySeat(n);
  }
  return 0;
}

void Flight::buySeat(int n) {
  cout << endl << " - Buy Seat " << n+1 << "? - " << endl << endl;
  cout << "Please " << TEXT << "enter Y" << RESET << " to buy this seat, or enter any other key to exit back to seat selection." << endl;
  string input;
  getline(cin, input);
  transform(input.begin(), input.end(), input.begin(), ::toupper);
  if (input == "Y" || input == "YES") {
    cout << "Please enter customer information for this seat." << endl;
    string name, address, phone;
    cout << TEXT << "Name: " << RESET;
    getline(cin, name);
    cout << TEXT << "Address: " << RESET;
    getline(cin, address);
    cout << TEXT << "Phone: " << RESET;
    getline(cin, phone);
    Customer c = Customer(name, address, phone);
    flight[n].setCustomer(c);
    cout << " - Transaction completed. - " << endl;
  } else {
    selectSeat();
  }
}

void Flight::cancelSeat(int n) {
  cout << " - Cancel Seat " << n+1 << "? - " << endl;
  cout << "Please " << TEXT << "enter Y" << RESET << " to cancel this seat, or enter any other key to exit back to seat selection." << endl;
  string input;
  getline(cin, input);
  transform(input.begin(), input.end(), input.begin(), ::toupper);
  if (input == "Y" || input == "YES") {
    flight[n].cancelCustomer();
    cout << " - Transaction completed. - " << endl;
  } else {
    selectSeat();
  }
}

void Flight::cancelFlight() {
  cout << endl << " - Cancel Flight from " << flightInfo() << "? - " << endl << endl;
  cout << "Please " << TEXT << "enter Y" << RESET << " to cancel this flight, or enter any other key to exit back to the main menu." << endl;
  string input;
  getline(cin, input);
  transform(input.begin(), input.end(), input.begin(), ::toupper);
  if (input == "Y" || input == "YES") {
    cout << endl << " - Flight cancelled. - " << endl << endl;
    cout << "Please " << TEXT << "enter A" << RESET << " to print customer information for this flight in alphabetical order, and enter any other key to print in seating order." << endl;
    string input2;
    getline(cin, input2);
    transform(input2.begin(), input2.end(), input2.begin(), ::toupper);
  if (input2 == "A" || input2 == "ALPHABETICAL" || input2 == "YES") {
    cout << customersAlpha();
  } else {
    cout << customersSeat();
  }
    operating = false;
    for (int i=0; i<10; i++) {
      flight[i].cancelCustomer();
    }
  }
}

void Flight::openFlight() {
  cout << endl << " - Open Flight from " << flightInfo() << "? - " << endl << endl;
  cout << "Please " << TEXT << "enter Y" << RESET << " to open this flight, or enter any other key to exit back to the main menu." << endl;
  string input;
  getline(cin, input);
  transform(input.begin(), input.end(), input.begin(), ::toupper);
  if (input == "Y" || input == "YES") {
    cout << " - Flight opened. - " << endl;
    operating = true;
  }
}