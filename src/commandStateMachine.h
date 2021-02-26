#pragma once

#include "publisher.h"
#include "subscriber.h"
#include "stateMachine.h"

#include <cstddef> // std::size_t
#include <string>  // std::string
#include <memory>  // std::enable_shared_from_this

namespace z80 {
  /**
   * @brief Автомат, обрабатывающий строковые команды (в терминах задания).
   * @details Расширяет классы subscriber и stateMachine типизированные std::string.
   */
  class commandStateMachine:
//      public std::enable_shared_from_this<z80::commandStateMachine>,
      public z80::stateMachine<std::string>,
      public z80::subscriber<std::string>,
      public z80::publisher<std::string> {
    public:
    commandStateMachine();
    ~commandStateMachine() override;
    void update(const std::string& command) override; // from z80::subscriber<std::string>
    std::size_t getStaticBlockSize();
    void        setStaticBlockSize(std::size_t blockSize);

    private:
    std::size_t staticBlockSize = 3;
  };
}
