/**
 * @brief Файл содержит объявление конечного автомата, обрабатывающего строковые команды.
 * @author Владимир Лазарев solock@mail.ru
 */
#pragma once

#include "publisher.h"
#include "subscriber.h"
#include "stateMachine.h"

#include <cstddef> // std::size_t
#include <string>  // std::string

namespace z80 {
  /**
   * @brief Автомат, обрабатывающий строковые команды (в терминах задания).
   * @details Класс является конечным автоматом, для чего наследуется от шаблонного класса z80::stateMachine с шаблонным
   * параметром std::string: входными данные для данного автомата являются строки.
   * Кроме того, автомат является участником отношения publisher/subscriber, причём сразу в двух ипостасях:
   * 1. получает входные воздействия он в качестве подписчика, для чего он наследуется от шаблонного класса
   * z80::subscriber с шаблонным параметром std::string и переопределяет методы update и unsubscribe.
   * он получаеРасширяет классы subscriber и stateMachine типизированные std::string.
   * 2. рассылает блоки команд класс в качестве издателя, для чего он наследуется от шаблонного класса z80::publisher с
   * шаблонным параметром std::string. От publisher'а он получает механизм рассылки уведомлений.
   */
  class commandStateMachine :
      public z80::stateMachine<std::string>,
      public z80::subscriber<std::string>,
      public z80::publisher<std::string> {
  public:
    /**
     * @brief Конструктор по-умолчанию устанавливает начальное состояние конечного автомата: Idle.
     */
    commandStateMachine();

    /**
     * @brief Перемещающий конструктор вызывает перемещающие конструкторы базовых классов и переписывает себе параметры
     * работы машины данного (commandStateMachine) класса из секции private.
     * @param csm
     */
    commandStateMachine(commandStateMachine&& csm) noexcept ;

    /**
     * @brief Оператор присваивания.
     * @param csm Автомат, состояние которого копируется в текущий.
     * @return Ссылка на текущий объект.
     */
    commandStateMachine& operator= (const commandStateMachine& csm);

    /**
     * @brief Через функцию update объект класса получает команды. Предполагается, что от publisher'а, но ничто
     * не мешает вызвать этот метод и постороннему коду.
     * @param command Новая команда (в терминах учебного задания).
     * @details Эта функция передаёт полученную команду в качестве входного воздействия в этот же автомат, который
     * унаследован данным классом от z80::stateMachine (z80::stateMachine::inputAction(command)).
     */
    void update(const std::string& command) override;

    /**
     * @brief Функция оповещает объект класса о том, что он, как подписчик, отписан от своего издателя.
     * @details Данный факт воспринимается автоматом, как сигнал завершения работы.
     */
    //void unsubscribed() override;

    /**
     * @brief Функция устанавливает значение свойства staticBlockSize: размер статического блока команд (выраженного в командах).
     * @param blockSize Ожидаемое количество команд в статическом блоке команд. В штуках команд.
     */
    void setStaticBlockSize(std::size_t blockSize);

    /**
     * @brief Функция возвращает значение свойства staticBlockSize: размер статического блока команд (выраженного в командах).
     * @return Ожидаемое количество команд в статическом блоке команд. В штуках команд. По-умолчанию - 3.
     */
    std::size_t getStaticBlockSize() const;

  private:
    std::size_t staticBlockSize = 3;
  };
}
