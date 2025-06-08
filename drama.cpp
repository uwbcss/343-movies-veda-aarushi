// -----------------------------------------------------------------------------
// drama.cpp
// Implementation of the Drama movie type and its factory.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cout, std::getline
#include <istream>  // for std::istream
#include <string>   // for std::string

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "drama.h"
#include <limits>

//------------------------------------------------------------------------------
// Drama methods
//------------------------------------------------------------------------------

// Constructor
// Initializes a Drama movie with stock, director, title, and year.
Drama::Drama(int stock, const std::string &director, const std::string &title,
             int year)
    : Movie(stock, director, title, year) {}

// display()
// Prints the movie's details in the format:
//   "<director>, <title>, <year> (<stock>) - Drama"
void Drama::display() const {
  std::cout << trim(director) << ", " << trim(title) << ", " << year << " ("
            << stock << ") - Drama\n";
}

// getMovieInfo()
// Returns a string for transaction history in the format:
//   "<director>, <title>, <year> (<stock>) - Drama"
std::string Drama::getMovieInfo() const {
  return trim(director) + ", " + trim(title) + ", " + std::to_string(year) +
         " (" + std::to_string(stock) + ") - Drama";
}

// getKey()
// Generates a lookup key based on director and title:
//   "<director>, <title>,"
std::string Drama::getKey() const {
  return trim(director) + ", " + trim(title) + ",";
}

// getType()
// Returns the genre code for Drama ("D")
std::string Drama::getType() const { return "D"; }

// trim()
// Utility to remove leading/trailing whitespace from a string.
std::string Drama::trim(const std::string &str) {
  const auto first = str.find_first_not_of(" \t");
  if (first == std::string::npos) {
    return ""; // Entire string is whitespace
  }
  const auto last = str.find_last_not_of(" \t");
  return str.substr(first, last - first + 1);
}

//------------------------------------------------------------------------------
// DramaFactory (self-registering)
//------------------------------------------------------------------------------

// Factory for creating Drama instances from the data file.
// Reads stock, director, title, and year.
class DramaFactory : public MovieFactory {
public:
  DramaFactory() { registerType('D', this); }

  Movie *createMovie(std::istream &input) const override {
    int stockVal;
    int yearVal;
    std::string directorVal;
    std::string titleVal;

    // 1) Read stock count
    input >> stockVal;
    input.ignore(); // skip comma

    // 2) Read director name (up to comma)
    std::getline(input, directorVal, ',');
    input.ignore(); // skip comma

    // 3) Read title (up to comma)
    std::getline(input, titleVal, ',');
    input.ignore(); // skip comma

    // 4) Read release year
    input >> yearVal;
    // Discard remainder of line (if any)
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return new Drama(stockVal, directorVal, titleVal, yearVal);
  }
};

// Static instance to register this factory at program startup
static DramaFactory registerDrama;
