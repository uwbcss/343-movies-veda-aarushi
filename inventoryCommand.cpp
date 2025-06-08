// -----------------------------------------------------------------------------
// inventoryCommand.cpp
// Implementation of the InventoryCommand and its factory.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cout
#include <istream>  // for std::istream

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "inventoryCommand.h"
#include "movieStore.h"

//------------------------------------------------------------------------------
// InventoryCommand
//------------------------------------------------------------------------------

// Constructor
// No initialization required.
InventoryCommand::InventoryCommand() {}

// execute()
// Prints a header, then delegates to MovieStore to display all inventory.
//-----------------------------------------------------------------------------
void InventoryCommand::execute(MovieStore &store, CustomerDB &customers) {
  (void)customers; // Unused parameter

  std::cout << "==========================\n"
            << "Displaying Inventory...\n";
  store.displayInventory();
}

//------------------------------------------------------------------------------
// InventoryCommandFactory (self-registering)
//------------------------------------------------------------------------------

// Registers the 'I' command code with the CommandFactory.
class InventoryCommandFactory : public CommandFactory {
public:
  InventoryCommandFactory() { registerType('I', this); }

  // createCommand()
  // Ignores any additional input and returns a new InventoryCommand.
  Command *createCommand(std::istream &input) const override {
    (void)input; // Unused parameter
    return new InventoryCommand();
  }
};

// Static instance to register this factory at program startup.
static InventoryCommandFactory registerInventory;
