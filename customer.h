#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "movie.h"

/**
 * Represents a customer who can borrow and return movies.
 */
class Customer {
public:
    /**
     * Construct a customer with ID and name.
     * @param customerId  Unique identifier for the customer.
     * @param firstName   Customer's first name.
     * @param lastName    Customer's last name.
     */
    Customer(int customerId, const std::string& firstName, const std::string& lastName);

    // Accessors
    int getCustomerId() const;
    std::string getFullName() const;

    // Borrow or return a movie
    void borrowMovie(Movie* movie);
    void returnMovie(Movie* movie);

    // Print the transaction history
    void printHistory() const;

private:
    int customerId_{0};
    std::string firstName_;
    std::string lastName_;
    std::unordered_map<std::string, Movie*> borrowedMovies_;
    std::vector<std::string> history_;
};

#endif // CUSTOMER_H
