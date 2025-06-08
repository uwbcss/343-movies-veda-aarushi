#include "comedy.h"
#include <iostream>
#include <vector>
#include <string>

//------------------------------------------------------------------------------
// Comedy implementation
//------------------------------------------------------------------------------

Comedy::Comedy(const std::vector<std::string>& params) {
    if (params.size() == 5) {
        // params[0] is genre code, skip
        inventoryCount_ = std::stoi(params[1]);
        directorName_  = params[2];
        movieTitle_    = params[3];
        releaseYear_   = std::stoi(params[4]);
    }
}

// Return the release year
int Comedy::getReleaseYear() const {
    return releaseYear_;
}

// Print movie details in the specified format
void Comedy::printDetails() const {
    std::cout << movieTitle_ << ", "
              << releaseYear_ << ", "
              << directorName_ << " ("
              << inventoryCount_ << ")"
              << " - Comedy"
              << std::endl;
}

// Comparison for sorting: title, then year
bool Comedy::isLessThan(const Movie* other) const {
    auto o = dynamic_cast<const Comedy*>(other);
    return (movieTitle_ < o->movieTitle_) ||
           (movieTitle_ == o->movieTitle_ && releaseYear_ < o->releaseYear_);
}

// Match for finding: title and year
bool Comedy::matches(int /*month*/, int year,
                     const std::string& titleQuery,
                     const std::string& /*director*/,
                     const std::string& /*actor*/) const {
    return (movieTitle_ == titleQuery && releaseYear_ == year);
}

// Register the Comedy factory at startup
ComedyFactory::ComedyFactory() {
    registerType(genreCode_, this);
}

// Create a new Comedy instance
Movie* ComedyFactory::makeMovie(const std::vector<std::string>& params) const {
    return new Comedy(params);
}

// Instantiate to self-register the factory
ComedyFactory theComedyFactory;
