#pragma once

namespace z80 {
  /**
   * @brief Шаблон класса subscriber. Обеспечивает функционал подписчика на событие.
   * @tparam T Тип, с которым работает класс.
   * @details Функционал подписчика заключается в получении нового значения.
   */
  template<typename T>
  class subscriber {
  public:
    virtual ~subscriber() = default;

    virtual void update(const T& data) = 0;

    virtual void unsubscribed() {};
  };
}