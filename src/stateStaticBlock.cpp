#include <utility>  // std::forward

#include "stateStaticBlock.h"

using namespace std;
using namespace z80;

stateStaticBlock::stateStaticBlock(shared_ptr<StateMachine> stateMachine, std::string&& iAction):
state<string>(stateMachine){
  input.emplace(std::forward<string>(iAction));
}

void
stateStaticBlock::inputAction(std::string&& iAction) {
  input.emplace(std::forward<string>(iAction));
}
