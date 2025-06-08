#ifndef DRAMA_H
#define DRAMA_H

#include <vector>
#include <string>

#include "movie.h"
#include "movieFactory.h"

/**
 * Represents a drama movie with director, title, and release year.
 */
class Drama : public Movie {
public:
    /**
     * Construct from tokens: [genreCode, stock, director, title, year]
     */
    explicit Drama(const std::vector<std::string>& tokens);

    int getReleaseYear() const override;
    void printDetails() const override;
    bool isLessThan(const Movie* other) const override;
    bool matches(int /*month*/,
                 int /*year*/,
                 const std::string& titleQuery,
                 const std::string& directorQuery,
                 const std::string& /*actor*/) const override;

private:
    static constexpr char genreCode_ = 'D';
    int releaseYear_{0};
};

/**
 * Factory for Drama; self-registers with MovieFactory.
 */
class DramaFactory : public MovieFactory {
public:
    DramaFactory();
    Movie* makeMovie(const std::vector<std::string>& tokens) const override;
};

#endif  // DRAMA_H