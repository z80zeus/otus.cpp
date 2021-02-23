#pragma once

#include <string>
#include <memory>
#include <set>

namespace z80 {
  class commandSubscriber;

  class commandPublisher {
    public:
    virtual ~commandPublisher() = default;
    virtual void subscribe(z80::commandSubscriber* subscriber);
    virtual void unsubscribe(z80::commandSubscriber* subscriber);
    virtual void notify(const std::string& command);

    private:
    std::set<z80::commandSubscriber*> subscribers;
  };
}