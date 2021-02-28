#include "commandStateMachineState.h"

using namespace z80;
using namespace std;

commandStateMachineState::commandStateMachineState(StateMachine& stateMachine):
state<string>(stateMachine),
cStateMachine(static_cast<commandStateMachine&>(stateMachine)),
blockStartTime(time(nullptr)) {}

void
commandStateMachineState::sendSavedCommands() {
  static_cast<commandStateMachine&>(sm).notify(to_string(blockStartTime) + " " + savedCommands);
  savedCommands = "";
}

void
commandStateMachineState::finish() {}