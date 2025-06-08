#include "drama.h"
#include <iostream>
#include <vector>
#include <string>

//------------------------------------------------------------------------------
// Drama implementation
//------------------------------------------------------------------------------

Drama::Drama(const std::vector<std::string>& tokens) {
    if (tokens.size() == 5) {
        // tokens[0] is genre code, skip
        inventoryCount_ = std::stoi(tokens[1]);
        directorName_   = tokens[2];
        movieTitle_     = tokens[3];
        releaseYear_    = std::stoi(tokens[4]);
    }
}

int Drama::getReleaseYear() const {
    return releaseYear_;
}

void Drama::printDetails() const {
    std::cout << directorName_ << ", "
              << movieTitle_   << ", "
              << releaseYear_  << " ("
              << inventoryCount_ << ")"
              << " - Drama"
              << std::endl;
}

bool Drama::isLessThan(const Movie* other) const {
    auto o = dynamic_cast<const Drama*>(other);
    return (directorName_ < o->directorName_) ||
           (directorName_ == o->directorName_ && movieTitle_ < o->movieTitle_);
}

bool Drama::matches(int /*month*/,
                    int /*year*/,
                    const std::string& titleQuery,
                    const std::string& directorQuery,
                    const std::string& /*actor*/) const {
    return (movieTitle_ == titleQuery && directorName_ == directorQuery);
}

DramaFactory::DramaFactory() {
    registerType(genreCode_, this);
}

Movie* DramaFactory::makeMovie(const std::vector<std::string>& tokens) const {
    return new Drama(tokens);
}

// Instantiate to self-register the factory
DramaFactory theDramaFactory;
