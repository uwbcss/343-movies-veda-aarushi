#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// forward declaration
class Command;

// Abstract CommandFactory where each subclass of Command needs its own concrete version
class CommandFactory { // implemented in command
public:
  virtual Command *makeCommand(const vector<string> &vs) const = 0;

  // find the corresponding command factory and get factory to create the object
  static Command *create(const char &cmd, const vector<string>& vs);

protected:
  // register a concrete factory with a given name
  static void registerType(const char &type, CommandFactory *factory);

private:
  /**
   * Storage place for the concrete command factories
   * @return map
   */
  static map<char, CommandFactory *> &getMap();
};

#endif // COMMAND_FACTORY_H