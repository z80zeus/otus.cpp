/**
 * @brief Файл содержит объявление шаблонного класса "Подписчик" (subscriber).
 * @author Владимир Лазарев solock@mail.ru
 */

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
    /**
     * @brief Деструктор полиморфного класса имеет реализацию по-умолчанию.
     */
    virtual ~subscriber() = default;

    /**
     * @brief Оповещение подписчика о значении.
     * @param data Значение, присланное издателем.
     */
    virtual void update(const T& data) = 0;

    /**
     * @brief Оповещение подписчика об отписке от издателя.
     */
    virtual void unsubscribed() {};
  };
}