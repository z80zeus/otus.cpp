#pragma once

#include "docEntity.h"
#include "docMeta.h"

namespace z80 {
/**
 * @brief Интерфейс документа. В терминах MVC - это Model.
 * @details Весь документ - тоже является сущностью документа (docEntity) и будет корнем дерева документа.
 */
  class document: public docEntity {
    public:
    /**
     * @brief Получить мета-инфморацию о документе
     * @return Объект, содержащий мета-информацию о документе.
     */
    virtual const z80::docMeta& meta();

    /**
     * @brief Тривиальный инструктор, уничтожающий интерфейс.
     */
    virtual ~document() = default;
  };
}