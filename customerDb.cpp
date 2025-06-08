// customerDb.cpp
// Definitions for CustomerDB declared in customerDb.h

#include "customerDb.h"
#include <vector>

// Destructor
// Deletes all Customer* stored in the hash table to avoid leaks.
CustomerDB::~CustomerDB() {
  std::vector<Customer *> allCustomers;
  customers.getAllValues(allCustomers);
  for (Customer *c : allCustomers) {
    delete c;
  }
}

// addCustomer
// Inserts a new Customer pointer into the hash table, keyed by their ID.
void CustomerDB::addCustomer(Customer *c) {
  if (c != nullptr) {
    customers.insert(c->getID(), c);
  }
}

// getCustomer
// Looks up a Customer by ID. Returns nullptr if not found.
Customer *CustomerDB::getCustomer(int id) const {
  Customer *result = nullptr;
  if (customers.find(id, result)) {
    return result;
  }
  return nullptr;
}
