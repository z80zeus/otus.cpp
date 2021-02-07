#include "application.h"

using namespace z80;

[[maybe_unused]]
application::application(std::unique_ptr<eventListener> el):
eListener(std::move(el)) {
}

int
application::run() {
  do {
    auto e = getEvent();
    if (e.isXEvent()) {
      if (eListener) eListener->event(e);
      continue;
    }
    if (e == event::codes::EXIT) return 0;
  } while (true);
}

event
application::getEvent() {
  return event{event::codes::MOUSE_CLICK};
}
