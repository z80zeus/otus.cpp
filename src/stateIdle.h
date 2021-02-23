#pragma once

#include "state.h"
#include "stateMachine.h"

namespace z80 {
  class stateIdle: public z80::state<std::string> {
    using stateMadhinePtr = std::shared_ptr<z80::stateMachine<std::string>;

    public:
    stateIdle(std::shared_ptr<z80::stateMachine<std::string> )
    void inputAction(const std::string& iAction) override;
  };
}