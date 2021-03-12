/**
 * @brief Файл содержит объявление класса - состояния "Обработка динамического блока команд" для конечного автомата.
 * @author Владимир Лазарев solock@mail.ru
 */
#pragma once

#include "commandStateMachine.h"
#include "commandStateMachineState.h"
#include "state.h"
#include "stateMachine.h"

#include <memory> // std::shared_ptr
#include <string> // std::string

namespace z80 {
  /**
   * @brief Класс состояния автомата "Обработка динамического блока команд" предназначен для работы с автоматом,
   * обрабатывающим строковые команды и наследуется от общего класса состояний автомата данного вида -
   * z80::commandStateMachineState.
   */
  class commandStateMachineStateDynamicBlock : public z80::commandStateMachineState {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    /**
     * @brief Конструкту состояния передаётся ссылка на автомат, в контексте которого это состояние работает.
     * @param sm Ссылка на объект-автомат.
     */
    explicit commandStateMachineStateDynamicBlock(StateMachine* sm);

//    commandStateMachineStateDynamicBlock(const commandStateMachineStateDynamicBlock& sms);

    /**
     * @brief Входное воздействие на автомат.
     * @param iAction В терминах данной работы входное воздействие - это строковая команда.
     * @details Этот метод переопределяет метод базового класса состояний и вызывается автоматом по приходу новой строки
     * (команды).
     */
    void inputAction(const std::string& iAction) override;

//    std::unique_ptr<z80::state<std::string>> clone(StateMachine& s) const override;

  private:
    /**
     * @brief Переключить машину в состояние Idle. Это - служебная функция, вызываемая изнутри данного класса.
     */
    void switchStateMachineToIdle() const;

    /**
     * @brief Уровень вложенности динамического блока команд.
     * При появлении на входе символа '{' - увеличивается на 1.
     * При появлении на входе символа '}' - уменьшается на 1.
     * При достижении 0 - накопленные команды блока передаются автомату и автомат переключается в Idle.
     */
    std::size_t nestingLevel = 0;
  };
}
