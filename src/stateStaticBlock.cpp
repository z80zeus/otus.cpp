#include "stateStaticBlock.h"
#include "stateIdle.h"
#include "commandStateMachine.h"

#include <typeinfo> // std::bad_cast

using namespace std;
using namespace z80;

stateStaticBlock::stateStaticBlock(const shared_ptr<StateMachine>& stateMachine, const std::string& iAction):
state<string>(stateMachine) {
  cStateMachine = static_pointer_cast<commandStateMachine>(stateMachine);
  if (!cStateMachine) throw bad_cast();
  blockSize = cStateMachine->getStaticBlockSize();
  addInputAction(iAction);
}

stateStaticBlock::~stateStaticBlock() {
  if (commandsCount)
    cStateMachine->notify(savedCommands);
}

void
stateStaticBlock::inputAction(const string& iAction) {
  addInputAction(iAction);
}

void
stateStaticBlock::addInputAction(const string& iAction) {
  if (savedCommands.length()) savedCommands+= ", ";
  savedCommands += iAction;
  if (++commandsCount < blockSize) return;

  cStateMachine->notify(savedCommands);

  savedCommands = "";
  commandsCount = 0;
  cStateMachine->setState(make_unique<stateIdle>(sm));
}