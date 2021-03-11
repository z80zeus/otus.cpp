/**
 * @brief Файл содержит объявление класса - состояния "Холостой ход" для конечного автомата.
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "commandStateMachineState.h"
#include "state.h"
#include "stateMachine.h"

#include <memory> // std::shared_ptr
#include <string> // std::string

namespace z80 {
  /**
   * @brief Класс состояния автомата "Холостой ход" предназначен для работы с автоматом, обрабатывающим строковые
   * команды и наследуется от общего класса состояний автомата данного вида - z80::commandStateMachineState.
   */
  class commandStateMachineStateIdle : public z80::commandStateMachineState {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    /**
     * @brief Конструкту состояния передаётся ссылка на автомат, в контексте которого это состояние работают.
     * @param stateMachine Ссылка на объект-автомат.
     */
    explicit commandStateMachineStateIdle(commandStateMachine& stateMachine);

    commandStateMachineStateIdle(const commandStateMachineStateIdle& sms);

    /**
     * @brief Входное воздействие на автомат.
     * @param iAction В терминах данной работы входное воздействие - это строковая команда.
     * @details Этот метод переопределяет метод базового класса состояний и вызывается автоматом по приходу новой строки
     * (команды).
     */
    void inputAction(const std::string& iAction) override;

    std::unique_ptr<z80::state<std::string>> clone(StateMachine& s) const override;

  private:
    /**
     * @brief Переключить машину в состояние StaticBLock. Это - служебная функция, вызываемая изнутри данного класса.
     * @details Вызывается по приходу любой команды, кроме команд начала/конца динамического блока: "{" / "}".
     */
    void switchStateMachineToStaticBlock(const std::string& iAction) const;

    /**
     * @brief Переключить машину в состояние DynamicBLock. Это - служебная функция, вызываемая изнутри данного класса.
     * @details Вызывается по приходу команды начала динамического блока: "{".
     */
    void switchStateMachineToDynamicBlock() const;
  };
}