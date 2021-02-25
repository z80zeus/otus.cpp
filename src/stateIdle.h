#pragma once

#include <memory>

#include "state.h"

namespace z80 {
  /**
   * @brief Класс состояния "Холостой ход" (без команды).
   * @details Это - начальное состояние алгоритма и состояние алгоритма между блоками команд.
   */
  class stateIdle: public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

   public:
    stateIdle(std::shared_ptr<StateMachine> stateMachine);
    void inputAction(std::string&& iAction) override;
  };
}