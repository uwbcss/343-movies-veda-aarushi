#include "historyCmd.h"
#include "classics.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
HistoryCmd::HistoryCmd() : cmd('H') {}

// helper to History movie

/*
  Print customer's transaction history
*/
void HistoryCmd::execute(MovieStore &store, const vector<string> &vs) const {
  // vs[0] = cmd id type genre
  char cmd;
  int id;
  istringstream iss(vs[0]);
  iss >> cmd >> id;

  // Get customerlist
  const auto &customers = store.getCustomerList();

  // Get customer
  Customer *customer = nullptr;
  auto it = customers.find(id);
  if (it != customers.end()) {
    // Save valid customer
    customer = it->second;
  }

  // Print history
  // cout << "Debug: History for " << id << " " << customer->getFullName() <<
  // endl;
  cout << "==========================" << endl;
  cout << "History for " << id << " " << customer->getFullName() << ":" << endl;
  customer->printHistory();
}

#ifndef EXCLUDE_HISTORYCMD

HistoryCmdFactory::HistoryCmdFactory() { registerType('H', this); }

Command *HistoryCmdFactory::makeCommand(const vector<string> & /*vs*/) const {
  return new HistoryCmd();
}

// creating the object registers the type at run time
HistoryCmdFactory theHistoryCmdFactory;

#endif // EXCLUDE_HISTORYCMD