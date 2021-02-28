#pragma once

#include "state.h"
#include "stateMachine.h"
#include "commandStateMachineState.h"

#include <string> // std::string
#include <memory> // std::shared_ptr

namespace z80 {
  /**
   * @brief Класс состояния "Обработка динамического блока команд".
   */
  class commandStateMachineStateDynamicBlock: public z80::commandStateMachineState {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    explicit commandStateMachineStateDynamicBlock(StateMachine& stateMachine);
    void inputAction(const std::string& iAction) override;

  private:
    void switchStateMachineToIdle() const;

    std::size_t nestingLevel = 0;
  };
}
