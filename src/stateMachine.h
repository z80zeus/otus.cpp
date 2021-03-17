/**
 * @brief Файл содержит описание шаблонного класса "Конечный автомат" (stateMachine), обрабатывающего входные воздействия.
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "state.h"

#include <memory>  // std::unique_ptr
#include <utility> // std::forward

namespace z80 {

  template<typename inputActionType>
  class state;

  /**
   * @brief Базовый класс содержащий реализацию алгоритма работы конечного автомата.
   * @tparam inputActionType Тип данных, с которым работает алгоритм. Данные этого типа поступают на вход автомату.
   * @details Данный класс не реализует никакого конкретного алгоритма. Он содержит базовый функционал работы конечного
   * автомата:
   * 1. Хранит текущее состояние.
   * 2. Передаёт текущему состоянию входное воздействие.
   * 3. Изменяет текущее состояние по команде (в т.ч. самогО состояния).
   */
  template<typename inputActionType>
  class stateMachine {
    using State = z80::state<inputActionType>;
    using StateMachine = z80::stateMachine<inputActionType>;

  public:
    stateMachine() = default;

    /**
     * @brief Перемещающий конструктор перемещеает из автомата-источника к себе его текущее состояние и указывает этому
     * состоянию свой адрес в качестве адреса его нового автомата.
     * @param sm Автомат-источник.
     */
    stateMachine(StateMachine&& sm) noexcept : currentState(std::move(sm.currentState)) {
      currentState->setStateMachine(this);
    }

    /**
     * @brief Деструктор даёт текущему состоянию автомата команду завершения работы.
     */
    virtual ~stateMachine() {
      if (currentState)
        currentState->finish();
    };

    /**
     * @brief Останов автомата. Команда передаётся текущему состоянию автомата.
     */
    virtual void stop() {
      if (currentState)
        currentState->finish();
    };

    /**
     * @brief Установить новое состояние автомата.
     * @param newState Указатель на объект-состояние.
     */
    void
    setState(std::unique_ptr<State>&& newState) {
      currentState = std::forward<std::unique_ptr<State>> (newState);
    };

    /**
     * @brief Входное воздействие на автомат.
     * @param command Ссылка на объект воздействия.
     * @details Автомат не содержит логики своей работы: вся логика находится в классах-состояниях автомата.
     * Поэтому автомат делегирует обработку воздействия текущему объекту-состоянию.
     */
    void
    inputAction(const inputActionType& command) {
      if (currentState)
        currentState->inputAction(command);
    };

  protected:
    /**
     * @brief Указатель на текущее состояние автомата.
     */
    std::unique_ptr<State> currentState;
  };
}
