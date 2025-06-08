#ifndef MOVIE_H
#define MOVIE_H

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cout
#include <string>   // for std::string

/// ---------------------------------------------------------------------------
/// Movie
///
/// Abstract base class representing a generic movie. Stores common attributes
/// (stock, director, title, year) and defines the interface for derived types.
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
  /// Virtual to ensure proper cleanup of derived classes.
  virtual ~Movie() = default;

  /// getStock
  /// Returns current stock count.
  int getStock() const { return stock; }

  /// getDirector
  /// Returns the director name.
  std::string getDirector() const { return director; }

  /// getTitle
  /// Returns the movie title.
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
  /// Pure virtual: must return a unique lookup key for this movie.
  virtual std::string getKey() const = 0;

  /// getType
  /// Pure virtual: must return the genre code (e.g., "F", "D", "C").
  virtual std::string getType() const = 0;

  /// matchesKey
  /// Checks if the provided key matches this movie's key.
  bool matchesKey(const std::string &key) const { return getKey() == key; }

  /// display
  /// Virtual: prints movie details in a generic format. Subclasses should
  /// override for custom formatting.
  virtual void display() const {
    std::cout << getType() << ", " << stock << ", " << director << ", " << title
              << ", " << year << "\n";
  }

  /// getMovieInfo
  /// Pure virtual: must return a formatted string for transaction history.
  virtual std::string getMovieInfo() const = 0;
};

#endif // MOVIE_H
