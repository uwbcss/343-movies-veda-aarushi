#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

#include "commandFactory.h"
#include "command.h"

//------------------------------------------------------------------------------
// Internal registry of all CommandFactory instances.
//------------------------------------------------------------------------------
std::map<char, CommandFactory*>& CommandFactory::getMap() {
    static std::map<char, CommandFactory*> registry;
    return registry;
}

//------------------------------------------------------------------------------
// Register a factory for a given command code.
//------------------------------------------------------------------------------
void CommandFactory::registerType(const char& commandCode,
                                  CommandFactory* factory) {
    getMap().emplace(commandCode, factory);
}

//------------------------------------------------------------------------------
// Create a Command from its code and arguments.  
// If the code is unknown, log and return nullptr.
//------------------------------------------------------------------------------
Command* CommandFactory::create(const char& commandCode,
                                const std::vector<std::string>& params) {
    auto& registry = getMap();
    if (registry.count(commandCode) == 0) {
        std::cout << "Unknown command type: " << commandCode
                  << "; discarding input:";
        if (params.size() > 1) {
            for (const auto& token : params) {
                std::cout << ' ' << token;
            }
        } else {
            std::istringstream iss(params[0]);
            std::string leftover;
            iss >> leftover;      // skip invalid token
            std::getline(iss, leftover);
            std::cout << leftover;
        }
        std::cout << std::endl;
        return nullptr;
    }

    return registry.at(commandCode)->makeCommand(params);
}
