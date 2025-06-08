#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include "movieStore.h"

/**
 * Command interface: each concrete command implements this.
 */
class Command {
public:
    virtual ~Command() = default;

    /** 
     * Execute this command against the given store 
     * using the provided argument list.
     */
    virtual void perform(MovieStore& store,
                         const std::vector<std::string>& parameters) const = 0;
};

#endif  // COMMAND_H
