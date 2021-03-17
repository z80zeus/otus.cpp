/**
 * @brief Файл содержит описание шаблонного класса "Состояние" (state) конечного автомата z80::stateMachine.
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "stateMachine.h"

namespace z80 {

  template<typename inputActionType>
  class stateMachine;

  /**
   * @brief Базовый класс состояний конечного автомата stateMachine. Описывает основной интерфейс состояний.
   * @tparam inputActionType Тип данных, с которым работает конечный автомат.
   */
  template<typename inputActionType>
  class state {
    using StateMachine = z80::stateMachine<inputActionType>;

  public:
    /**
     * @brief Конструктору состояния передаётся указатель на автомат, в контексте которого он работает.
     * @param stateMachine Автомат, в контексте которого работает данное состояние.
     */
    explicit state(StateMachine* stateMachine) : sm{stateMachine} {};

    /**
     * @brief Полиморфному классу необходим деструктор. Для данного класса достаточно реализации по-умолчанию.
     */
    virtual ~state() = default;

    /**
     * @brief В данную функцию автомат передаёт входное воздействие, полученное на свой вход.
     * @param iAction Входное воздействие, принятое автоматом, требуещее обработки алгоритмом состояния.
     */
    virtual void inputAction(const inputActionType& iAction) = 0;

    /**
     * @brief Вызовом данной функции автомат оповещает состояние о завершении своей работы. Состоянию следует завершить
     * свой алгоритм.
     */
    virtual void finish() = 0;

    /**
     * @brief Указать состоянию указатель на новый автомат, в контексте которого теперь будет работать состояние.
     * @param sMachine Новый указатель на автомат - владельца состояния.
     * @details Эта функция вызывается при перемещении автомата, когда меняется его позиция в памяти и об этом требуется
     * оповестить состояние.
     */
    virtual void setStateMachine(StateMachine* sMachine) {
      sm = sMachine;
    }

  protected:
    /**
     * @brief Указатель на конечный автомат, с которым работает данное состояние.
     */
    StateMachine* sm = nullptr;
  };
}
