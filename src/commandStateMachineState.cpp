#include "commandStateMachineState.h"
#include "publisher.h"

using namespace z80;
using namespace std;

using Publisher = publisher<string>;

commandStateMachineState::commandStateMachineState(StateMachine* sm) :
state<string>(sm),
//cStateMachine(csm),
blockStartTime(time(nullptr)) {}

//commandStateMachineState::commandStateMachineState(const commandStateMachineState& csms):
//state<string>(csms.sm),
//cStateMachine(csms.cStateMachine),
//blockStartTime(csms.blockStartTime) {};

void
commandStateMachineState::sendSavedCommands() {
  dynamic_cast<Publisher*>(sm)->notify(to_string(blockStartTime) + " " + savedCommands);
  savedCommands = "";
}

void
commandStateMachineState::finish() {}
