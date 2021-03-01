#pragma once

#include <istream>
#include "publisher.h"

namespace z80 {
  /**
   * @brief Publisher строк из строкового потока.
   * @details Расширяет класс publisher типизированный std::string.
   */
  class publisherCommandsFromStream : public z80::publisher<std::string> {
  public:
    explicit publisherCommandsFromStream(std::istream& inputStream);

    void start();

  private:
    std::istream& is;
  };
}
