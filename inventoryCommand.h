#ifndef INVENTORYCOMMAND_H
#define INVENTORYCOMMAND_H

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "command.h"
#include "commandFactory.h"

/// ---------------------------------------------------------------------------
/// InventoryCommand
///
/// A Command subclass that displays the complete movie inventory.
/// Implements the execute interface to print inventory to stdout.
/// ---------------------------------------------------------------------------
class InventoryCommand : public Command {
public:
  /// Constructor
  /// No parameters required.
  InventoryCommand();

  /// execute
  /// Prints a separator and "Displaying Inventory..." header,
  /// then calls MovieStore::displayInventory().
  /// \param store      The movie inventory to display
  /// \param customers  Unused (required by base interface)
  void execute(MovieStore &store, CustomerDB &customers) override;

  /// Destructor
  /// Virtual to support proper cleanup via base-class pointers.
  ~InventoryCommand() override {}
};

#endif // INVENTORYCOMMAND_H
