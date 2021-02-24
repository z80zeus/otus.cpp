#include <stdexcept>  // std::invalid_argument exception
#include <utility>    // std::forward

#include "stateIdle.h"
#include "stateStaticBlock.h"
#include "stateDynamicBlock.h"

using namespace std;
using namespace z80;

stateIdle::stateIdle(shared_ptr<StateMachine> stateMachine):
state<string>::state (stateMachine) {
}

void
stateIdle::inputAction(string&& iAction) {
  if (iAction == "{") {
    sm->setState(std::move(make_unique<stateDynamicBlock>(sm)));
    return;
  }

  if (iAction == "}") throw new invalid_argument("Bad input");

  sm->setState(std::move(make_unique<stateStaticBlock>(sm, forward<string>(iAction))));
}
