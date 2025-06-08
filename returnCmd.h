#ifndef RETURNCMD_H
#define RETURNCMD_H

#include "command.h"
#include "commandFactory.h"
#include "movieStore.h"

class ReturnCmd : public Command {
  protected:
    string data;
  public:
    ReturnCmd();
    void execute(MovieStore& store, const vector<string> &vs) const override;
  private:
    char cmd;  // 'R'
};

/**
 * Creating ReturnCmdFactory to make ReturnCmd objects
 * ReturnCmdFactory object will register itself later and get stored in Command class
 */
class ReturnCmdFactory : public CommandFactory {
public:
  ReturnCmdFactory();
  Command *makeCommand(const vector<string> &vs) const override;
};

#endif // RETURNCMD_H