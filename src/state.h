#pragma once

#include "stateMachine.h"

#include <string> // std::string
#include <memory> // std::sharedPtr

namespace z80 {

  template<typename inputActionType>
  class stateMachine;

  /**
   * @brief Базовый класс состояний класса stateMachine (конечный автомат).
   * @tparam inputActionType Тип данных, с которым работает конечный автомат.
   */
  template<typename inputActionType>
  class state {
    using StateMachine = z80::stateMachine<inputActionType>;

    public:
    explicit state(StateMachine& stateMachine): sm(stateMachine) {};
    virtual ~state() = default;
    virtual void inputAction(const inputActionType& iAction) = 0;
    virtual void finish () = 0;

  protected:
    StateMachine& sm;
  };
}