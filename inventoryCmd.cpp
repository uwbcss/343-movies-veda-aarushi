#ifndef HISTORYCMD_H
#define HISTORYCMD_H

#include "command.h"
#include "commandFactory.h"
#include "movieStore.h"

class HistoryCmd : public Command {
  protected:
    string data;
  public:
    HistoryCmd();
    void execute(MovieStore& store, const vector<string> &vs) const override;
  private:
    char cmd;  // 'H'
};

/**
 * Creating HistoryCmdFactory to make HistoryCmd objects
 * HistoryCmdFactory object will register itself later and get stored in Command class
 */
class HistoryCmdFactory : public CommandFactory {
public:
  HistoryCmdFactory();
  Command *makeCommand(const vector<string> &vs) const override;
};

#endif // HISTORYCMD_H