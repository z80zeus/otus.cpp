#include "commandStateMachine.h"

using namespace std;
using namespace z80;

void
commandStateMachine::update(const std::string& command) {
  inputAction(command);
}
