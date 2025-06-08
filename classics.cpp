#include "classics.h"
#include <iostream>
#include <sstream>

//------------------------------------------------------------------------------
// Classics implementation
//------------------------------------------------------------------------------

Classics::Classics(const std::vector<std::string>& params) {
    if (params.size() == 5) {
        // params[0] is genre code, skip
        inventoryCount_ = std::stoi(params[1]);
        directorName_   = params[2];
        movieTitle_     = params[3];

        // Parse lead actor and release date from params[4]
        std::istringstream iss(params[4]);
        std::string firstName, lastName;
        int mo, yr;
        iss >> firstName >> lastName >> mo >> yr;

        leadActor_    = firstName + " " + lastName;
        releaseMonth_ = mo;
        releaseYear_  = yr;
    }
}

// Return the release year
int Classics::getReleaseYear() const {
    return releaseYear_;
}

// Print movie details in the specified format
void Classics::printDetails() const {
    std::cout << releaseYear_ << ' '
              << releaseMonth_ << ", "
              << leadActor_    << ", "
              << directorName_ << ", "
              << movieTitle_   << " ("
              << inventoryCount_ << ")"
              << " - Classics"
              << std::endl;
}

// Comparison for sorting: year, month, then lead actor
bool Classics::isLessThan(const Movie* other) const {
    auto o = dynamic_cast<const Classics*>(other);
    return (releaseYear_ < o->releaseYear_) ||
           (releaseYear_ == o->releaseYear_ && releaseMonth_ < o->releaseMonth_) ||
           (releaseYear_ == o->releaseYear_ &&
            releaseMonth_ == o->releaseMonth_ &&
            leadActor_ < o->leadActor_);
}

// Match for finding: month, year, and lead actor
bool Classics::matches(int month,
                       int year,
                       const std::string& /*title*/,
                       const std::string& /*director*/,
                       const std::string& actor) const {
    return (releaseMonth_ == month &&
            releaseYear_  == year  &&
            leadActor_    == actor);
}

// Register the Classics factory at startup
ClassicsFactory::ClassicsFactory() {
    registerType(genreCode_, this);
}

// Create a new Classics instance
Movie* ClassicsFactory::makeMovie(const std::vector<std::string>& params) const {
    return new Classics(params);
}

// Instantiate to self-register the factory
ClassicsFactory theClassicsFactory;
