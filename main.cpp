#include <iostream>
#include <algorithm>
using namespace std;
#include "Flight.h"
#include "Seat.h"
#include "Customer.h"

//below are highlight colours
#define RESET "\033[0m"
#define TEXT "\033[1;94m"   /* White */

Flight* addFlights(int n); //allows user to set up the system with flights & their respective information
void airlineInfo(Flight* airlines, int n); //prints out information relevant to a selected airline
void chooseFlight(Flight* airlines, int n); //allows user to select a flight to proceed with further transactions
void flightOptions(Flight* airlines, int m, int n); //prints out all flights from the airline

int main() {
  cout << TEXT << "Welcome to CB22 Airlines!" << RESET << endl;
  //setting up an array of flights
  string input;
  int n;
  do {
    //this do-while loop error traps the input to ensure that an appropriate integer is entered
    cout << "Please enter " << TEXT << "the number of flights " << RESET << "operating." << endl;
    getline(cin, input);
    try {
      n = stoi(input);
      if (n > 0) {
        break;
      } else {
        cout << "Invalid input." << endl;
      }
    } catch (exception& e) {
      cout << "Invalid input." << endl;
    }
  } while (true);

  //pointer for Flight object, to store an array of flights
  Flight* airlines;
  airlines = addFlights(n);
  chooseFlight(airlines, n);
}

Flight* addFlights(int n) {
  //an array is created to contain all flight objects. 
  Flight* airlines = new Flight[n];
  for (int i=0; i<n; i++) {
    cout << "Please enter the " << TEXT << "origin" << RESET << " for flight #" << i+1 << ": ";
    string origin, destination;
    cin >> origin;
    cout << "Please enter the " << TEXT << "destination" << RESET << " for flight #" << i+1 << ": ";
    cin >> destination;
    airlines[i] = Flight(origin, destination);
  }
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return airlines;
}


void airlineInfo(Flight* airlines, int n) {
  cout << TEXT << "—————————————————————" << endl;
  cout << "CB22 Airlines Flights" << endl;
  cout << "—————————————————————" << RESET << endl;
  for (int i=0; i<n; i++) {
    cout << " - Flight #" << i+1 << " - : " << airlines[i].flightInfo() << endl;
  }
  cout << endl;
}

void chooseFlight(Flight* airlines, int n) {
  airlineInfo(airlines, n);
  string input;
  int m;
  do {
    cout << "Please " << TEXT << "select a flight" << RESET << " to proceed by entering its number from 1-" << n << ". " << endl;
    getline(cin, input);
    try {
      m = stoi(input);
      if (m > 0 && m <= n) {
        break;
      } else {
        cout << "Invalid input." << endl;
      }
    } catch (exception& e) {
      cout << "Invalid input." << endl;
    }
  } while (true);

  m -=1;
  flightOptions(airlines, m, n);
}

void flightOptions(Flight* airlines, int m, int n) {
  cout << endl << TEXT << "- Flight #" << m+1 << " - : " << airlines[m].flightInfo() << RESET << endl << endl;
  if (airlines[m].getOperating()) {
    //if the airline is operating, many options are available for transactions/displays.
    cout << "Please " << TEXT << "choose an option" << RESET << " below by entering the corresponding key." << endl;
    cout 
      << "- 1: Select a seat to make a transaction" << endl
      << "- 2: Print flight information" << endl
      << "- 3: Print seating information" << endl
      << "- 4: Print full flight information" << endl
      << "- 5: Print all customers (alphabetical)" << endl
      << "- 6: Print all customers (seating order)" << endl
      << "- 7: Cancel this flight" << endl 
      << "- Any other key: BACK to flight selection" << endl;

    //the code below takes the user to the transactions/functions that they have indicated through their input.
    string choice;
    getline(cin, choice);
    if (choice == "1") {
      airlines[m].selectSeat();
    } else if (choice == "2") {
      cout << airlines[m].flightInfoFormatted() << endl;
      cout << endl << "Press enter to continue..." << endl;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (choice == "3") {
      cout << TEXT << "———————————————————" << endl;
      cout << "Seating Information" << endl;
      cout << "———————————————————" << RESET << endl;
      cout << airlines[m].seatingInfo();
      cout << endl << "Press enter to continue..." << endl;
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (choice == "4") {
      cout << airlines[m].fullFlightInfo();
      cout << endl << "Press enter to continue..." << endl;
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (choice == "5") {
      cout << airlines[m].customersAlpha();
      cout << endl << "Press enter to continue..." << endl;
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (choice == "6") {
      cout << airlines[m].customersSeat();
      cout << endl << "Press enter to continue..." << endl;
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (choice == "7") {
      airlines[m].cancelFlight();
    } else {
      chooseFlight(airlines, n);
    }

  } else {
    //if the airline has been cancelled, the only possible function to perform should be re-opening the flight. 
    cout << "Please " << TEXT << "choose an option" << RESET << " below by entering the corresponding key." << endl;
    cout 
      << "- 1: Open this flight" << endl
      << "- Any other key: BACK to flight selection" << endl;

    string choice;
    getline(cin, choice);
    if (choice == "1") {
      airlines[m].openFlight();
    } else {
      chooseFlight(airlines, n);
    }
  }

  cout << endl;
  flightOptions(airlines, m, n);
}