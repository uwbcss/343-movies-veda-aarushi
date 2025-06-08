// -----------------------------------------------------------------------------
// classics.cpp
// Implementation of the Classics movie type and its factory.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cout
#include <limits>   // for std::numeric_limits
#include <sstream>  // for std::ostringstream

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "classics.h"

//------------------------------------------------------------------------------
// Classics methods
//------------------------------------------------------------------------------

// display()
// Prints the movie's details in the format:
//   "<year> <month>, <actor>, <director>, <title> (<stock>) - Classics"
void Classics::display() const {
  std::cout << year << " " << month << ", " << actor << ", " << director << ", "
            << title << " (" << stock << ") - Classics\n";
}

// getMovieInfo()
// Returns a string for transaction history in the format:
//   "<year> <month>, <actor>, <director>, <title> (<stock>) - Classics"
std::string Classics::getMovieInfo() const {
  std::ostringstream oss;
  oss << year << " " << month << ", " << actor << ", " << director << ", "
      << title << " (" << stock << ") - Classics";
  return oss.str();
}

// getKey()
// Generates a unique lookup key based on month, year, and actor:
//   "<month> <year> <actor>"
std::string Classics::getKey() const {
  std::ostringstream oss;
  oss << month << " " << year << " " << actor;
  return oss.str();
}

// getType()
// Returns the character code for the Classics genre ('C')
std::string Classics::getType() const { return "C"; }

// getActor()
// Accessor for the major actor of this Classic
std::string Classics::getActor() const { return actor; }

// getMonth()
// Accessor for the release month of this Classic
int Classics::getMonth() const { return month; }

//------------------------------------------------------------------------------
// ClassicsFactory (self-registering)
//------------------------------------------------------------------------------

// Factory for creating Classics instances from an input stream.
// Reads stock, director, title, actor names, month, and year.
class ClassicsFactory : public MovieFactory {
public:
  ClassicsFactory() { registerType('C', this); }

  Movie *createMovie(std::istream &input) const override {
    int stockVal;
    int monthVal;
    int yearVal;
    std::string directorVal;
    std::string titleVal;
    std::string firstName;
    std::string lastName;

    // 1) Read stock count
    input >> stockVal;
    input.ignore(); // skip comma

    // 2) Read director name (up to comma)
    std::getline(input, directorVal, ',');
    input.ignore(); // skip comma

    // 3) Read title (up to comma)
    std::getline(input, titleVal, ',');
    input.ignore(); // skip comma

    // 4) Read actor first/last name, month, and year
    input >> firstName >> lastName >> monthVal >> yearVal;
    // Discard the rest of the line (if any)
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Combine actor first and last name
    std::string actorName = firstName + " " + lastName;

    // Create and return the Classics object
    return new Classics(stockVal, directorVal, titleVal, actorName, monthVal,
                        yearVal);
  }
};

// Static instance to register the ClassicsFactory at program startup
static ClassicsFactory registerClassics;
