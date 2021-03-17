#include "commandStateMachine.h"
#include "commandStateMachineStateDynamicBlock.h"
#include "commandStateMachineStateIdle.h"
#include "commandStateMachineStateStaticBlock.h"

#include <memory> // std::make_unique

using namespace std;
using namespace z80;

commandStateMachineStateStaticBlock::commandStateMachineStateStaticBlock(commandStateMachine* sm, const string& iAction):
commandStateMachineState(sm),
blockSize { sm->getStaticBlockSize() } {
  inputAction_(iAction);
}

void
commandStateMachineStateStaticBlock::finish() {
  if (commandsCount) sendSavedCommands();
  commandsCount = 0;
}

void
commandStateMachineStateStaticBlock::inputAction(const string& iAction) {
  inputAction_(iAction);
}

void
commandStateMachineStateStaticBlock::inputAction_(const std::string& iAction) {
  if (iAction == "{") {
    sendSavedCommands();
    commandsCount = 0;
    switchStateMachineToDynamicBlock();
    return;
  }

  if (savedCommands.length()) savedCommands += ", ";
  savedCommands += iAction;
  if (++commandsCount < blockSize) return;

  sendSavedCommands();
  commandsCount = 0;
  switchStateMachineToIdle();
}

void
commandStateMachineStateStaticBlock::switchStateMachineToIdle() const {
  sm->setState(make_unique<commandStateMachineStateIdle>(csm));
}

void
commandStateMachineStateStaticBlock::switchStateMachineToDynamicBlock() const {
  sm->setState(make_unique<commandStateMachineStateDynamicBlock>(csm));
}
