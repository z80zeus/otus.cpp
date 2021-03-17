#include "commandStateMachineState.h"

using namespace z80;
using namespace std;

atomic<size_t>
commandStateMachineState::countPostfix = 0;

commandStateMachineState::commandStateMachineState(commandStateMachine* sm) :
state<string>(sm),
csm(sm),
blockStartTime(time(nullptr)),
startTimePostfix{++countPostfix} {
}

void
commandStateMachineState::setCStateMachine(z80::commandStateMachine* cStateMachine) {
  csm = cStateMachine;
}

void
commandStateMachineState::sendSavedCommands() {
  csm->notify(to_string(blockStartTime) + "." + to_string(startTimePostfix) + " " + savedCommands);
  savedCommands = "";
}

void
commandStateMachineState::finish() {}
