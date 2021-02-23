#pragma once

#include <memory>

#include "state.h"

namespace z80 {
  template <typename inputActionType>
  class stateMachine {
    using State = std::unique_ptr<z80::state<inputActionType>>;

    public:

    void setState(State newState) {
      currentState = newState;
    };

    void inputAction(const commandType& command) {
      if (currentState)
        currentState->inputAction(command);
    };

    private:
    State currentState;
  };
}
