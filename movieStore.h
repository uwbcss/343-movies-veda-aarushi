#include "movieStore.h"
#include "commandFactory.h"
#include "movieFactory.h"

#include <fstream>
#include <algorithm>
#include <iostream>

//------------------------------------------------------------------------------
// Accessors
//------------------------------------------------------------------------------

// Return the array of movie buckets
std::vector<Movie*> (&MovieStore::getMoviesByType())[TABLE_SIZE] {
    return moviesByType;
}

// Return the customer map
std::unordered_map<int, Customer*>& MovieStore::getCustomerList() {
    return customerList;
}

//------------------------------------------------------------------------------
// Utility functions
//------------------------------------------------------------------------------

std::string MovieStore::trimString(const std::string& str) {
    const auto start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    const auto end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> MovieStore::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string temp;
    for (char c : str) {
        if (c == delimiter) {
            tokens.push_back(trimString(temp));
            temp.clear();
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        tokens.push_back(trimString(temp));
    }
    return tokens;
}

//------------------------------------------------------------------------------
// File readers
//------------------------------------------------------------------------------

void MovieStore::readCustomersFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening customer file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        auto parts = splitString(line, ' ');
        if (parts.size() >= 3) {
            int id = std::stoi(parts[0]);
            auto cust = new Customer(id, parts[1], parts[2]);
            customerList.emplace(id, cust);
        }
    }
}

void MovieStore::readMoviesFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening movie file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        auto parts = splitString(line, ',');
        char type = parts[0][0];
        Movie* movie = MovieFactory::create(type, parts);
        if (movie) {
            int bucket = getBucket(type);
            moviesByType[bucket].push_back(movie);
        }
    }
}

// Read and execute commands
void MovieStore::readCommandsFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening commands file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        auto parts = splitString(line, ' ');
        char cmd = parts[0][0];
        auto command = CommandFactory::create(cmd, parts);
        if (command) {
            command->perform(*this, parts);
            delete command;
        }
    }
}

// Execute commands directly
void MovieStore::executeCommands(const std::string& filename) {
    readCommandsFromFile(filename);
}

// Sort all movie buckets
void MovieStore::sortInventory() {
    for (auto& bucket : moviesByType) {
        std::sort(bucket.begin(), bucket.end(), [](Movie* a, Movie* b) {
            return a->isLessThan(b);
        });
    }
}

// Destructor: free all allocated movies and customers
MovieStore::~MovieStore() {
    for (auto& bucket : moviesByType) {
        for (auto* m : bucket) {
            delete m;
        }
    }
    for (auto& kv : customerList) {
        delete kv.second;
    }
}
