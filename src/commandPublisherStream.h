#pragma once

#include <istream>
#include "commandPublisher.h"

namespace z80 {
  class commandPublisherStream: public z80::commandPublisher {
    public:
    commandPublisherStream(std::istream& inputStream);
    void start();

    private:
    std::istream& is;
  };
}
