#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <map>

/**
 * Abstract base for all movie types.
 * Provides factory storage and movie-creation interfaces.
 */
class Movie {
public:
    virtual ~Movie() = default;

    // Accessors
    virtual int getReleaseYear() const = 0;
    virtual void printDetails() const = 0;

    // Comparison for sorting
    virtual bool isLessThan(const Movie* other) const = 0;

    // Match query parameters (year/month/title/director/actor)
    virtual bool matches(int month,
                         int year,
                         const std::string& titleQuery,
                         const std::string& directorQuery,
                         const std::string& leadActor) const = 0;

    // Stock operations
    int getInventoryCount() const { return inventoryCount_; }
    void incrementInventory() { ++inventoryCount_; }
    void decrementInventory() { --inventoryCount_; }

protected:
    std::string directorName_;
    std::string movieTitle_;
    int inventoryCount_{0};
};

#endif  // MOVIE_H
