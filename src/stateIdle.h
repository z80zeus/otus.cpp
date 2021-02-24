#pragma once

#include <memory>

#include "state.h"
//#include "stateMachine.h"

namespace z80 {
  class stateIdle: public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

   public:
    stateIdle(std::shared_ptr<StateMachine> stateMachine);
    void inputAction(std::string&& iAction) override;
  };
}