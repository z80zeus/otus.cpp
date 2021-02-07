#pragma once

namespace z80 {
/**
 * @brief Интерфейс команд проекта.
 */
  class command {
    public:
    /**
     * @brief Выполнить команду.
     */
    virtual void execute() = 0;

    /**
     * @brief Деструктор интерфейса.
     */
    virtual ~command() = default;
  };
}
