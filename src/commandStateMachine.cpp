#include "commandStateMachine.h"
#include "commandStateMachineStateIdle.h"
#include "state.h"

#include <memory> // std::make_unique

using namespace z80;
using namespace std;

commandStateMachine::commandStateMachine() :
  stateMachine<string>(),
  subscriber<string>(),
  publisher<string>() {
  setState(make_unique<commandStateMachineStateIdle>(this));
}

commandStateMachine::commandStateMachine(commandStateMachine&& csm) noexcept:
  stateMachine<string>(std::forward<commandStateMachine>(csm)),
  subscriber<string>(),
  publisher<string>(),
  staticBlockSize(csm.staticBlockSize) {
}

//commandStateMachine::~commandStateMachine() noexcept {
//  if (currentState)
//    currentState->finish();
//}

commandStateMachine&
commandStateMachine::operator=(const commandStateMachine& csm) {
  stateMachine<string>::operator=(csm);
  staticBlockSize = csm.staticBlockSize;
  return *this;
}

void
commandStateMachine::update(const string& command) {
  inputAction(command);
}

//void
//commandStateMachine::unsubscribed() {
//  if (currentState)
//    currentState->finish();
//}

void
commandStateMachine::setStaticBlockSize(size_t blockSize) {
  staticBlockSize = blockSize;
}

size_t
commandStateMachine::getStaticBlockSize() const {
  return staticBlockSize;
}
