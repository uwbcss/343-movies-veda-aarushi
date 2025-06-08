#ifndef CUSTOMERDB_H
#define CUSTOMERDB_H

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "customer.h"
#include "hashTable.h"

/// ---------------------------------------------------------------------------
/// CustomerDB
///
/// Manages the collection of Customer objects using a custom hash table
/// for O(1) lookup by customer ID. Responsible for adding, retrieving,
/// and cleaning up Customer instances.
/// ---------------------------------------------------------------------------
class CustomerDB {
private:
  HashTable<int, Customer *> customers; ///< Map from customer ID to Customer*

public:
  /// Destructor
  /// Frees all Customer* entries in the hash table to prevent memory leaks.
  ~CustomerDB();

  /// addCustomer
  /// Inserts a new Customer into the database.
  /// \param c  Pointer to a dynamically allocated Customer
  void addCustomer(Customer *c);

  /// getCustomer
  /// Retrieves a Customer by ID, or nullptr if not found.
  /// \param id  Four‐digit customer ID
  /// \return Pointer to Customer or nullptr
  Customer *getCustomer(int id) const;
};

#endif // CUSTOMERDB_H
