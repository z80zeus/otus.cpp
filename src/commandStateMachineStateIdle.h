#pragma once

#include "state.h"
#include "stateMachine.h"
#include "commandStateMachineState.h"

#include <memory> // std::shared_ptr

namespace z80 {
  /**
   * @brief Класс состояния "Холостой ход" (без команды).
   * @details Это - начальное состояние алгоритма и состояние алгоритма между блоками команд.
   */
  class commandStateMachineStateIdle: public z80::commandStateMachineState {
    using StateMachine = z80::stateMachine<std::string>;

   public:
    explicit commandStateMachineStateIdle(StateMachine& stateMachine);
    void inputAction(const std::string& iAction) override;

    private:
    void switchStateMachineToStaticBlock(const std::string& iAction) const;
    void switchStateMachineToDynamicBlock() const;
  };
}