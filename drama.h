#ifndef DRAMA_H
#define DRAMA_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <string> // for std::string

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "movie.h"
#include "movieFactory.h"

/// ---------------------------------------------------------------------------
/// Drama
///
/// Subclass of Movie representing Drama films. Overrides display,
/// key generation, and history formatting. Includes a trim utility
/// for cleaning whitespace on input fields.
/// ---------------------------------------------------------------------------
class Drama : public Movie {
public:
  /// Constructor
  /// \param stock      Initial stock count
  /// \param director   Director's name
  /// \param title      Movie title
  /// \param year       Release year
  Drama(int stock, const std::string &director, const std::string &title,
        int year);

  /// display
  /// Prints the movie’s details in the format:
  ///   "<director>, <title>, <year> (<stock>) - Drama"
  void display() const override;

  /// getMovieInfo
  /// Returns a string for transaction history:
  ///   "<director>, <title>, <year> (<stock>) - Drama"
  std::string getMovieInfo() const override;

  /// getKey
  /// Generates the lookup key for dramas:
  ///   "<director>, <title>,"
  std::string getKey() const override;

  /// getType
  /// Returns the genre code for dramas ("D")
  std::string getType() const override;

private:
  /// trim
  /// Removes leading and trailing whitespace from a string.
  /// \param str  Input string
  /// \return     Trimmed string
  static std::string trim(const std::string &str);
};

#endif // DRAMA_H
