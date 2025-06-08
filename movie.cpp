#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "movieFactory.h"
#include "movie.h"

//------------------------------------------------------------------------------
// Registry of all MovieFactory instances.
//------------------------------------------------------------------------------
std::map<char, MovieFactory*>& MovieFactory::getMap() {
    static std::map<char, MovieFactory*> registry;
    return registry;
}

//------------------------------------------------------------------------------
// Register a factory for a given movie code.
//------------------------------------------------------------------------------
void MovieFactory::registerType(const char& movieCode,
                                MovieFactory* factory) {
    getMap().emplace(movieCode, factory);
}

//------------------------------------------------------------------------------
// Create a Movie from its code and parameters.
// If the code is unknown, log and return nullptr.
//------------------------------------------------------------------------------
Movie* MovieFactory::create(const char& movieCode,
                            const std::vector<std::string>& params) {
    auto& registry = getMap();
    if (registry.count(movieCode) == 0) {
        std::cout << "Unknown movie type: " << movieCode << std::endl;
        return nullptr;
    }
    return registry.at(movieCode)->makeMovie(params);
}
