#pragma once

namespace z80 {
  /**
  * @brief Интерфейс для всех сущностей, которые могут быть отрисованы.
  */
  class drawable {
  public:
    /**
     * @brief Отрисовать графический элемент.
     */
    [[maybe_unused]] virtual void draw() = 0;

    /**
     * @brief Сделать элемент видимым. При вызове draw() он появится на экране.
     */
    [[maybe_unused]] virtual void show() = 0;

    /**
    * @brief Сделать элемент невидимым. При вызове draw() он не будет отрисовываться.
    */
    [[maybe_unused]] virtual void hide() = 0;

    /**
     * @brief Видимость.
     * @return true - если элемент отрисовывается при вызове функции draw, false - в противном случае.
     */
    [[maybe_unused]] virtual bool isVisible() = 0;

    /**
     * @brief Виртуальный деструктор - тривиальный.
     */
    virtual ~drawable() = default;
  };
}