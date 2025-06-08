#ifndef BORROWCOMMAND_H
#define BORROWCOMMAND_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <string>

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "command.h"
#include "commandFactory.h"

/// ---------------------------------------------------------------------------
/// BorrowCommand
///
/// Represents the action of a customer borrowing a movie.
/// Checks inventory, updates stock, and records the transaction.
/// ---------------------------------------------------------------------------
class BorrowCommand : public Command {
private:
  int customerID;       ///< ID of the customer borrowing the movie
  std::string movieKey; ///< Unique key identifying the movie

public:
  /// Constructor
  /// \param id    Customer ID
  /// \param key   Movie key string
  BorrowCommand(int id, std::string key);

  /// execute
  /// Executes the borrow operation:
  ///  1. Validates customer ID
  ///  2. Checks movie availability
  ///  3. Updates stock and customer history
  void execute(MovieStore &store, CustomerDB &customers) override;

  /// Destructor (default behavior)
  ~BorrowCommand() override {}
};

#endif // BORROWCOMMAND_H
