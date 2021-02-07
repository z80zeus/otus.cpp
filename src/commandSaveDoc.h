#pragma once

#include "command.h"
#include "document.h"

namespace z80 {
  /**
   * @brief Команда "Сохранить документ".
   */
  class commandSaveDoc: public z80::command {
    public:
    /**
     * @brief Конструктору передаётся документ для сохранения.
     * @param doc2save Документ для сохранения.
     */
    commandSaveDoc(const z80::document& doc2save);

    /**
     * @brief Переопределённая функция выполнения команды.
     * @details Если в мета-данных документа нет сохраняющего объекта - функция создаёт его и записывает в мета-данные.
     * Вызовом метода execute сохраняющего объекта - документ сохраняется в соответствии со специализацией сохраняющего объекта.
     */
    void execute () override;

    /**
     * @brief Деструктор - тривиальный.
     */
    ~commandSaveDoc() override = default;

    private:
    /**
     * @brief Документ, с которым работает команда.
     */
    const z80::document& doc;
  };
}
