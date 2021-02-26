#pragma once

#include <memory> // std::shared_ptr
#include <set>
#include <iostream>

#include "subscriber.h"

namespace z80 {

  /**
   * @brief Шаблон класса publisher. Обеспечивает функционал подписки-отписки-оповещения.
   * @tparam T Тип, с которым работает класс.
   */
  template<typename T>
  class publisher {
    using Subscriber = z80::subscriber<T>;

    public:

    virtual ~publisher() { std::cout << "~publisher" << std::endl; };

    virtual void subscribe(std::shared_ptr<Subscriber> subscriber) {
      subscribers.emplace(subscriber);
    }

    virtual void unsubscribe(std::shared_ptr<Subscriber> subscriber) {
      subscribers.erase(subscriber);
    }

    virtual void notify(const T& data) {
      for(auto& subscriber : subscribers)
        subscriber->update(data);
    }

    private:
    std::set<std::shared_ptr<Subscriber>> subscribers;
  };
}