#pragma once

#include "state.h"
#include "stateMachine.h"
#include "commandStateMachine.h"

#include <string> // std::string
#include <memory> // std::shared_ptr

namespace z80 {
  /**
   * @brief Класс состояния "Обработка динамического блока команд".
   */
  class stateDynamicBlock: public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    explicit stateDynamicBlock(const std::weak_ptr<StateMachine>& stateMachine);
    ~stateDynamicBlock() noexcept override;
    void inputAction(const std::string& iAction) override;

  private:
    std::weak_ptr<commandStateMachine>  cStateMachine;
    std::string savedCommands;
  };
}
