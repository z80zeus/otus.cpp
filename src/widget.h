#pragma once

#include <memory>
#include <list>

#include "drawable.h"
#include "hierarchic.h"
#include "eventListener.h"

namespace z80 {
  /**
   * @brief Базовый класс всех виджетов проекта.
   * @details Является:
   * 1. Отрисовываемым (наследуется от z80::drawable)
   * 2. Иерархическим (наследуется от z80::hierarchiv)
   * 3. Получателем сообщений (наследуется от z80::eventListener)
   */
  class widget: public z80::drawable, z80::hierarchic<z80::widget>, z80::eventListener {
    public:

    /**
     * @brief Отрисовка виджета.
     * @details Если признак видимости виджета isVisible() = true - функция вызывает функции draw у всех виджетов-потомков.
     * В противном случае - не делает ничего. Т.о. видимость виджета влияет на отрисовку не только его самого,
     * но и всех его дочерних (вложенных) виджетов, даже если их собственный признак видимости позволяет отрисоваться.
     */
    void draw () override;

    /**
     * @brief Сделать виджет видимым.
     */
    void show() override;

    /**
    * @brief Сделать виджет невидимым.
    */
    void hide() override;

    /**
     * @brief Проверка признака видимости виджета.
     * @return true = виджет видим (отрисовывается при вызове draw),
     * false = виджет невидим (функция draw ничего не делает).
     */
    bool isVisible() override;

    /**
     * @brief Тривиальный деструктор.
     */
    ~widget() override = default;

    private:
    /**
     * @brief Признак видимости виджета.
     */
    bool visible = true;
  };
}