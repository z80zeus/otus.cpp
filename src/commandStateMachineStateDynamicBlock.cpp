#include "commandStateMachineStateDynamicBlock.h"

#include "commandStateMachineStateIdle.h"
#include "commandStateMachine.h"

#include <memory>   // std::make_unique
#include <typeinfo> // std::static_pointer_cast
#include <iostream> // std::cout

using namespace std;
using namespace z80;

commandStateMachineStateDynamicBlock::commandStateMachineStateDynamicBlock(StateMachine& stateMachine):
commandStateMachineState(stateMachine),
nestingLevel(1) {
}

void
commandStateMachineStateDynamicBlock::inputAction(const std::string& iAction) {
  if (iAction == "{") {         // Начало вложенного динамического блока команд. Увеличить уровень вложенности.
    ++nestingLevel;
    return;
  }

  if (iAction == "}")           // Динамический блок команд закрывается
  {
    if (--nestingLevel) return; // Закрылся вложенный блок - продолжить работу с динамическим блоком.

    sendSavedCommands();
    switchStateMachineToIdle();
    return;
  }

  if (savedCommands.length()) savedCommands += ", ";
  savedCommands += iAction;
}

void
commandStateMachineStateDynamicBlock::switchStateMachineToIdle() const {
  sm.setState(make_unique<commandStateMachineStateIdle>(sm));
//  auto csm = sm.lock();
//  if (csm) csm->setState(make_unique<commandStateMachineStateIdle>(sm));
}
