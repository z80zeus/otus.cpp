#pragma once

#include <istream>
#include "publisher.h"

namespace z80 {
  /**
   * @brief Publisher строк из строкового потока.
   * @details Расширяет класс publisher типизированный std::string.
   */
  class publisherStream: public z80::publisher<std::string> {
    public:
    explicit publisherStream(std::istream& inputStream);
    ~publisherStream() override;
    void start();

    private:
    std::istream& is;
  };
}
