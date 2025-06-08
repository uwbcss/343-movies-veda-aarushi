#ifndef MOVIESTORE_H
#define MOVIESTORE_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <string>        // for std::string
#include <unordered_map> // for std::unordered_map

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "movie.h"

/// ---------------------------------------------------------------------------
/// MovieStore
///
/// Manages the collection of Movie instances in the store. Supports adding
/// movies, looking up by key, displaying inventory sorted by genre and
/// the assignment’s criteria, and tracking original stock levels.
/// ---------------------------------------------------------------------------
class MovieStore {
private:
  std::unordered_map<std::string, Movie *> inventory; ///< Map: key → Movie*
  std::unordered_map<std::string, int>
      originalStock; ///< Map: key → initial stock

public:
  /// Destructor
  /// Frees all dynamically allocated Movie objects in the inventory.
  ~MovieStore();

  /// addMovie
  /// Inserts a Movie into the inventory under its unique key. Records the
  /// original stock count on first insertion.
  /// \param movie  Pointer to a dynamically allocated Movie
  void addMovie(Movie *movie);

  /// getInventory
  /// Returns the current map of keys to Movie pointers.
  std::unordered_map<std::string, Movie *> getInventory() const {
    return inventory;
  }

  /// findMovie
  /// Looks up a Movie by its key. If not found, returns nullptr (and prints
  /// an error in the .cpp implementation).
  /// \param key  Unique movie key
  /// \return     Pointer to Movie or nullptr if missing
  Movie *findMovie(const std::string &key);

  /// displayInventory
  /// Prints the full inventory, grouped and sorted by the assignment’s
  /// rules (Comedy by title/year, Drama by director/title, Classics by
  /// date/actor), with separators before and after.
  void displayInventory() const;

  /// getOriginalStock
  /// Retrieves the initial stock count recorded for the given key.
  /// Returns -1 if the key is not found.
  /// \param movieKey  Unique movie key
  /// \return          Original stock count or -1
  int getOriginalStock(const std::string &movieKey) const;
};

#endif // MOVIESTORE_H
