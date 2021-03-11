/**
 * @brief Файл содержит объявление базового класса, для всех классов состояний конечного автомата обработки команд
 * (в терминах задания).
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "commandStateMachine.h"
#include "state.h"
#include "stateMachine.h"

#include <ctime>  // std::time_t
#include <memory> // unique_ptr
#include <string> // std::string, std::to_string

namespace z80 {
  /**
   * @brief Класс является подтипом класса z80::state - состояния абстрактного конечного автомата.
   * @details Класс предназначен для работы с автоматом обработки строковых команд, поэтому при наследовании от
   * базового шаблонного класса (состояния абстрактного автомата) z80::state он параметризирует его типом std::string,
   * т.к. в терминах задания команды - это строки.
   */
  class commandStateMachineState : public z80::state<std::string> {
    using StateMachine = z80::stateMachine<std::string>;

  public:
    /**
     * @brief Вызов данного метода является сигналом о том, что автомат заканчивает работу и объекту нужно завершить
     * свой алгоритм. В данном классе этот метод не делает ничего.
     */
    void finish() override;

    void setStateMachine(z80::stateMachine<std::string>* sMachine) override;

    protected:
    /**
     * @brief Создание объектов данного класса не предусмотрено, поэтому единственный конструктор находится в защищённой
     * секции и вызывается конструкторами классов-наследников.
     * @param sm Ссылка на автомат, в контексте которого работает данное конструируемое состояние.
     * Используется для доступа к функционалу автомата из состояния.
     */
    explicit commandStateMachineState(commandStateMachine* sm);

    /**
     * @brief
     * @param sms Ссылка на объект состояния, на основе которого производится копирование.
     */
    commandStateMachineState(const commandStateMachineState& sms);

    /**
     * @brief Функция отправки сохранённого блока команд. Это - сервисная функция, используемая в наследниках.
     * @details В процессе работы объекта-состояния вознимает необходимость отправки сформированного блока команд вовне
     * автомата. Эта функция вызывает метод notify у автомата, передавая ему накопленные команды, после чего - обнуляет их.
     * Строка команд предваряется служебным полем: временем создания данного блока в unixtime.
     */
    void sendSavedCommands();

    /**
     * @brief Блок команд, накопленных объектом.
     */
    std::string savedCommands;

    /**
     * @brief Указатель на объект автомата, приведённый к типу z80::commandStateMachine. Для объектов производных классов.
     */
    z80::commandStateMachine* cStateMachine = nullptr;

    /**
     * @brief Время (unixtime) начала (открытия) текущего блока команд. Это время инициализируется в конструкторе и
     * используется в работе функции sendSavedCommands().
     */
    std::time_t blockStartTime = std::time_t();
  };
}