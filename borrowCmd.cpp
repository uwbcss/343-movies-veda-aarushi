#include "borrowCmd.h"
#include "classics.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

//------------------------------------------------------------------------------
// BorrowCmd implementation
//------------------------------------------------------------------------------

BorrowCmd::BorrowCmd() = default;

void BorrowCmd::perform(MovieStore& store,
                            const std::vector<std::string>& tokens) const {
    // Parse header: B <customerId> <mediaTypeCode> <categoryCode>
    std::istringstream header(tokens[0]);
    char commandLetter{};
    int customerId{};
    char mediaTypeCode{};
    char categoryCode{};
    header >> commandLetter >> customerId >> mediaTypeCode >> categoryCode;

    // Remaining data
    int releaseMonth{0}, releaseYear{0};
    std::string movieTitle, directorName, leadActor;

    // Lookup customer
    Customer* customer = nullptr;
    auto& customers = store.getCustomerList();
    auto custIt = customers.find(customerId);
    if (custIt != customers.end()) {
        customer = custIt->second;
    }

    // Validate category
    if (categoryCode != 'F' && categoryCode != 'D' && categoryCode != 'C') {
        std::string rest;
        std::getline(header, rest);
        std::cout << "Invalid movie category " << categoryCode
                  << ", discarding line:" << rest << std::endl;
        return;
    }

    // Handle per-category parsing
    if (categoryCode == 'F' || categoryCode == 'D') {
        // Both Comedy and Drama require mediaType 'D' and a valid customer
        if (mediaTypeCode != 'D') {
            std::string rest;
            std::getline(header, rest);
            std::cout << "Invalid media type " << mediaTypeCode
                      << ", discarding line:" << rest
                      << ", " << tokens[1] << std::endl;
            return;
        }
        if (!customer) {
            header.clear();
            header.seekg(0);
            header >> commandLetter >> customerId;
            std::string rest;
            std::getline(header, rest);
            std::cout << "Invalid customer ID " << customerId
                      << ", discarding line:" << rest
                      << ", " << tokens[1] << std::endl;
            return;
        }
        if (categoryCode == 'F') {
            // Comedy: tokens[1] = year, rest of header = title
            releaseYear = std::stoi(tokens[1]);
            std::getline(header, movieTitle);
            // trim leading space
            movieTitle.erase(0, movieTitle.find_first_not_of(' '));
        } else {
            // Drama: tokens[1] = title, rest of header = director
            movieTitle = tokens[1];
            std::getline(header, directorName);
            directorName.erase(0, directorName.find_first_not_of(' '));
        }
    } else {
        // Classics: mediaType 'D', valid customer, then month year actor
        if (mediaTypeCode != 'D') {
            std::string rest;
            std::getline(header, rest);
            std::cout << "Invalid media type " << mediaTypeCode
                      << ", discarding line:" << rest << std::endl;
            return;
        }
        if (!customer) {
            header.clear();
            header.seekg(0);
            header >> commandLetter >> customerId;
            std::string rest;
            std::getline(header, rest);
            std::cout << "Invalid customer ID " << customerId
                      << ", discarding line:" << rest << std::endl;
            return;
        }
        // tokens[0] includes month and year and actor
        std::string firstName, lastName;
        header >> releaseMonth >> releaseYear >> firstName >> lastName;
        leadActor = firstName + " " + lastName;
    }

    // Find the movie in inventory
    Movie* target = nullptr;
    auto& inventory = store.getMoviesByType();
    const auto& movieList = inventory[categoryCode - 'A'];
    for (Movie* m : movieList) {
        if (m->matches(releaseMonth, releaseYear,
                       movieTitle, directorName, leadActor)) {
            target = m;
            break;
        }
    }

    if (!target) {
        std::cout << "Invalid movie for customer "
                  << (customer ? customer->getFullName() : "Unknown")
                  << ", discarding line." << std::endl;
        return;
    }

    // Attempt to borrow
    if (target->getInventoryCount() > 0) {
        customer->borrowMovie(target);
        target->decrementInventory();
    } else {
        std::cout << "==========================" << std::endl
                  << customer->getFullName()
                  << " could NOT borrow " << movieTitle
                  << ", out of stock:" << std::endl
                  << "==========================" << std::endl
                  << "Failed to execute command: Borrow "
                  << customer->getFullName() << " "
                  << movieTitle << std::endl;
    }
}

//------------------------------------------------------------------------------
// BorrowCmdFactory self-registration
//------------------------------------------------------------------------------

BorrowCmdFactory::BorrowCmdFactory() {
    registerType(commandCode_, this);
}

Command* BorrowCmdFactory::makeCommand(
    const std::vector<std::string>& /*args*/) const {
    return new BorrowCmd();
}

// Instantiate to self-register
BorrowCmdFactory theBorrowCmdFactory;
