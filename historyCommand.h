#ifndef HISTORYCOMMAND_H
#define HISTORYCOMMAND_H

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "command.h"
#include "commandFactory.h"

/// ---------------------------------------------------------------------------
/// HistoryCommand
///
/// A Command subclass that retrieves and displays the transaction history
/// for a specified customer. Inherits the execute interface for uniformity.
/// ---------------------------------------------------------------------------
class HistoryCommand : public Command {
private:
  int customerID; ///< ID of the customer whose history will be shown

public:
  /// Constructor
  /// \param id  Four‐digit customer ID
  explicit HistoryCommand(int id);

  /// execute
  /// Fetches the Customer by ID from CustomerDB and calls displayHistory().
  /// Prints an error if the ID is invalid.
  /// \param store      Unused (required by base interface)
  /// \param customers  Database of customers for lookup
  void execute(MovieStore &store, CustomerDB &customers) override;

  /// Destructor
  /// Default virtual destructor to clean up via base class pointer.
  ~HistoryCommand() override {}
};

#endif // HISTORYCOMMAND_H
