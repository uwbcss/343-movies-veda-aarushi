// -----------------------------------------------------------------------------
// comedy.cpp
// Implementation of the Comedy movie type and its factory.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cout
#include <string>   // for std::string, std::to_string

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "comedy.h"

//------------------------------------------------------------------------------
// Comedy methods
//------------------------------------------------------------------------------

// display()
// Prints the movie's details in the format:
//   "<title>, <year>, <director> (<stock>) - Comedy"
void Comedy::display() const {
  std::cout << title << ", " << year << ", " << director << " (" << stock
            << ") - Comedy\n";
}

// getMovieInfo()
// Returns a string suitable for transaction history:
//   "<title>, <year>, <director> (<stock>) - Comedy"
std::string Comedy::getMovieInfo() const {
  return title + ", " + std::to_string(year) + ", " + director + " (" +
         std::to_string(stock) + ") - Comedy";
}

// getKey()
// Generates the lookup key for comedies:
//   "<title>, <year>"
std::string Comedy::getKey() const {
  return title + ", " + std::to_string(year);
}

// getType()
// Returns the genre code for comedies ("F")
std::string Comedy::getType() const { return "F"; }

//------------------------------------------------------------------------------
// ComedyFactory (self-registering)
//------------------------------------------------------------------------------

// Factory class for creating Comedy instances from an input stream.
// Reads stock, director, title, and year.
class ComedyFactory : public MovieFactory {
public:
  ComedyFactory() { registerType('F', this); }

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

    // 4) Read release year
    input >> yearVal;

    // Create and return the Comedy object
    return new Comedy(stockVal, directorVal, titleVal, yearVal);
  }
};

// Static instance to register this factory at program startup
static ComedyFactory registerComedy;
