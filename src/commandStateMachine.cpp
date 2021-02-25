#include "commandStateMachine.h"

using namespace std;
using namespace z80;

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