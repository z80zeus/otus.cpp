#pragma once

#include <memory> // std::shared_ptr
#include <set>

#include "subscriber.h"

namespace z80 {

  template<typename T>
  class publisher {
    using Subscriber = z80::subscriber<T>;

    public:

    virtual ~publisher() = default;

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