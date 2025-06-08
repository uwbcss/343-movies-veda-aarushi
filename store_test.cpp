/**
 * Testing ass4 movie store functions
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

#include "command.h"
#include "commandFactory.h"
#include "customer.h"
#include "customerDb.h"
#include "movieFactory.h"
#include "movieStore.h"

using namespace std;

// Helper: load all movies (reports unknown types internally)
void loadMovies(MovieStore &store) {
  ifstream file("data4movies.txt");
  assert(file.is_open() && "Failed to open data4movies.txt");
  char type;
  while (file >> type) {
    file.ignore(); // skip comma
    Movie *moviePtr = MovieFactory::create(type, file);
    if (moviePtr != nullptr) {
      store.addMovie(moviePtr);
    } else {
      // skip the rest of this bad line
      file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

// Helper: load all customers
void loadCustomers(CustomerDB &db) {
  ifstream file("data4customers.txt");
  assert(file.is_open() && "Failed to open data4customers.txt");
  int id;
  string lastName;
  string firstName;
  while (file >> id >> lastName >> firstName) {
    db.addCustomer(new Customer(id, firstName, lastName));
  }
}

// Helper: process all commands (I, H, B, R, etc.)
void processCommands(MovieStore &store, CustomerDB &db) {
  ifstream file("data4commands.txt");
  assert(file.is_open() && "Failed to open data4commands.txt");
  char code;
  while (file >> code) {
    Command *cmdPtr = CommandFactory::create(code, file);
    if (cmdPtr != nullptr) {
      cmdPtr->execute(store, db);
      delete cmdPtr;
    } else {
      // skip bad command line
      file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

// Test 1: verify sequence of command codes in testcommands-1.txt
void testStore1() {
  cout << "Start testStore1" << endl;
  const string cmdFile = "testcommands-1.txt";
  ifstream fs(cmdFile);
  assert(fs.is_open() && "Failed to open testcommands-1.txt");
  stringstream out;
  char commandType;
  string discardLine;
  while (fs >> commandType) {
    out << commandType;
    getline(fs, discardLine);
  }
  fs.close();
  const string expected = "IHHBRIBBIH";
  assert(out.str() == expected && "testStore1: unexpected command sequence");
  cout << "End testStore1" << endl;
}

// Test 2: load movies and display initial inventory
void testStore2() {
  cout << "Start testStore2" << endl;
  MovieStore store;
  loadMovies(store);
  store.displayInventory();
  cout << "End testStore2" << endl;
}

// Test 3: full integration run (movies + customers + commands)
void testStoreFinal() {
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;
  MovieStore store;
  CustomerDB db;
  loadMovies(store);
  loadCustomers(db);
  processCommands(store, db);
  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
}

// Called by your existing main.cpp
void testAll() {
  testStore1();
  testStore2();
  testStoreFinal();
}
