#pragma once

#include <memory>  // std::unique_ptr
#include <utility> // std::forward

#include "state.h"

namespace z80 {

  template<typename inputActionType>
  class state;

  template <typename inputActionType>
  class stateMachine {
    using State = z80::state<inputActionType>;

    public:

    void
    setState(std::unique_ptr<State>&& newState) {
      currentState = std::forward<std::unique_ptr<State>>(newState);
    };

    void
    inputAction(inputActionType&& command) {
      if (currentState)
        currentState->inputAction(std::forward<inputActionType>(command));
    };

    private:
    std::unique_ptr<State> currentState;
  };
}
