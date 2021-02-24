#pragma once

#include <istream>
#include "publisher.h"

namespace z80 {
  class publisherStream: public z80::publisher<std::string> {
    public:
    explicit publisherStream(std::istream& inputStream);
    void start();

    private:
    std::istream& is;
  };
}
