#include "stateDynamicBlock.h"

#include "stateIdle.h"
#include "commandStateMachine.h"

#include <memory>   // std::make_unique
#include <typeinfo> // std::static_pointer_cast
#include <iostream> // std::cout

using namespace std;
using namespace z80;

stateDynamicBlock::stateDynamicBlock(const std::weak_ptr<StateMachine>& stateMachine):
state<std::string>(stateMachine) {
  cout << "stateDynamicBlock: begin." << endl;
  cStateMachine = static_pointer_cast<commandStateMachine>(sm.lock());
  if (!cStateMachine.lock()) throw bad_cast();
}

stateDynamicBlock::~stateDynamicBlock() noexcept {
  if (savedCommands.length()) {
    cout << "~stateDynamicBlock: end. Commands = " << savedCommands << endl;
    auto csm = cStateMachine.lock();
    if (csm) csm->notify(savedCommands);
  }
}

void
stateDynamicBlock::inputAction(const std::string& iAction) {
  if (iAction == "}") {
    cout << "stateDynamicBlock: end. Commands = " << savedCommands << endl;
    cStateMachine.lock()->notify(savedCommands);
    savedCommands = "";
    cout << "stateDynamicBlock: switch to stateIdle..." << endl;
    auto csm = sm.lock();
    if (csm) csm->setState(make_unique<stateIdle>(sm));
    return;
  }

  if (savedCommands.length()) savedCommands+= ", ";
  savedCommands += iAction;
}
