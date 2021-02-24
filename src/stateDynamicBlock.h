#pragma once

#include <string> // std::string
#include <memory> // std::shared_ptr

#include "state.h"

namespace z80 {
  class stateDynamicBlock: public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    stateDynamicBlock(std::shared_ptr<StateMachine> stateMachine);
    void inputAction(std::string&& iAction) override;
  };
}
