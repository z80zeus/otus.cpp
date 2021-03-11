/**
 * @brief Файл содержит объявление шаблонного класса "Состояние" (state).
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "stateMachine.h"

#include <memory> // std::unique_ptr
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
    explicit state(StateMachine& stateMachine) : sm{stateMachine} {};

    /**
     * @brief Копирующий конструктор копирует из исходного объекта ссылку на автомат.
     * @param s Ссылка на объект на основе которого создаётся новый объект state.
     */
    state (const z80::state<inputActionType>& s) = default;

    /**
     * @brief Клонирование объекта state. Это требуется при копировании машин для передачи в новую машину текущего состояния.
     * @param s Машина к которой привязывается вновь создаваемый объект.
     * @return
     */
    virtual std::unique_ptr<z80::state<inputActionType>> clone(StateMachine& s) const = 0;

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

    virtual void setStateMachine(z80::stateMachine<inputActionType>& sMachine) {
      sm = sMachine;
    }

  protected:
    /**
     * @brief Ссылка на конечный автомат, с которым работает данное состояние.
     */
    StateMachine& sm;
  };
}
