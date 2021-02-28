#pragma once

#include "state.h"

#include <memory>  // std::unique_ptr
#include <utility> // std::forward
#include <iostream>


namespace z80 {

  template<typename inputActionType>
  class state;

  /**
   * @brief Базовый класс содержащий реализацию алгоритма работы конечного автомата.
   * @tparam inputActionType Тип данных, с которым работает алгоритм.
   * @details Данный класс не реализует никакого конкретного алгоритма. Он является базовым и реализует базовый
   * функционал работы конечного автомата:
   * 1. Хранит текущее состояние.
   * 2. Передаёт текущему состоянию входное воздействие.
   * 3. Изменяет текущее состояние по команде (в т.ч. самогО состояния).
   */
  template <typename inputActionType>
  class stateMachine {
    using State = z80::state<inputActionType>;

    public:

    void
    setState(std::unique_ptr<State>&& newState) {
      currentState = std::forward<std::unique_ptr<State>>(newState);
    };

    void
    inputAction(const inputActionType& command) {
      if (currentState)
        currentState->inputAction(command);
    };

    protected:
    std::unique_ptr<State> currentState;
  };
}
