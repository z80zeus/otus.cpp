#include "commandStateMachineState.h"

using namespace z80;
using namespace std;

commandStateMachineState::commandStateMachineState(commandStateMachine* csm) :
state<string>(csm),
cStateMachine(csm),
blockStartTime(time(nullptr)) {}

commandStateMachineState::commandStateMachineState(const commandStateMachineState& csms):
state<string>(csms.sm),
cStateMachine(csms.cStateMachine),
blockStartTime(csms.blockStartTime) {};

void
commandStateMachineState::sendSavedCommands() {
  cStateMachine->notify(to_string(blockStartTime) + " " + savedCommands);
  savedCommands = "";
}

void
commandStateMachineState::finish() {}

void
commandStateMachineState::setStateMachine(stateMachine<std::string>* sMachine) {
  state::setStateMachine(sMachine);
  cStateMachine = dynamic_cast<commandStateMachine*>(sm);
}