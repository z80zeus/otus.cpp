#pragma once

#include "hierarchic.h"

namespace z80 {
  /**
   * @brief Интерфейс всех сущностей документа. Является узлом иерархической структуры parent-child.
   */
  class docEntity: public z80::hierarchic<z80::docEntity> {
    public:
    /**
     * @brief Деструктор - тривиальный.
     */
    virtual ~docEntity() = default;
  };
}