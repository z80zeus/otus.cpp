#include "commandStateMachine.h"
#include "commandStateMachineStateIdle.h"

#include <memory> // std::make_unique

using namespace z80;
using namespace std;

commandStateMachine::commandStateMachine() :
    stateMachine<string>(),
    subscriber<string>(),
    publisher<string>() {
  setState(make_unique<commandStateMachineStateIdle>(*this));
}

void
commandStateMachine::update(const string& command) {
  inputAction(command);
}

void
commandStateMachine::unsubscribed() {
  currentState->finish();
}

void
commandStateMachine::setStaticBlockSize(size_t blockSize) {
  staticBlockSize = blockSize;
}

size_t
commandStateMachine::getStaticBlockSize() {
  return staticBlockSize;
}
