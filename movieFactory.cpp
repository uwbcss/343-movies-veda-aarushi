// -----------------------------------------------------------------------------
// movieFactory.cpp
// Implements the self‐registering factory for Movie subclasses.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cerr
#include <istream>  // for std::istream
#include <limits>   // for std::numeric_limits
#include <map>      // for std::map

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "movie.h"
#include "movieFactory.h"

//------------------------------------------------------------------------------
// MovieFactory static registry access
//------------------------------------------------------------------------------

// getRegistry()
// Returns the singleton map from movie code → factory instance.
std::map<char, MovieFactory *> &MovieFactory::getRegistry() {
  static std::map<char, MovieFactory *> registry;
  return registry;
}

//------------------------------------------------------------------------------
// Registration API
//------------------------------------------------------------------------------

// registerType()
// Associates a movie‐code character with a particular factory object.
void MovieFactory::registerType(char type, MovieFactory *factory) {
  getRegistry()[type] = factory;
}

//------------------------------------------------------------------------------
// Factory creation
//------------------------------------------------------------------------------

// create()
// Looks up the factory for the given movie code and delegates to createMovie().
// On unknown codes, logs an error, skips the rest of the line, and returns
// nullptr.
Movie *MovieFactory::create(char type, std::istream &input) {
  auto &registry = getRegistry();
  auto it = registry.find(type);
  if (it == registry.end()) {
    std::cerr << "Unknown movie type: " << type << ", discarding line.\n";
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return nullptr;
  }
  return it->second->createMovie(input);
}
