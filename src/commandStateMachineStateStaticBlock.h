#pragma once

#include "state.h"
#include "stateMachine.h"
#include "commandStateMachine.h"
#include "commandStateMachineState.h"

#include <string> // std::string
#include <memory> // std::shared_ptr

namespace z80 {
  /**
   * @brief Класс состояния "Обработка статического блока команд".
   */
  class commandStateMachineStateStaticBlock : public z80::commandStateMachineState {
    using StateMachine = stateMachine<std::string>;

  public:
    commandStateMachineStateStaticBlock(StateMachine& stateMachine, const std::string& iAction);

    void inputAction(const std::string& iAction) override;

    void finish() override;

  private:
    void addInputAction(const std::string& iAction);

    void switchStateMachineToIdle() const;

    void switchStateMachineToDynamicBlock() const;

    std::size_t commandsCount = 0;
    std::size_t blockSize = 3;
  };
}
