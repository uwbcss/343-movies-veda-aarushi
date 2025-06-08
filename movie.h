#ifndef MOVIE_H
#define MOVIE_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cout in display()
#include <string>   // for std::string

/// ---------------------------------------------------------------------------
/// Movie
///
/// Abstract base class for all movie types. Encapsulates common attributes
/// (stock, director, title, year) and defines the polymorphic interface:
///   • getKey()       – unique lookup key
///   • getType()      – genre identifier
///   • display()      – human‐readable output
///   • getMovieInfo() – formatted for transaction history
/// ---------------------------------------------------------------------------
class Movie {
protected:
  int stock;            ///< Number of copies available
  std::string director; ///< Movie director
  std::string title;    ///< Movie title
  int year;             ///< Release year

public:
  /// Constructor
  /// \param stock      Initial stock count
  /// \param director   Director name
  /// \param title      Movie title
  /// \param year       Release year
  Movie(int stock, const std::string &director, const std::string &title,
        int year)
      : stock(stock), director(director), title(title), year(year) {}

  /// Destructor
  /// Virtual to allow proper cleanup of derived classes.
  virtual ~Movie() = default;

  /// getStock
  /// Returns the current stock count.
  int getStock() const { return stock; }

  /// getDirector
  /// Returns the director’s name.
  std::string getDirector() const { return director; }

  /// getTitle
  /// Returns the movie’s title.
  std::string getTitle() const { return title; }

  /// getYear
  /// Returns the release year.
  int getYear() const { return year; }

  /// borrowMovie
  /// Decrements stock by one if available.
  void borrowMovie() {
    if (stock > 0) {
      --stock;
    }
  }

  /// returnMovie
  /// Increments stock by one.
  void returnMovie() { ++stock; }

  /// getKey
  /// Pure virtual: returns the unique lookup key for this movie.
  virtual std::string getKey() const = 0;

  /// getType
  /// Pure virtual: returns the genre code (e.g., "F", "D", "C").
  virtual std::string getType() const = 0;

  /// matchesKey
  /// Compares a candidate key string to this movie’s key.
  bool matchesKey(const std::string &key) const { return getKey() == key; }

  /// display
  /// Prints movie details in a generic CSV‐like format. Subclasses may
  /// override.
  virtual void display() const {
    std::cout << getType() << ", " << stock << ", " << director << ", " << title
              << ", " << year << "\n";
  }

  /// getMovieInfo
  /// Pure virtual: returns a formatted string for printing in histories.
  virtual std::string getMovieInfo() const = 0;
};

#endif // MOVIE_H
