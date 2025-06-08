#ifndef CUSTOMER_H
#define CUSTOMER_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <algorithm> // for std::any_of
#include <iostream>  // for std::cout
#include <string>    // for std::string
#include <vector>    // for std::vector

/// ---------------------------------------------------------------------------
/// Customer
///
/// Represents a store customer, tracking their ID, name, and transaction
/// history. Provides methods to add to and display history, as well as check
/// past borrows.
/// ---------------------------------------------------------------------------
class Customer {
private:
  int id;                           ///< Unique customer ID
  std::string firstName;            ///< Customer’s first name
  std::string lastName;             ///< Customer’s last name
  std::vector<std::string> history; ///< Chronological list of transactions

public:
  /// Constructor
  /// \param customerId  Four‐digit customer ID
  /// \param fName       First name
  /// \param lName       Last name
  Customer(int customerId, std::string fName, std::string lName)
      : id(customerId), firstName(std::move(fName)),
        lastName(std::move(lName)) {}

  /// getID
  /// Returns the customer’s ID.
  int getID() const { return id; }

  /// getName
  /// Returns the customer’s full name as "First Last".
  std::string getName() const { return firstName + " " + lastName; }

  /// getHistory
  /// Accessor for the raw transaction history vector.
  const std::vector<std::string> &getHistory() const { return history; }

  /// addTransaction
  /// Appends a new transaction record to the customer’s history.
  /// \param transaction  Formatted string describing the borrow/return.
  void addTransaction(const std::string &transaction) {
    history.push_back(transaction);
  }

  /// displayHistory
  /// Prints the customer’s full transaction history to stdout.
  /// If no transactions exist, prints a “No history” message.
  void displayHistory() const {
    std::cout << "History for " << getName() << ":\n";
    if (history.empty()) {
      std::cout << "No history for " << getName() << "\n";
    } else {
      for (const auto &record : history) {
        std::cout << record << "\n";
      }
    }
  }

  /// hasBorrowed
  /// Checks whether the customer has previously borrowed a movie with
  /// the exact title string.
  /// \param movieTitle  Title to search for, expects format "Borrowed <Title>"
  /// \return true if matching record found, false otherwise
  bool hasBorrowed(const std::string &movieTitle) const {
    const std::string lookup = "Borrowed " + movieTitle;
    return std::any_of(
        history.begin(), history.end(),
        [&lookup](const std::string &record) { return record == lookup; });
  }
};

#endif // CUSTOMER_H
