// -----------------------------------------------------------------------------
// historyCommand.cpp
// Implementation of the HistoryCommand and its factory.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cout, std::cerr
#include <istream>  // for std::istream

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "customer.h"
#include "customerDb.h"
#include "historyCommand.h"

//------------------------------------------------------------------------------
// HistoryCommand
//------------------------------------------------------------------------------

// Constructor
// Initializes a HistoryCommand with a customer ID.
HistoryCommand::HistoryCommand(int id) : customerID(id) {}

// execute()
// Retrieves and displays the transaction history for the specified customer.
// Prints error if the customer ID is invalid.
//-----------------------------------------------------------------------------
void HistoryCommand::execute(MovieStore &store, CustomerDB &customers) {
  (void)store; // Unused parameter

  // Look up the customer
  Customer *customer = customers.getCustomer(customerID);
  if (customer == nullptr) {
    std::cerr << "Invalid customer ID " << customerID << "\n";
    return;
  }

  // Display history with separators
  std::cout << "==========================\n";
  customer->displayHistory();
  std::cout << "==========================\n";
}

//------------------------------------------------------------------------------
// HistoryCommandFactory (self-registering)
//------------------------------------------------------------------------------

// Registers the 'H' command code with the factory at static initialization.
class HistoryCommandFactory : public CommandFactory {
public:
  HistoryCommandFactory() { registerType('H', this); }

  // createCommand()
  // Parses the customer ID from the input stream and returns a new
  // HistoryCommand.
  Command *createCommand(std::istream &input) const override {
    int customerID;
    input >> customerID;
    return new HistoryCommand(customerID);
  }
};

// Static instance to register the HistoryCommandFactory.
static HistoryCommandFactory registerHistory;
