#pragma once

#include <cstdint>  // std::uint32_t

namespace z80 {

  /**
   * @brief Структура - событие.
   */
  struct event {
    /**
     * @brief События кодируются 32-байтным числом
     */
    using eventCodeType = std::uint32_t;

    /**
     * @brief Параметр события - 32-байтное число.
     */
    using eventParam = std::uint32_t;

    /**
     * @brief Перечисление всех событий, поддерживаемых приложением.
     */
    enum codes : z80::event::eventCodeType {
      EXIT = 0,
      MOUSE_CLICK = 1,
      // и т.д.
    };

    /**
     * @brief Код события.
     * @details Значение по-умолчанию: EXIT. Т.е. генерация пустого события приведёт к завершению приложения.
     */
    z80::event::codes code = z80::event::codes::EXIT;

    /**
     * @brief Параметр события. Для каждого события имеет свой смысл.
     */
    eventParam       param = std::uint32_t {};

    /**
     * @brief Проверка - является ли данное событие событием графической подсистемы.
     * @return true
     */
    [[nodiscard]]
    bool
    isXEvent() const noexcept;
  };

  /**
   * @brief Оператор сравнения события с числовым значением кода события. Сравнивает код события e с переданным кодом c.
   * @param e Событие e, код которого сравнивается с кодом c.
   * @param c Код, сравнивается с кодом события e.
   * @return true, если e.code == c, false - в противном случае.
   */
  bool
  operator==(const z80::event& e, z80::event::eventCodeType c);
}
