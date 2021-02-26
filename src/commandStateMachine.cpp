#include "commandStateMachine.h"
#include "stateIdle.h"

#include <memory>
#include <iostream>

using namespace std;
using namespace z80;

commandStateMachine::commandStateMachine():
stateMachine<string>(),
subscriber<string>(),
publisher<string>()//, enable_shared_from_this<commandStateMachine>()
{
  // setState(make_unique<stateIdle>(shared_from_this()));
}

commandStateMachine::~commandStateMachine() {
  cout << "~commandStateMachine" << endl;
}

void
commandStateMachine::update(const std::string& command) {
  inputAction(command);
}

void
commandStateMachine::setStaticBlockSize(std::size_t blockSize) {
  staticBlockSize = blockSize;
}

std::size_t
commandStateMachine::getStaticBlockSize() {
  return staticBlockSize;
}