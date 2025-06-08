#ifndef COMEDY_H
#define COMEDY_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <string>

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "movie.h"
#include "movieFactory.h"

/// ---------------------------------------------------------------------------
/// Comedy
///
/// Subclass of Movie representing Comedy films. Provides polymorphic overrides
/// for display, key generation, and type identification.
/// ---------------------------------------------------------------------------
class Comedy : public Movie {
public:
  /// Constructor
  /// \param stock     Initial stock count
  /// \param director  Director's name
  /// \param title     Movie title
  /// \param year      Release year
  Comedy(int stock, const std::string &director, const std::string &title,
         int year)
      : Movie(stock, director, title, year) {}

  /// display
  /// Prints movie details in the format:
  ///   "<title>, <year>, <director> (<stock>) - Comedy"
  void display() const override;

  /// getMovieInfo
  /// Returns a string for transaction history:
  ///   "<title>, <year>, <director> (<stock>) - Comedy"
  std::string getMovieInfo() const override;

  /// getKey
  /// Generates unique lookup key:
  ///   "<title>, <year>"
  std::string getKey() const override;

  /// getType
  /// Returns the genre code for Comedy ("F")
  std::string getType() const override;
};

#endif // COMEDY_H
