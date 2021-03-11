#include "commandStateMachineStateDynamicBlock.h"

#include "commandStateMachineStateIdle.h"
#include "commandStateMachine.h"

using namespace z80;
using namespace std;

commandStateMachineStateDynamicBlock::commandStateMachineStateDynamicBlock(commandStateMachine& stateMachine):
    commandStateMachineState(stateMachine),
    nestingLevel(1) {
}

commandStateMachineStateDynamicBlock::commandStateMachineStateDynamicBlock(const commandStateMachineStateDynamicBlock& sms) = default;

void
commandStateMachineStateDynamicBlock::inputAction(const string& iAction) {
  if (iAction == "{") {         // Начало вложенного динамического блока команд.
    ++nestingLevel;             // Увеличить уровень вложенности.
    return;
  }

  if (iAction == "}")           // Конец динамического блока команд.
  {
    if (--nestingLevel)         // Закончился вложенный блок
      return;                   // Подолжить работу с динамическим блоком.
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
  sm.setState(make_unique<commandStateMachineStateIdle>(cStateMachine));
}

unique_ptr<state<string>>
commandStateMachineStateDynamicBlock::clone(StateMachine& s) const {
  return make_unique<commandStateMachineStateDynamicBlock>(*this);
}
