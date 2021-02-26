#include "stateStaticBlock.h"
#include "stateIdle.h"
#include "commandStateMachine.h"

#include <typeinfo> // std::bad_cast
#include <iostream> // std::cout

using namespace std;
using namespace z80;

stateStaticBlock::stateStaticBlock(const weak_ptr<StateMachine>& stateMachine, const std::string& iAction):
state<string>(stateMachine) {
  cout << "stateStaticBlock: begin." << endl;
  cStateMachine = static_pointer_cast<commandStateMachine>(sm.lock());
  if (!cStateMachine.lock()) throw bad_cast();
  blockSize = cStateMachine.lock()->getStaticBlockSize();
  addInputAction(iAction);
}

stateStaticBlock::~stateStaticBlock() {
  if (commandsCount) {
    cout << "~stateStaticBlock: end. Commands = " << savedCommands << endl;
    auto csm = cStateMachine.lock();
    if (csm) csm->notify(savedCommands);
  }
}

void
stateStaticBlock::inputAction(const string& iAction) {
  addInputAction(iAction);
}

void
stateStaticBlock::addInputAction(const string& iAction) {
  if (savedCommands.length()) savedCommands+= ", ";
  savedCommands += iAction;
  cout << "stateStaticBlock: Commands = " << savedCommands << endl;
  if (++commandsCount < blockSize) return;

  cout << "stateStaticBlock: end." << endl;
  auto csm = cStateMachine.lock();
  if (csm) csm->notify(savedCommands);

  savedCommands = "";
  commandsCount = 0;
  cout << "stateStaticBlock: switch to stateIdle..." << endl;
  auto ssm = sm.lock();
  if (ssm) ssm->setState(make_unique<stateIdle>(sm));
}