#ifndef CLASSICS_H
#define CLASSICS_H

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
/// Classics
///
/// A subclass of Movie representing classic films. Includes additional fields
/// for the lead actor and release month, and provides polymorphic overrides.
/// ---------------------------------------------------------------------------
class Classics : public Movie {
public:
  /// Constructor
  /// \param stock     Initial number of copies in stock
  /// \param director  Director's name
  /// \param title     Movie title
  /// \param actor     Lead actor's full name
  /// \param month     Release month (1–12)
  /// \param year      Release year
  Classics(int stock, const std::string &director, const std::string &title,
           const std::string &actor, int month, int year)
      : Movie(stock, director, title, year), actor(actor), month(month) {}

  /// display
  /// Prints movie details in the format:
  ///   "<year> <month>, <actor>, <director>, <title> (<stock>) - Classics"
  void display() const override;

  /// getMovieInfo
  /// Returns a string suitable for transaction history:
  ///   "<year> <month>, <actor>, <director>, <title> (<stock>) - Classics"
  std::string getMovieInfo() const override;

  /// getKey
  /// Generates the lookup key:
  ///   "<month> <year> <actor>"
  std::string getKey() const override;

  /// getType
  /// Returns the genre code for Classics ("C").
  std::string getType() const override;

  /// getActor
  /// Accessor for the lead actor.
  std::string getActor() const;

  /// getMonth
  /// Accessor for the release month.
  int getMonth() const;

private:
  std::string actor; ///< Lead actor for this classic
  int month;         ///< Release month
};

#endif // CLASSICS_H
