/**
 * @brief Файл содержит объявление класса, который выводит блок команд в поток.
 * @author Владимир Лазарев solock@mail.ru
 */
#pragma once

#include "subscriber.h"

#include <ostream>  // std::ostream
#include <string>   // std::string

namespace z80 {
  /**
   * @brief Объекты данного класса используются для вывода блоков команд в поток.
   * @details Блоки команд поступают через механизм publisher/subsrciber, для чего данный класс наследуется от
   * шаблонного класса z80::subscriber с шаблонным параметром std::string (команды и блоки команд представляют собой строки).
   * Для получения блоков команд класс переопределяет функцию update.
   */
  class commandBlockPrinter : public z80::subscriber<std::string> {
  public:
    /**
     * @brief Конструктор параметризируется ссылкой на объект потокового вывода, куда будет направлять свой вывод
     * создаваемый объект.
     * @param outputStream Ссылка на объект, реализующий функциональность стандартного потокового вывода.
     */
    commandBlockPrinter(std::ostream& outputStream);

    /**
     * @brief Функция выводит блок команд в поток, указанный в конструкторе.
     * @param commandBlock Блок команд, который следует вывести в файл.
     * @details В commandBlock, помимо самих команд, в самом начале строки находится служебная информация:
     * время открытия данного блока команд в формате unixtime (число секунд прошедших с 1 января 1970 года).
     * <unixtime> <commands>.
     * Данная функция игнорирует эту служебную информацию и выводит в поток только команды (<commands>).
     */
    void update(const std::string& commandBlock) override;

  private:
    std::ostream& os;
  };
}
