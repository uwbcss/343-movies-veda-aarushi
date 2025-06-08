#ifndef COMMAND_H
#define COMMAND_H

//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
class MovieStore;
class CustomerDB;

/// ---------------------------------------------------------------------------
/// Command
///
/// Abstract base class for all customer/store commands:
///   - BorrowCommand
///   - ReturnCommand
///   - InventoryCommand
///   - HistoryCommand
///
/// Provides a uniform interface (`execute`) and ensures derived classes
/// are cleaned up correctly via a virtual destructor.
/// ---------------------------------------------------------------------------
class Command {
public:
  /// execute
  /// Pure-virtual method to apply this command to the MovieStore and
  /// CustomerDB. \param store      Reference to the central MovieStore
  /// (inventory/actions) \param customers  Reference to the CustomerDB
  /// (history/actions)
  virtual void execute(MovieStore &store, CustomerDB &customers) = 0;

  /// Destructor
  /// Virtual to ensure proper cleanup of derived Command objects.
  virtual ~Command() {}
};

#endif // COMMAND_H
