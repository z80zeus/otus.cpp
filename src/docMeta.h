#pragma once

#include <memory>
#include "command.h"

namespace z80 {
  /**
   * @brief Мета-информация о документе.
   */
  struct docMeta {

    /**
     * @brief Объект, сохраняющий документ.
     */
    std::unique_ptr<z80::command> docSaver;
  };
}