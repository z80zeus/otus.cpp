#include "stateIdle.h"
#include "stateStaticBlock.h"
#include "stateDynamicBlock.h"

#include <stdexcept>  // std::invalid_argument exception
#include <utility>    // std::forward

using namespace std;
using namespace z80;

stateIdle::stateIdle(const shared_ptr<StateMachine>& stateMachine):
state<string>::state (stateMachine) {
}

void
stateIdle::inputAction(const string& iAction) {
  if (iAction == "{") {
    sm->setState(std::move(make_unique<stateDynamicBlock>(sm)));
    return;
  }

  if (iAction == "}") throw invalid_argument("Bad input");

  sm->setState(std::move(make_unique<stateStaticBlock>(sm, iAction)));
}
