#pragma once

#include <string>

#include "subscriber.h"
#include "stateMachine.h"

namespace z80 {
  class commandStateMachine: public z80::subscriber<std::string>, z80::stateMachine<std::string> {
    public:
    void update(const std::string& command) override;
  };
}
