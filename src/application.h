#pragma once

#include <memory>
#include <string>

#include "event.h"
#include "eventListener.h"

namespace z80 {

/**
 * @brief Класс, инкапсулирующий приложение.
 */
  class application {
  public:
    /**
     * @brief Конструктор по-умолчанию.
     */
    application() = default;

    /**
     * @brief Конструктор принимает указатель на объект, которому следует отправлять системные события.
     */
    [[maybe_unused]] explicit application(std::unique_ptr<z80::eventListener> eventListener);

    /**
     * @brief Запуск приложения.
     * @return Код возврата.
     * @details Эта функция запускает цикл обработки сообщений.
     */
    int run();

    /**
     * @brief Копирование приложения запрещено.
     * @details Копирование объекта инкапсулирующего приложение видится бессмысленным, поэтому запрещается. Во избежание.
     */
    application(const application &) = delete;

    /**
     * @brief Копирование приложения запрещено.
     * @details Копирование объекта инкапсулирующего приложение внутри самого приложения видится бессмысленным,
     * поэтому запрещается. Во избежание.
     */
    application &operator=(const application &) = delete;

  private:
    /**
     * @brief Функция получает событие из системного цикла событий.
     * @return
     */
    static z80::event getEvent();

    /**
     * @brief Получатель событий, прикреплённый к приложению.
     * Для графического приложения это скорее всего будет корневой виджет приложения - его окно.
     */
    std::unique_ptr<z80::eventListener> eListener;
  };
}