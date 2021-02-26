#pragma once

#include "state.h"
#include "stateMachine.h"

#include <memory> // std::shared_ptr

namespace z80 {
  /**
   * @brief Класс состояния "Холостой ход" (без команды).
   * @details Это - начальное состояние алгоритма и состояние алгоритма между блоками команд.
   */
  class stateIdle: public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

   public:
    explicit stateIdle(std::weak_ptr<StateMachine> stateMachine);
    void inputAction(const std::string& iAction) override;
  };
}