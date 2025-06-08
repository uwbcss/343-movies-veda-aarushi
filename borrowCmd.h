#ifndef BORROW_COMMAND_H
#define BORROW_COMMAND_H

#include <vector>
#include <string>

#include "command.h"
#include "commandFactory.h"
#include "movieStore.h"

/**
 * Command to borrow a movie from the store.
 * Decreases stock by one when executed.
 */
class BorrowCmd : public Command {
public:
    BorrowCmd();

    /** 
     * Performs a borrow action on the store.
     * @param store  Reference to the movie store.
     * @param args   Parsed command tokens.
     */
    void perform(MovieStore& store,
                 const std::vector<std::string>& args) const override;

private:
    static constexpr char commandCode_ = 'B';
};

/**
 * Factory for BorrowCmd; self-registers with CommandFactory.
 */
class BorrowCmdFactory : public CommandFactory {
public:
    BorrowCmdFactory();
    Command* makeCommand(const std::vector<std::string>& args) const override;
};

#endif  // BORROW_COMMAND_H
