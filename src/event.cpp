#include "event.h"

using namespace z80;

bool
event::isXEvent() const noexcept {
  return code != event::codes::EXIT;
}

bool
z80::operator==(const event& e, event::eventCodeType c) {
  return e.code == c;
}
