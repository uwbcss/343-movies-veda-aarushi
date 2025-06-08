#include "customer.h"

#include <iostream>
#include <sstream>
#include <string>

//------------------------------------------------------------------------------
// Customer implementation
//------------------------------------------------------------------------------

Customer::Customer(int customerId,
                   const std::string& firstName,
                   const std::string& lastName)
    : customerId_(customerId),
      firstName_(firstName),
      lastName_(lastName) {}

int Customer::getCustomerId() const {
    return customerId_;
}

std::string Customer::getFullName() const {
    return lastName_ + " " + firstName_;
}

void Customer::borrowMovie(Movie* movie) {
    borrowedMovies_[movie->title] = movie;
    history_.push_back("Borrow " + movie->title);
}

void Customer::returnMovie(Movie* movie) {
    auto it = borrowedMovies_.find(movie->title);
    if (it == borrowedMovies_.end()) {
        std::cout << "==========================" << std::endl;
        std::cout << getFullName() << " could NOT return "
                  << movie->title << ", never borrowed:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Failed to execute command: Return "
                  << getFullName() << " " << movie->title << std::endl;
        return;
    }
    borrowedMovies_.erase(it);
    history_.push_back("Return " + movie->title);
}

void Customer::printHistory() const {
    if (history_.empty()) {
        std::cout << "No history for " << getFullName() << std::endl;
        return;
    }
    for (const auto& record : history_) {
        std::istringstream iss(record);
        std::string action;
        std::string remainder;
        iss >> action;
        std::getline(iss, remainder);
        std::cout << action << " " << getFullName() << remainder << std::endl;
    }
}
