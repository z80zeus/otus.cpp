#pragma once

#include "event.h"

namespace z80 {
  /**
   * @brief Интерфейс для объектов, получающих системные события.
   */
  class eventListener {
    public:
    /**
     * @brief События поступают, путём вызова данной функции.
     * @param e Событие, требующее обработки.
     */
    virtual void event(z80::event e) = 0;

    /**
     * @brief Тривиальный деструктор.
     */
    virtual ~eventListener() = default;
  };
}