// -----------------------------------------------------------------------------
// movieStore.cpp
// Implementation of the MovieStore, which manages inventory and display logic.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <algorithm>     // for std::sort
#include <iostream>      // for std::cout, std::cerr
#include <string>        // for std::string
#include <typeinfo>      // optionally for type checks
#include <unordered_map> // for grouping by type
#include <vector>        // for dynamic arrays

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "movie.h"
#include "movieStore.h"

//------------------------------------------------------------------------------
// MovieStore methods
//------------------------------------------------------------------------------

// Destructor
// Frees all dynamically allocated Movie objects in the inventory.
MovieStore::~MovieStore() {
  for (auto &entry : inventory) {
    delete entry.second;
  }
}

// addMovie
// Adds a Movie to the inventory map by its key. Records the original stock
// count on first insertion for later reference.
void MovieStore::addMovie(Movie *movie) {
  if (movie == nullptr) {
    return;
  }

  const std::string key = movie->getKey();
  inventory[key] = movie;

  if (originalStock.find(key) == originalStock.end()) {
    originalStock[key] = movie->getStock();
  }
}

// getOriginalStock
// Retrieves the stored original stock count for a given movie key.
// Returns -1 if the key is not found.
int MovieStore::getOriginalStock(const std::string &movieKey) const {
  auto it = originalStock.find(movieKey);
  return (it != originalStock.end()) ? it->second : -1;
}

// findMovie
// Looks up a Movie by key in the inventory. If not found, prints an error.
Movie *MovieStore::findMovie(const std::string &key) {
  auto it = inventory.find(key);
  if (it != inventory.end()) {
    return it->second;
  }
  std::cerr << "Invalid Movie: Movie not found in inventory " << key << "\n";
  return nullptr;
}

// displayInventory
// Shows the full inventory, grouped by genre code (in reverse alphabetical
// order), then sorted within each group according to the assignment rules.
// Prints separators before and after.
void MovieStore::displayInventory() const {
  // 1) Collect all movies
  std::vector<Movie *> allMovies;
  allMovies.reserve(inventory.size());
  for (const auto &entry : inventory) {
    allMovies.push_back(entry.second);
  }

  // 2) Group by type code
  std::unordered_map<std::string, std::vector<Movie *>> byType;
  for (Movie *m : allMovies) {
    byType[m->getType()].push_back(m);
  }

  // 3) Extract and sort type codes in descending order
  std::vector<std::string> types;
  types.reserve(byType.size());
  for (const auto &pair : byType) {
    types.push_back(pair.first);
  }
  std::sort(types.rbegin(), types.rend());

  std::cout << "==========================\n";

  // 4) For each type, sort its movies and display them
  for (const auto &type : types) {
    auto movies = byType[type];

    std::sort(movies.begin(), movies.end(), [&](Movie *a, Movie *b) {
      if (type == "C") {
        // Classics: by year ascending, then title
        if (a->getYear() != b->getYear()) {
          return a->getYear() < b->getYear();
        }
        return a->getTitle() < b->getTitle();
      }
      if (type == "D") {
        // Drama: by director ascending, then title
        if (a->getDirector() != b->getDirector()) {
          return a->getDirector() < b->getDirector();
        }
        return a->getTitle() < b->getTitle();
      }
      // Comedy and others: by title ascending
      return a->getTitle() < b->getTitle();
    });

    for (Movie *m : movies) {
      m->display();
    }
  }

  std::cout << "==========================\n";
}
