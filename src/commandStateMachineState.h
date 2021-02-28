#pragma once

#include "commandStateMachine.h"
#include "state.h"
#include "stateMachine.h"

#include <string> // std::string
#include <ctime>  // std::time_t

namespace z80 {
  class commandStateMachineState: public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

    public:
    void finish () override;

    protected:
    explicit commandStateMachineState(StateMachine& stateMachine);
    void sendSavedCommands();
    std::string savedCommands;
    z80::commandStateMachine&  cStateMachine;
    std::time_t   blockStartTime;
  };
}