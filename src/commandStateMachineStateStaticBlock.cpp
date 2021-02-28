#include "commandStateMachine.h"
#include "commandStateMachineStateDynamicBlock.h"
#include "commandStateMachineStateIdle.h"
#include "commandStateMachineStateStaticBlock.h"



using namespace std;
using namespace z80;

commandStateMachineStateStaticBlock::commandStateMachineStateStaticBlock(StateMachine& stateMachine, const std::string& iAction):
commandStateMachineState(stateMachine) {
  blockSize = cStateMachine.getStaticBlockSize();
  addInputAction(iAction);
}

void
commandStateMachineStateStaticBlock::finish() {
  if (commandsCount) sendSavedCommands();
}

void
commandStateMachineStateStaticBlock::inputAction(const string& iAction) {
  addInputAction(iAction);
}

void
commandStateMachineStateStaticBlock::addInputAction(const string& iAction) {
  if (iAction == "{") {
    savedCommands += " ";
    savedCommands += asctime(localtime(&blockStartTime));
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
  sm.setState(make_unique<commandStateMachineStateIdle>(sm));
}

void
commandStateMachineStateStaticBlock::switchStateMachineToDynamicBlock() const {
  sm.setState(make_unique<commandStateMachineStateDynamicBlock>(sm));
}
