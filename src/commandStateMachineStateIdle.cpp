#include "commandStateMachineStateDynamicBlock.h"
#include "commandStateMachineStateIdle.h"
#include "commandStateMachineStateStaticBlock.h"

#include <memory>     // std::make_unique
#include <stdexcept>  // std::invalid_argument exception

using namespace std;
using namespace z80;

commandStateMachineStateIdle::commandStateMachineStateIdle(commandStateMachine* sm) :
commandStateMachineState(sm) {
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
  sm->setState(make_unique<commandStateMachineStateDynamicBlock>(csm));
}

void
commandStateMachineStateIdle::switchStateMachineToStaticBlock(const string& iAction) const {
  sm->setState(make_unique<commandStateMachineStateStaticBlock>(csm, iAction));
}
