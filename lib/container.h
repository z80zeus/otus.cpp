/**
 * @file Файл содержит учебный контейнер в соответствии с заданием.
 * @author Владимир Лазарев solock@mail.ru
 * @details Реализовать свой контейнер, который по аналогии с контейнерами stl параметризуется аллокатором.
 * Контейнер должен иметь две возможности - добавить новый элемент и обойти контейнер в одном направлении.
 * Опционально реализовать совместимость с контейнерами stl – итераторы, вспомогательные методы size, empty и т.д.
 * Цель реализации своего контейнера – попробовать использовать std::allocator, а также свой аллокатор.
*/

#pragma once

#include <memory>  // std::allocator_traits

namespace z80 {

  /**
   * @brief Контейнер, в соответствии с заданием.
   * @tparam T Тип хранимого значения.
   * @tparam Alloc Тип аллокатора.
   */
  template<typename T, typename Allocator = std::allocator<T>>
  class container {
    using alloc_traits = std::allocator_traits<Allocator>;

    public:
      /**
       * @brief Достаточно конструктора по-умолчанию.
       */
      container() = default;

      /**
       * @brief Деструктор очищает выделенную память.
       */
      ~container();

      /**
       * @brief Добавление элемента в конец контейнера.
       * @param value Элемент, копия которого будет помещена в контейнер.
       */
      void push_back(const T& value);

      /**
       * @brief Оператор доступа к данным по индексу.
       * @param index Индекс требуемого элемента.
       * @return Ссылка на требуемый элемент.
       */
      T& operator[](std::size_t index);

      /**
       * @brief Константный оператор доступа к данным по индексу.
       * @param index Индекс требуемого элемента.
       * @return Константная ссылка на требуемый элемент
       */
      const T& operator[](std::size_t index) const;

      /**
       * @brief Количество элементов, хранящихся в контейнере.
       * @return Количество элементов в контейнере.
       */
      std::size_t size() const noexcept;

      /**
       * @brief Аллоцированная ёмкость контейнера. Может быть больше size.
       * @return Для какого количества элементов контейнер зарезервировал память.
       */
      std::size_t capacity() const noexcept;

    private:
      /**
       * @brief Реалоцирует память для расширения контейнера.
       * @return Указатель на новый буффер в памяти.
       * @details Функция изменяет поле data объекта и возвращает указатель на него.
       */
      T* realloc();

      Allocator   allocator;
      T*          data       = nullptr;
      std::size_t size_      = 0;
      std::size_t capacity_  = 0;
      static const std::size_t multFactor = 2;
  };
}

template<typename T, typename Allocator>
z80::container<T, Allocator>::~container() {
    if (data == nullptr) return;

    for (std::size_t index = 0; index < size_; ++index)
        std::allocator_traits<Allocator>::destroy (allocator, data + index);

    std::allocator_traits<Allocator>::deallocate(allocator, data, capacity_);
}

template<typename T, typename Allocator>
void
z80::container<T, Allocator>::push_back(const T& value) {
    if (size_ >= capacity_) realloc();
    std::allocator_traits<Allocator>::construct(allocator, data + size_, value);
    ++size_;
}

template<typename T, typename Allocator>
T&
z80::container<T, Allocator>::operator[](std::size_t index) {
    return data[index];
}

template<typename T, typename Allocator>
const T&
z80::container<T, Allocator>::operator[](std::size_t index) const {
    return data[index];
}

template<typename T, typename Allocator>
std::size_t
z80::container<T, Allocator>::size() const noexcept {
    return size_;
}

template<typename T, typename Allocator>
std::size_t
z80::container<T, Allocator>::capacity() const noexcept {
    return capacity_;
}

template<typename T, typename Allocator>
T*
z80::container<T, Allocator>::realloc() {
/* g++ неправильно обрабатывает аттрибут [[unlikely]] для блока операторов в if'е.
 * В таком виде:
 * if (capacity_ == 0) [[unlikely]] {
 *   data = std::allocator_traits<Allocator>::allocate(allocator, capacity_ = 1);
 *   return;
 * }
 * - аттрибут игнорируется
 * Поэтому пришлось совместить выделение памяти и возврат из функции в одно выражение, а функция стала возвращать
 * укзаатель.
 * В данной, учебной реализации контейнера необходимости в этом нет, а в полноценном контейнере может это бы и пригодилось.
 */
    if (capacity_ == 0) [[unlikely]]
      return data = std::allocator_traits<Allocator>::allocate(allocator, capacity_ = 1);

    auto newData = std::allocator_traits<Allocator>::allocate(allocator, capacity_ * multFactor);
    for (std::size_t index = 0; index < size_; ++index)
        std::allocator_traits<Allocator>::construct(allocator, newData + index, std::move(data[index]));

    std::allocator_traits<Allocator>::deallocate(allocator, data, capacity_);
    data = newData;
    capacity_ *= multFactor;
    return data;
}
