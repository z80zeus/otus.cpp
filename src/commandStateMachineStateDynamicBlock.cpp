#include "commandStateMachineStateDynamicBlock.h"

#include "commandStateMachineStateIdle.h"
#include "commandStateMachine.h"

#include <memory> // std::make_unique

using namespace z80;
using namespace std;

commandStateMachineStateDynamicBlock::commandStateMachineStateDynamicBlock(commandStateMachine* sm):
  commandStateMachineState(sm),
  nestingLevel(1) {
}

void
commandStateMachineStateDynamicBlock::inputAction(const string& iAction) {
  if (iAction == "{") {         // Начало вложенного динамического блока команд.
    ++nestingLevel;             // Увеличить уровень вложенности.
    return;
  }

  if (iAction == "}")           // Конец динамического блока команд.
  {
    if (--nestingLevel) return; // Закончился вложенный блок - продолжить работу с динамическим блоком.

    // Конец динамического блока верхнего уровня.
    sendSavedCommands();
    switchStateMachineToIdle();
    return;
  }

  if (savedCommands.length()) savedCommands += ", ";
  savedCommands += iAction;
}

void
commandStateMachineStateDynamicBlock::switchStateMachineToIdle() const {
  sm->setState(make_unique<commandStateMachineStateIdle>(csm));
}
