#include "commandStateMachineStateDynamicBlock.h"
#include "commandStateMachineStateIdle.h"
#include "commandStateMachineStateStaticBlock.h"

#include <stdexcept>  // std::invalid_argument exception

using namespace std;
using namespace z80;

commandStateMachineStateIdle::commandStateMachineStateIdle(StateMachine& stateMachine) :
    commandStateMachineState(stateMachine) {
}

void
commandStateMachineStateIdle::inputAction(const string& iAction) {
  if (iAction == "{") {
    switchStateMachineToDynamicBlock();
    return;
  }

  if (iAction == "}") throw invalid_argument("Bad input");

  switchStateMachineToStaticBlock(iAction);
}

void
commandStateMachineStateIdle::switchStateMachineToDynamicBlock() const {
  sm.setState(make_unique<commandStateMachineStateDynamicBlock>(sm));
}

void
commandStateMachineStateIdle::switchStateMachineToStaticBlock(const std::string& iAction) const {
  sm.setState(make_unique<commandStateMachineStateStaticBlock>(sm, iAction));
}
