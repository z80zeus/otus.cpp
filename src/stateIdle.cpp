#include "stateIdle.h"
#include "stateStaticBlock.h"
#include "stateDynamicBlock.h"

#include <stdexcept>  // std::invalid_argument exception
#include <utility>    // std::forward
#include <iostream>   // std::cout

using namespace std;
using namespace z80;

stateIdle::stateIdle(weak_ptr<stateMachine<basic_string<char>>> stateMachine):
state<string>::state (stateMachine) {
  cout << "stateIdle: begin." << endl;
}

void
stateIdle::inputAction(const string& iAction) {
  if (iAction == "{") {
    cout << "stateIdle: switch to stateDynamicBlock..." << endl;
    auto csm = sm.lock();
    if (csm) csm->setState(std::move(make_unique<stateDynamicBlock>(sm)));
    return;
  }

  if (iAction == "}") throw invalid_argument("Bad input");

  cout << "stateIdle: switch to stateStaticBlock..." << endl;
  auto csm = sm.lock();
  if (csm)
    csm->setState(std::move(make_unique<stateStaticBlock>(sm, iAction)));
}
