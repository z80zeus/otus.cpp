/**
 * @brief Файл содержит объявление класса, который выводит блок команд в файл.
 * @author Владимир Лазарев solock@mail.ru
 */
#pragma once

#include "subscriber.h"

#include <string> // std::string

namespace z80 {
  /**
   * @brief Объекты данного класса используются для вывода блоков команд в файлы.
   * @details Блоки команд поступают через механизм publisher/subsrciber, для чего данный класс наследуется от
   * шаблонного класса z80::subscriber с шаблонным параметром std::string (команды и блоки команд представляют собой строки).
   * Для получения блоков команд класс переопределяет функцию update.
   */
  class commandBlockFiler : public z80::subscriber<std::string> {
  public:
    /**
     * @brief Функция выводит блок команд в файл.
     * @param commandBlock Блок команд, который следует вывести в файл.
     * @details Для каждого блока команд функция создаёт файл с именем bulk<unixtime>.log, где unixtime - время открытия
     * данного блока команд в формате unixtime (число секунд прошедших с 1 января 1970 года).
     * Это время функция рассчитывает получить в самом commandBlock, в самом начале строки до первого пробела:
     * <unixtime> <commands>.
     * В файл будет записана только часть строки <commands>.
     */
    void update(const std::string& commandBlock) override;
  };
}
