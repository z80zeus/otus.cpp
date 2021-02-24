#pragma once

namespace z80 {
  template<typename T>
  class subscriber {
    public:
    virtual ~subscriber() = default;
    virtual void update(const T& data) = 0;
  };
}