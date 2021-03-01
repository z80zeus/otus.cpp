/**
 * @brief Файл содержит объявление шаблонного класса "Конечный автомат" (stateMachine).
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
   * @tparam inputActionType Тип данных, с которым работает алгоритм.
   * @details Данный класс не реализует никакого конкретного алгоритма. Он содержит базовый функционал работы конечного
   * автомата:
   * 1. Хранит текущее состояние.
   * 2. Передаёт текущему состоянию входное воздействие.
   * 3. Изменяет текущее состояние по команде (в т.ч. самогО состояния).
   */
  template<typename inputActionType>
  class stateMachine {
    using State = z80::state<inputActionType>;

  public:
    /**
     * @brief Установить новое состояние автомата.
     * @param newState Указатель на объект-состояние.
     */
    void setState(std::unique_ptr<State>&& newState) {
      currentState = std::forward<std::unique_ptr<State>> (newState);
    };

    /**
     * @brief Входное воздействие на автомат.
     * @param command Ссылка на объект воздействия.
     * @details Автомат не содержит логики своей работы, поэтому делегирует обработку воздействия текущему объекту-состоянию.
     */
    void inputAction(const inputActionType& command) {
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
