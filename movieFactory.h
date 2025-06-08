#ifndef MOVIEFACTORY_H
#define MOVIEFACTORY_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::istream in createMovie signature
#include <map>      // for std::map used in registry

//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
class Movie; // Represents a generic movie type

/// --------------------------------------------------------------------------
/// MovieFactory
///
/// Self‐registering factory interface for creating Movie instances from input
/// streams. Derived factories implement createMovie() to parse their specific
/// formats. Registration ties a character code (e.g., 'F', 'D', 'C') to each
/// factory instance.
/// --------------------------------------------------------------------------
class MovieFactory {
public:
  /// createMovie
  /// Pure virtual: parse input and return a new Movie instance.
  /// \param input  Stream positioned after the movie type code.
  virtual Movie *createMovie(std::istream &input) const = 0;

  /// create
  /// Static entry point: looks up the factory for `type` and delegates to
  /// createMovie(). Emits an error on unrecognized types.
  /// \param type   Movie genre code character
  /// \param input  Stream containing the rest of the record
  static Movie *create(char type, std::istream &input);

protected:
  /// registerType
  /// Registers a factory instance for a given movie code. Called by each
  /// concrete factory at static initialization.
  /// \param type     Genre code character
  /// \param factory  Pointer to factory instance
  static void registerType(char type, MovieFactory *factory);

private:
  /// getRegistry
  /// Returns the singleton map from code → factory.
  static std::map<char, MovieFactory *> &getRegistry();
};

#endif // MOVIEFACTORY_H
