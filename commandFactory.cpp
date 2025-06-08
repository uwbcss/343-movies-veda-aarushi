// -----------------------------------------------------------------------------
// commandFactory.cpp
// Implements the self‐registering factory for Commands.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cerr
#include <istream>  // for std::istream
#include <map>      // for std::map

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "commandFactory.h"

//------------------------------------------------------------------------------
// CommandFactory static registry access
//------------------------------------------------------------------------------

// getRegistry()
// Returns the singleton map from command code char → factory instance.
std::map<char, CommandFactory *> &CommandFactory::getRegistry() {
  static std::map<char, CommandFactory *> registry;
  return registry;
}

//------------------------------------------------------------------------------
// Registration API
//------------------------------------------------------------------------------

// registerType()
// Associates a command‐code character with a particular factory object.
void CommandFactory::registerType(char type, CommandFactory *factory) {
  getRegistry()[type] = factory;
}

//------------------------------------------------------------------------------
// Factory creation
//------------------------------------------------------------------------------

// create()
// Looks up the factory for the given command code and invokes it.
// On unknown codes, logs an error and returns nullptr.
Command *CommandFactory::create(char type, std::istream &input) {
  auto &registry = getRegistry();
  auto it = registry.find(type);
  if (it != registry.end()) {
    return it->second->createCommand(input);
  }
  std::cerr << "Invalid command type: " << type << ", discarding line.\n";
  return nullptr;
}
