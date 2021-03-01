#pragma once

#include "subscriber.h"

#include <iostream>

#include <functional> // std::reference_wrapper
#include <memory>     // std::weak_ptr
#include <vector>

namespace z80 {

  /**
   * @brief Шаблон класса publisher. Обеспечивает функционал подписки-отписки-оповещения.
   * @tparam T Тип, с которым работает класс.
   */
  template<typename T>
  class publisher {
    using Subscriber = z80::subscriber<T>;

  public:

    virtual ~publisher() = default;

    //virtual void subscribe(std::weak_ptr<Subscriber> subscriber) {
    virtual void subscribe(Subscriber& subscriber) {
      subscribers.push_back(subscriber);
    }

    virtual void unsubscribeAll() {
      for (const auto& subscriber : subscribers)
        subscriber.get().unsubscribed();
      subscribers.clear();
    }

    virtual void notify(const T& data) {
      for (const auto& subscriber : subscribers)
        subscriber.get().update(data);
    }

  private:
    //std::set<std::shared_ptr<Subscriber>> subscribers;
    std::vector <std::reference_wrapper<Subscriber>> subscribers;
  };
}