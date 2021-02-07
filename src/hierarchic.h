#pragma once

#include <memory>
#include <iterator>
#include <list>

namespace z80 {
  /**
   * @brief Шаблонный клас, наследование от которого наделяет класс функционалом отношений child/parent.
   * @tparam T Тип класса потомка.
   * @details Класс реализует идиому CRTP (Curiously Recurring Template Pattern): класс, который необходимо наделить
   * поддержкой отношения child/parent наследуется от данного шаблона в качестве шаблонного параметра передавая самого себя.
   * Подмешанный функционал выглядит так, будто он находится в наследнике.
   */
  template <typename T>
  class hierarchic {

    public:
//    class iterator: public std::bidirectional_iterator_tag {
//      public:
//      iterator(std::shared_ptr<T> t_): t(t_) {}
//      const T& operator*() = 0;
//      Titerator& operator++() = 0;
//      Titerator& operator--() = 0;
//      ~iterator() = default;
//    };

    /**
     * @brief Добавить потомка в объект.
     * @param child Указатель на потомка: объект того же типа Т, который наследуется от шаблона.
     */
    void addChild(std::unique_ptr<T> child) {};

    /**
     * @brief Удалить потомка из объекта.
     * @param child Потомок, который сладует удалить из данного объекта.
     */
    void removeChild(T& child) {};

    protected:
    /**
     * @brief Потомки данного узла.
     */
    std::list<std::unique_ptr<T>> children;
  };
}