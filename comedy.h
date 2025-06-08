#ifndef COMEDY_H
#define COMEDY_H

#include <vector>
#include <string>

#include "movie.h"
#include "movieFactory.h"

/**
 * Represents a comedy movie with title, director, and release year.
 */
class Comedy : public Movie {
public:
    /**
     * Construct from tokens: [genreCode, stock, director, title, year]
     */
    explicit Comedy(const std::vector<std::string>& tokens);

    int getReleaseYear() const override;
    void printDetails() const override;
    bool isLessThan(const Movie* other) const override;
    bool matches(int /*month*/,
                 int year,
                 const std::string& titleQuery,
                 const std::string& /*director*/,
                 const std::string& /*actor*/) const override;

private:
    static constexpr char genreCode_ = 'F';
    int releaseYear_{0};
};

/**
 * Factory for Comedy; self-registers with MovieFactory.
 */
class ComedyFactory : public MovieFactory {
public:
    ComedyFactory();
    Movie* makeMovie(const std::vector<std::string>& tokens) const override;
};

#endif  // COMEDY_H
