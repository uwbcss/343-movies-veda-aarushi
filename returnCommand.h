#ifndef RETURNCOMMAND_H
#define RETURNCOMMAND_H

#include "command.h"
#include "commandFactory.h"
#include <string>

class ReturnCommand : public Command {
private:
  int customerID;       // Customer ID associated with the return transaction
  std::string movieKey; // Unique key for identifying the movie

public:
  // Constructor: Initializes the return command with customer ID and movie key
  ReturnCommand(int id, std::string key);

  // Executes the return transaction for a customer
  void execute(MovieStore &store, CustomerDB &customers) override;

  // Destructor
  ~ReturnCommand() override {}
};

#endif
