#ifndef HASHTABLE_H
#define HASHTABLE_H

// -----------------------------------------------------------------------------
// hashTable.h
// A simple, generic hash table implementation using separate chaining.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <functional> // for std::hash
#include <iostream>   // for debugging output (display)
#include <iterator>   // for iterator requirements
#include <list>       // for chaining buckets
#include <vector>     // for bucket storage

/// ---------------------------------------------------------------------------
/// HashTable<K, V>
///
/// A basic hash table with separate chaining. Supports insertion, lookup,
/// removal, and simple debugging/display utilities. Uses std::hash<K> and
/// a fixed prime TABLE_SIZE for bucket distribution.
/// ---------------------------------------------------------------------------
template <typename K, typename V> class HashTable {
private:
  static const int TABLE_SIZE = 101; ///< Prime bucket count for distribution

  /// The main bucket array: each index holds a list of key-value pairs
  std::vector<std::list<std::pair<K, V>>> table;

  /// hashFunction
  /// Computes an index in [0, TABLE_SIZE) for a given key
  int hashFunction(const K &key) const {
    std::hash<K> hasher;
    return static_cast<int>(hasher(key) % TABLE_SIZE);
  }

public:
  /// Constructor
  /// Initializes an empty table with TABLE_SIZE buckets.
  HashTable() : table(TABLE_SIZE) {}

  /// insert
  /// Inserts or updates the value associated with `key`.
  /// If the key already exists, its value is overwritten.
  void insert(const K &key, V value) {
    int index = hashFunction(key);
    for (auto &entry : table[index]) {
      if (entry.first == key) {
        entry.second = value;
        return;
      }
    }
    table[index].emplace_back(key, value);
  }

  /// find
  /// Looks up `key`. If found, stores the value in `value` and returns true.
  /// Otherwise, returns false.
  bool find(const K &key, V &value) const {
    int index = hashFunction(key);
    for (const auto &entry : table[index]) {
      if (entry.first == key) {
        value = entry.second;
        return true;
      }
    }
    return false;
  }

  /// remove
  /// Erases the entry for `key` if present. Returns true if removed.
  bool remove(const K &key) {
    int index = hashFunction(key);
    auto &chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
      if (it->first == key) {
        chain.erase(it);
        return true;
      }
    }
    return false;
  }

  /// display
  /// Prints non-empty buckets and their keys for debugging.
  void display() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
      if (!table[i].empty()) {
        std::cout << "Bucket " << i << ": ";
        for (const auto &entry : table[i]) {
          std::cout << "[" << entry.first << "] ";
        }
        std::cout << "\n";
      }
    }
  }

  /// getAllValues
  /// Appends all stored values into the provided vector.
  void getAllValues(std::vector<V> &values) const {
    for (const auto &bucket : table) {
      for (const auto &entry : bucket) {
        values.push_back(entry.second);
      }
    }
  }

  /// getAllKeys
  /// Appends all stored keys into the provided vector.
  void getAllKeys(std::vector<K> &keys) const {
    for (const auto &bucket : table) {
      for (const auto &entry : bucket) {
        keys.push_back(entry.first);
      }
    }
  }
};

#endif // HASHTABLE_H
