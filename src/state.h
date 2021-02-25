#pragma once

#include <string> // std::string
#include <memory> // std::sharedPtr

#include "stateMachine.h"

namespace z80 {
  /**
   * @brief Базовый класс состояний класса stateMachine (конечный автомат).
   * @tparam inputActionType Тип данных, с которым работает конечный автомат.
   */
  template<typename inputActionType>
  class state {
    using StateMachine = stateMachine<inputActionType>;

    public:
    state(std::shared_ptr<StateMachine> stateMachine): sm(stateMachine) {};
    virtual ~state() = default;
    virtual void inputAction(inputActionType&& iAction) = 0;

  protected:
    std::shared_ptr<StateMachine> sm;
  };
}