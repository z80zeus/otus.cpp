#pragma once

namespace z80 {
  class commandSubscriber {
    public:
    virtual ~commandSubscriber() = default;
    virtual void newCommand(const std::string& command) = 0;
  };
}