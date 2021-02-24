#include "stateDynamicBlock.h"

#include "stateIdle.h"

using namespace std;
using namespace z80;

stateDynamicBlock::stateDynamicBlock(std::shared_ptr<StateMachine> stateMachine):
state<std::string>(stateMachine) {
}

void
stateDynamicBlock::inputAction(std::string&& iAction) {
  if (iAction == "}") {
    sm->setState(make_unique<stateIdle>(sm));
    return;
  }
}
