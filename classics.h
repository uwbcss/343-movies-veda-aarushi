#ifndef CLASSICS_H
#define CLASSICS_H

#include <vector>
#include <string>

#include "movie.h"
#include "movieFactory.h"

/**
 * Represents a classic movie, including release date and leading actor.
 */
class Classics : public Movie {
public:
    /** 
     * Construct from a token list: 
     * [genreCode, director, title, month, year, actorFirst actorLast]
     */
    explicit Classics(const std::vector<std::string>& params);

    int getReleaseYear() const override;
    void printDetails() const override;
    bool isLessThan(const Movie* other) const override;
    bool matches(int month,
                 int year,
                 const std::string& titleQuery,
                 const std::string& directorQuery,
                 const std::string& leadActor) const override;

private:
    int releaseMonth_{0};
    int releaseYear_{0};
    std::string leadActor_;
    static constexpr char genreCode_ = 'C';
};

/**
 * Factory for Classics objects; self-registers with MovieFactory.
 */
class ClassicsFactory : public MovieFactory {
public:
    ClassicsFactory();
    Movie* makeMovie(const std::vector<std::string>& params) const override;
};

#endif  // CLASSICS_H
