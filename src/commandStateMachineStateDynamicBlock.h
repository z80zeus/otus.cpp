/**
 * @brief Файл содержит объявление класса - состояния "Обработка динамического блока команд" для конечного автомата
 * z80::commandStateMachine.
 * @author Владимир Лазарев solock@mail.ru
 */
#pragma once

#include "commandStateMachine.h"
#include "commandStateMachineState.h"
#include "state.h"
#include "stateMachine.h"

#include <string> // std::string

namespace z80 {
  /**
   * @brief Класс состояния автомата "Обработка динамического блока команд" предназначен для работы с автоматом,
   * обрабатывающим строковые команды (z80::commandStateMachine) и наследуется от общего класса состояний автомата
   * данного вида - z80::commandStateMachineState.
   */
  class commandStateMachineStateDynamicBlock : public z80::commandStateMachineState {
  public:
    /**
     * @brief Конструктору состояния передаётся указатель на автомат, в контексте которого это состояние работает.
     * @param sm Указатель на объект-автомат.
     */
    explicit commandStateMachineStateDynamicBlock(z80::commandStateMachine* sm);

    /**
     * @brief Входное воздействие на автомат.
     * @param iAction В терминах данной работы входное воздействие - это строковая команда.
     * @details Этот метод переопределяет метод базового класса состояний и вызывается автоматом по приходу новой строки
     * (команды).
     */
    void inputAction(const std::string& iAction) override;

  private:
    /**
     * @brief Переключить автомат в состояние Idle. Это - служебная функция, вызываемая изнутри данного класса.
     */
    void switchStateMachineToIdle() const;

    /**
     * @brief Уровень вложенности динамического блока команд.
     * При появлении на входе символа '{' - увеличивается на 1.
     * При появлении на входе символа '}' - уменьшается на 1.
     * При достижении 0, объект-состояние передаёт накопленные команды автомату и переключает автомат в Idle.
     */
    std::size_t nestingLevel = 0;
  };
}
