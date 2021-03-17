/**
 * @brief Файл содержит объявление конечного автомата, специализированного для обработки строковых команд.
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
   * @brief Конечный автомат, обрабатывающий строковые "команды" (в терминах задания).
   * @details Класс является конечным автоматом, для чего наследуется от шаблонного класса z80::stateMachine с шаблонным
   * параметром std::string: входными данные для данного автомата являются строки.
   * Кроме того, автомат является участником отношения publisher/subscriber, причём сразу в двух ипостасях:
   * 1. получает входные воздействия он в качестве Подписчика, для чего он наследуется от шаблонного класса
   * z80::subscriber с шаблонным параметром std::string и переопределяет метод update.
   * 2. рассылает сфорированные блоки команд в качестве Издателя, для чего он наследуется от шаблонного класса
   * z80::publisher с шаблонным параметром std::string. От publisher'а он получает механизм рассылки уведомлений.
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
     * @param csm Конечный автомат - источник перемещения.
     */
    commandStateMachine(commandStateMachine&& csm) noexcept ;

    /**
     * @brief Через функцию update объект класса получает команды от publisher'а, хотя ничто не мешает вызвать этот
     * метод и постороннему коду.
     * @param command Новая команда (в терминах учебного задания).
     * @details Функция передаёт полученную команду для обработки функции z80::stateMachine::inputAction(command), в
     * контексте этого же (this) объекта.
     */
    void update(const std::string& command) override;

    /**
     * @brief Через эту функцию устанавливается значение свойства staticBlockSize: размер статического блока команд
     * (выраженного в командах).
     * @param blockSize Ожидаемое количество команд в статическом блоке команд. В штуках команд.
     */
    void setStaticBlockSize(std::size_t blockSize);

    /**
     * @brief Функция возвращает значение свойства staticBlockSize: размер статического блока команд (выраженного в командах).
     * @return Ожидаемое количество команд в статическом блоке команд. В штуках команд. По-умолчанию - 3.
     */
    std::size_t getStaticBlockSize() const;

  private:
    /**
     * @brief Количество команд в статическом блоке команд.
     */
    std::size_t staticBlockSize = 3;
  };
}
