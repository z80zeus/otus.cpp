#pragma once

#include "widget.h"
#include "event.h"

namespace z80 {
  /**
   * @brief Базовый класс для окон.
   * @details Наследует виджет, но переопределяет в нём только обработку событий.
   * Если окно не может обработать событие - к оно определяет, кому из дочерних виджетов оно относится и вызывает метод
   * event у него. У того всё повторяется аналогично: он или обрабатывает его или передаёт дальше.
   */
  class window: public z80::widget {
    public:
    /**
     * @brief Получение событий для окна, их обработка и маршрутизация.
     * @param e Событие из системной очереди событий.
     */
    void event(z80::event e) override;
  };
}
