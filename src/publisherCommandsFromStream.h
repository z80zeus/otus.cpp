/**
 * @brief Файл содержит объявление класса "Publisher команд из строкового потока".
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "publisher.h"

#include <istream>

namespace z80 {
  /**
   * @brief Publisher строковых команд из строкового потока.
   * @details Класс является Издателем, для чего наследуется от шаблонного класса z80::publisher<T> с шаблонным
   * параметром std::string: в данном проекте команды представляют собой строки.
   */
  class publisherCommandsFromStream : public z80::publisher<std::string> {
  public:
    /**
     * @brief Конструктор параметризируется ссылкой на объект std::istream.
     * @param inputStream Ссылка на объект, являющийся типом std::istream.
     */
    explicit publisherCommandsFromStream(std::istream& inputStream);

    /**
     * @brief Запуск чтения потока.
     * @details Эта функция блокирует вызывающий код, выполняет циклическое чтение потока и рассылку полученных команд.
     * При закрытии потока - цикл завершается и выполняется отписка всех подписчиков.
     * Фактически, данная функция является eventloop'ом программы.
     */
    void start();

  private:
    /**
     * @brief Ссылка на входной поток команд с которым работает объект.
     */
    std::istream& is;
  };
}
