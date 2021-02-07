#pragma once

#include "document.h"
#include "command.h"

namespace z80 {
  /**
   * @brief Класс сохраняет документ в файл.
   * @details Создаётся при сохранении документа при выборе пользователем опции "Сохранить в файл".
   * После создания - записывается в блок meta-информации документа и используется при последующих сохранениях.
   */
  class documentSaver2File: public z80::command {
    public:
    /**
     * @brief
     * @param doc2save
     * @param filename2save
     */
    documentSaver2File(const z80::document& doc2save, std::string&& filename2save);

    /**
     * @brief Функция, запускающяа операрцию сохранения документа в файл.
     */
    void execute() override;

    /**
     * @brief Деструктор - тривиальный.
     */
    ~documentSaver2File() override = default;

    private:
    /**
     * @brief Документ, к которому прикреплён данный "сохранятель".
     */
    const z80::document& doc;

    /**
     * @brief Имя файла куда следует сохранять документ.
     */
    std::string filename;
  };
}