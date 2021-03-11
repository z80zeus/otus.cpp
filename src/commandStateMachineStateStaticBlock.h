/**
 * @brief Файл содержит объявление класса - состояния "Обработка статического блока команд" для конечного автомата.
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
   * @brief Класс состояния автомата "Обработка статического блока команд" предназначен для работы с автоматом,
   * обрабатывающим строковые команды и наследуется от общего класса состояний автомата данного вида -
   * z80::commandStateMachineState.
   */
  class commandStateMachineStateStaticBlock : public z80::commandStateMachineState {
    using StateMachine = stateMachine<std::string>;

  public:
    /**
     * @brief Конструкту состояния передаётся ссылка на автомат, в контексте которого это состояние работают.
     * @param stateMachine Ссылка на объект-автомат.
     * @param iAction Начальное входное воздействие на автомат, которое привело к переключению в данное состояние.
     */
    commandStateMachineStateStaticBlock(commandStateMachine& stateMachine, const std::string& iAction);


    commandStateMachineStateStaticBlock(const commandStateMachineStateStaticBlock& sms);

    /**
     * @brief Входное воздействие на автомат.
     * @param iAction В терминах данной работы входное воздействие - это строковая команда.
     * @details Этот метод переопределяет метод базового класса состояний и вызывается автоматом по приходу новой строки
     * (команды).
     */
    void inputAction(const std::string& iAction) override;


    /**
     * @brief Вызов данного метода является сигналом о том, что автомат заканчивает работу и объекту нужно завершить
     * свой алгоритм.
     * @details Объекты класса "Обработка статического блока команд" по вызову этой функции отсылают автомату накопленный
     * блок команд.
     */
    void finish() override;

    std::unique_ptr<z80::state<std::string>> clone(StateMachine& s) const override;

  private:
    /**
     * @brief Обработка нового входного воздействия на автомат.
     * @param iAction Входное воздействие - в терминах настоящего задания это строка.
     * @details Это - служебная функция, вызываемая внутри данного класса, которая реализует функционал функции inputAction.
     * Функционал вынесен в отдельную функцию, потому что в конструкторе класса должны быть выполнены такие же действия:
     * добавить новую команду в блок.
     */
    void addInputAction(const std::string& iAction);

    /**
     * @brief Переключить машину в состояние Idle. Это - служебная функция, вызываемая изнутри данного класса.
     */
    void switchStateMachineToIdle() const;

    /**
     * @brief Переключить машину в состояние "Обработка холостого хода". Это - служебная функция, вызываемая изнутри
     * данного класса.
     */
    void switchStateMachineToDynamicBlock() const;

    /**
     * @brief Счётчик команд, накопленных в блоке к настоящему моменту. Используется для сравнения с blockSize.
     */
    std::size_t commandsCount = 0;

    /**
     * @brief Размер блока (в штуках команд) по достижении которого он закрывается и автомат переходит в состояние Idle.
     */
    std::size_t blockSize = 3;
  };
}
