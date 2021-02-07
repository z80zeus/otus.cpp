#pragma once

#include <string> // std::string
#include <memory> // std::shared_ptr

#include "widget.h"
#include "command.h"

namespace z80 {
  /**
   * @brief Сущность - меню.
   * @details Может являться как узловым элементом меню (с выпадающими подменю), так и листом. Т.е. этот класс
   * используется и для поддержки корневого меню и для вложенных пунктов и для конечного пункта меню.
   */
  class menu : public z80::widget {
    public:
    /**
     * @brief Конструктор по-умолчанию создаёт пункт меню без имени и без обработчика. Самое подходящее применение - корень меню.
     */
    menu() = default;

    /**
     * @brief Конструктор
     * @param menuName Имя меню
     * @param command Команда, выполняющаяся при щелчке на меню. shared_ptr, потому что эта же команда может быть
     * привязана к кнопке, к горячей клавише и т.д.
     */
    menu(std::string&& menuName, std::shared_ptr<z80::command> command);

    /**
     * @brief Деструктор - тривиальный. Все данные удалятся автоматически.
     */
    ~menu() override = default;

    private:
    /**
     * @brief Название пункта меню
     */
    std::string name;

    /**
     * Команда, которая выполняется по щелчку на данном пункте меню.
     */
    std::shared_ptr<z80::command> com;
  };
}