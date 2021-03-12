#include "commandStateMachine.h"
#include "commandStateMachineStateDynamicBlock.h"
#include "commandStateMachineStateIdle.h"
#include "commandStateMachineStateStaticBlock.h"

using namespace std;
using namespace z80;

commandStateMachineStateStaticBlock::commandStateMachineStateStaticBlock(StateMachine* sm, const string& iAction):
    commandStateMachineState(sm),
    blockSize { dynamic_cast<commandStateMachine*>(sm)->getStaticBlockSize() } {
  inputAction_(iAction);
}

// commandStateMachineStateStaticBlock::commandStateMachineStateStaticBlock(const commandStateMachineStateStaticBlock& sms) = default;

void
commandStateMachineStateStaticBlock::finish() {
  if (commandsCount) sendSavedCommands();
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
  sm->setState(make_unique<commandStateMachineStateIdle>(sm));
}

void
commandStateMachineStateStaticBlock::switchStateMachineToDynamicBlock() const {
  sm->setState(make_unique<commandStateMachineStateDynamicBlock>(sm));
}

//unique_ptr<state<string>>
//commandStateMachineStateStaticBlock::clone(StateMachine &s) const {
//  return make_unique<commandStateMachineStateStaticBlock>(*this);
//}