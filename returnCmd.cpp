#ifndef INVENTORYCMD_H
#define INVENTORYCMD_H

#include "command.h"
#include "commandFactory.h"
#include "movieStore.h"

class InventoryCmd : public Command {
  public:
    InventoryCmd();
    void execute(MovieStore& store, const vector<string> &vs) const override;
  private:
    char cmd;  // 'I'
};

/**
 * Creating InventoryCmdFactory to make InventoryCmd objects
 * InventoryCmdFactory object will register itself later and get stored in Command class
 */
class InventoryCmdFactory : public CommandFactory {
public:
  InventoryCmdFactory();
  Command *makeCommand(const vector<string> &vs) const override;
};

#endif // INVENTORYCMD_H