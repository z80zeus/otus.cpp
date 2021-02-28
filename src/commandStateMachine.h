#pragma once

#include "publisher.h"
#include "subscriber.h"
#include "stateMachine.h"

#include <cstddef> // std::size_t
#include <string>  // std::string

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
    commandStateMachine();
    void update(const std::string& command) override; // from z80::subscriber<std::string>
    void unsubscribed() override;
    std::size_t getStaticBlockSize();
    void        setStaticBlockSize(std::size_t blockSize);

    private:
    std::size_t staticBlockSize = 3;
  };
}
