/**
 * @brief Файл содержит объявление класса - состояния "Холостой ход" для конечного автомата z80::commandStateMachine.
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "commandStateMachineState.h"
#include "state.h"
#include "stateMachine.h"

#include <string> // std::string

namespace z80 {
  /**
   * @brief Класс состояния автомата "Холостой ход" предназначен для работы с автоматом, обрабатывающим строковые
   * команды (z80::commandStateMachine) и наследуется от общего класса состояний автомата данного вида -
   * z80::commandStateMachineState.
   */
  class commandStateMachineStateIdle : public z80::commandStateMachineState {
  public:
    /**
     * @brief Конструктору состояния передаётся указатель на автомат, в контексте которого это состояние работает.
     * @param sm Указатель на объект-автомат.
     */
    explicit commandStateMachineStateIdle(z80::commandStateMachine* sm);

    /**
     * @brief Входное воздействие на автомат.
     * @param iAction В терминах данной работы входное воздействие - это строковая команда.
     * @details Этот метод переопределяет метод базового класса состояний и вызывается автоматом по приходу новой строки
     * (команды).
     */
    void inputAction(const std::string& iAction) override;

  private:
    /**
     * @brief Переключить автомат в состояние StaticBLock. Это - служебная функция, вызываемая изнутри данного класса.
     * @details Вызывается по приходу любой команды, кроме команд начала/конца динамического блока: "{" / "}".
     */
    void switchStateMachineToStaticBlock(const std::string& iAction) const;

    /**
     * @brief Переключить автомат в состояние DynamicBLock. Это - служебная функция, вызываемая изнутри данного класса.
     * @details Вызывается по приходу команды начала динамического блока: "{".
     */
    void switchStateMachineToDynamicBlock() const;
  };
}