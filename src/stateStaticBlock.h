#pragma once

#include "state.h"
#include "stateMachine.h"
#include "commandStateMachine.h"

#include <string> // std::string
#include <memory> // std::shared_ptr

namespace z80 {
  /**
   * @brief Класс состояния "Обработка статического блока команд".
   */
  class stateStaticBlock : public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    stateStaticBlock(const std::weak_ptr<StateMachine>& stateMachine, const std::string& iAction);
    ~stateStaticBlock() override;

    void inputAction(const std::string& iAction) override;

  private:
    void addInputAction (const std::string& iAction);

    std::weak_ptr<commandStateMachine>  cStateMachine;
    std::string   savedCommands;
    std::size_t   commandsCount = 0;
    std::size_t   blockSize     = 3;
  };
}
