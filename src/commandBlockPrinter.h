#pragma once

#include "subscriber.h"

#include <string>

namespace z80 {
  class commandBlockPrinter: public z80::subscriber<std::string> {
    public:
    void update(const std::string& commandBlock) override;
  };
}
