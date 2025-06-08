#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::istream in createCommand signature
#include <map>      // for std::map used in registry

//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
class Command;

//------------------------------------------------------------------------------
/// CommandFactory
///
/// Self‐registering factory for creating Command instances based on a
/// single‐character command code. Derived factories implement createCommand()
/// to parse their specific parameters and return a new Command object.
/// ---------------------------------------------------------------------------
class CommandFactory {
public:
  /// createCommand
  /// Pure‐virtual method to parse input and instantiate a Command.
  /// \param input  Stream positioned after the command code.
  virtual Command *createCommand(std::istream &input) const = 0;

  /// create
  /// Static entry point: looks up the factory for `type` and delegates
  /// to createCommand(). Emits an error on unknown types.
  /// \param type   Command code character (e.g., 'B', 'R', 'I', 'H')
  /// \param input  Stream to parse remaining parameters.
  static Command *create(char type, std::istream &input);

  /// registerType
  /// Registers a factory instance for a given command code.
  /// Called by each concrete factory at static initialization.
  /// \param type     Command code character
  /// \param factory  Pointer to factory instance
  static void registerType(char type, CommandFactory *factory);

private:
  /// getRegistry
  /// Returns the singleton map from code → factory.
  static std::map<char, CommandFactory *> &getRegistry();
};

#endif // COMMANDFACTORY_H
