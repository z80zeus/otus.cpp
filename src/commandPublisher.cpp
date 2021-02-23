#include "commandPublisher.h"
#include "commandSubscriber.h"

using namespace z80;

void
commandPublisher::subscribe(z80::commandSubscriber* subscriber) {
  subscribers.emplace(subscriber);
}

void
commandPublisher::unsubscribe(z80::commandSubscriber* subscriber) {
  subscribers.erase(subscriber);
}

void
commandPublisher::notify(const std::string& command) {
  for(auto& subscriber : subscribers)
    subscriber->newCommand(command);
}