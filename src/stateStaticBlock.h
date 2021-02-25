#pragma once

#include <string> // std::string
#include <memory> // std::shared_ptr
#include <queue>

#include "state.h"

namespace z80 {
  /**
   * @brief Класс состояния "Обработка статического блока команд".
   */
  class stateStaticBlock : public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    stateStaticBlock(std::shared_ptr<StateMachine> stateMachine, std::string&& iAction);

    void inputAction(std::string&& iAction) override;

  private:
    std::queue<std::string>       input;
  };
}
