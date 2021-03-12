/**
 * @brief Файл содержит объявление шаблонного класса "Издатель" (publisher).
 * @author Владимир Лазарев solock@mail.ru
 */

#pragma once

#include "subscriber.h"

#include <functional> // std::reference_wrapper
#include <vector>     // std::vector

namespace z80 {
  /**
   * @brief Шаблонный класс publisher. Обеспечивает функционал подписки-отписки-оповещения.
   * @tparam T Тип, с которым работает класс.
   * @details Работает с подписчиками типа z80::subscriber<T>, рассылая им уведомления путём вызова метода
   * z80::subscriber<T>::update().
   */
  template<typename T>
  class publisher {
    using Subscriber = z80::subscriber<T>;

  public:
    publisher() = default;
    publisher(z80::publisher<T>&& p): subscribers(std::move(p.subscribers)) {};

    /**
     * @brief Деструктор полиморфного класса. Реализацию по-умолчанию.
     */
    virtual ~publisher() = default;

    /**
     * @brief Функция подписки Подписчика (Subscriber) на рассылку значения типа T.
     * @param subscriber Подписчик типа z80::subscriber<T>.
     */
    virtual void subscribe(Subscriber& subscriber) {
      subscribers.push_back(subscriber);
    }

    /**
     * @brief Функция отписки всех подписчиков. Функция индивидуальной отписки в данном проекте не требуется.
     * @details У каждого подписчика вызывает метод unsubscribed(), оповещая его об окончании действия подписки.
     */
    virtual void unsubscribeAll() {
      for (const auto& subscriber : subscribers)
        subscriber.get().unsubscribed();
      subscribers.clear();
    }

    /**
     * @brief Функция оповещения подписчиков о значении data типа T.
     * @param data Значение, которое нужно разослать всем подписчикам.
     * @details У каждого подписчика вызывает метод update(data).
     */
    virtual void notify(const T& data) {
      for (const auto& subscriber : subscribers)
        subscriber.get().update(data);
    }

  private:
    /**
     * @brief Вектор ссылок на подписчиков данного издателя.
     */
    std::vector <std::reference_wrapper<Subscriber>> subscribers;
  };
}