/**
 * @brief Файл содержит объявление шаблонного класса "Состояние" (state).
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "stateMachine.h"

#include <string> // std::string

namespace z80 {

  template<typename inputActionType>
  class stateMachine;

  /**
   * @brief Базовый класс состояний класса stateMachine (конечный автомат). Описывает интерфейс состояний конечного
   * автомата.
   * @tparam inputActionType Тип данных, с которым работает конечный автомат.
   */
  template<typename inputActionType>
  class state {
    using StateMachine = z80::stateMachine<inputActionType>;

  public:
    /**
     * @brief Конструктору состояния передаётся ссылка на автомат, в контексте которого он работает.
     * @param stateMachine Автомат, в контексте которого работает данное состояние.
     */
    explicit state(StateMachine& stateMachine) : sm(stateMachine) {};

    /**
     * @brief Деструктор полиморфного класса по-умолчанию.
     */
    virtual ~state() = default;

    /**
     * @brief В данную функцию своего текущего состояния автомат передаёт входное воздействие, принятое на свой вход.
     * @param iAction Входное воздействие, принятое автоматом.
     */
    virtual void inputAction(const inputActionType& iAction) = 0;

    /**
     * @brief Вызовом данной функции автомат оповещает состояние о завершении своей работы.
     */
    virtual void finish() = 0;

  protected:
    /**
     * @brief Ссылка на конечный автомат, с которым работает данное состояние.
     */
    StateMachine& sm;
  };
}
