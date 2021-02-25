#pragma once

#include <string>

#include "publisher.h"
#include "subscriber.h"
#include "stateMachine.h"

namespace z80 {
  /**
   * @brief Автомат, обрабатывающий строковые команды (в терминах задания).
   * @details Расширяет классы subscriber и stateMachine типизированные std::string.
   */
  class commandStateMachine:
      public z80::stateMachine<std::string>,
      public z80::subscriber<std::string>,
      public z80::publisher<std::string> {
    public:
    void update(const std::string& command) override; // z80::subscriber<std::string>
    std::size_t getStaticBlockSize();
    void        setStaticBlockSize(std::size_t blockSize);

    private:
    std::size_t staticBlockSize = 3;
  };
}
