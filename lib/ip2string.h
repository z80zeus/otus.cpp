/**
 * @mainpage print_ip
 * Проект print_ip является демонстрацией механизма SFINAE в метапрограммировании на c++.\n
 * Основной частью проекта является header-only библиотека ip2string, преобразующая в строку разные представления
 * IP-адреса: целочисленное, строковое или контейнер.
 */
/**
 * @file ip2string.h
 * @brief Файл содержит функции преобразования IP в строку в соответствии с заданием.
 * @author Владимир Лазарев solock@mail.ru
 * @details
 * Реализовать функцию печати условного ip-адреса.
 * Функцию нужно реализовать для различных входных параметров путём использования механизма SFINAE.
 * Всего нужно выполнить 3 обязательных и один опциональный вариант функции.
 * 1. Адрес может быть представлен в виде произвольного целочисленного типа.
 *    Представление не зависит от знака типа. Выводить побайтово, начиная со старшего байта, с символом `.`
 *    (символ точки) в качестве разделителя.
 * 2. Адрес может быть представлен в виде строки. Выводится как есть.
 * 3. Адрес может быть представлен в виде контейнеров `std::list`, `std::vector`. Выводится содержимое контейнера
 *    поэлементно и разделяется `.` (одним символом точка).
 * 4. Опционально адрес может быть представлен в виде `std::tuple` при условии, что все типы одинаковы.
 *    Выводится содержимое поэлементно и разделяется `.` (одним символом точка).
 *
 * Дополнительные требования:
 * - функция печати должна быть одной шаблонной функцией, разные варианты входов должны быть реализованы через механизм SFINAE,
 * - специализация для целочисленного представления должна быть единственная,
 * - специализация для контейнеров должна быть единственная,
 * - не должно быть реализации типа "если не совпало с иными - значит это контейнер",
 * - опциональная реализация для `std::tuple` должна приводить к ошибке в случае отличающихся типов,
 * - найдите самый простой способ сделать для печати `std::string`.
*/

#pragma once

#include <type_traits>
#include <string>

namespace z80 {
  /**
   * @brief Преобразование представления IP-адреса в виде целого числа - в строку.
   * @tparam T Целочисленный тип.
   * @param ip Значение типа T, которое следует преобразовать в строку.
   * @return Для целочисленного T функция возвращает объект типа std::string.
   * Для T других типов данный вариант функции не скомпилируется.
   */
  template<typename T>
  std::enable_if_t<std::is_integral_v<T>, std::string>
  ip2string(T ip) {
    constexpr auto bytes = sizeof(T);
    std::string rtn;
    auto ip_ = ip;
    for (std::size_t byte = 0; byte < bytes; ++byte, ip_ >>= 8) {
      auto byteValue = ip_ & 0xFF;
      rtn = ((bytes - byte) > 1 ? "." : "") + std::to_string(byteValue) + rtn;
    }
    return rtn;
  }

  /**
   * @brief Вариант "преобразования" IP-адреса в строку из... строки.
   * На самом деле никакого преобразованяи не производится. Функция возвращает строку, переданную параметром.
   * @tparam T std::string
   * @param ip Константная ссылка на строку. Функция не анализирует содержимое переданной строки и возвращает её как есть.
   * @return Для T = std::string функция возвращает объект типа std::string.
   * Для T других типов данный вариант функции не скомпилируется.
   */
  template<typename T>
  std::enable_if_t<std::is_same_v<T, std::string>, std::string>
  ip2string(const T &ip) {
    return ip;
  }

  /**
   * @brief Метафункция проверяет наличие в типе T подтипа - константный итератор.
   * @tparam T Тип, который следует проверить.
   * @return has_const_iterator::value = true, если тип T содержит требуемый подтип. false - в противном случае.
   */
  template<typename T>
  struct has_const_iterator {
    using yes = char[1];
    using no = char[2];

    template<typename C>
    static yes &
    test(typename C::const_iterator *);

    template<typename C>
    static no &
    test(...);

    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
  };

  /**
   * @brief Метафункция проверяет отсутствие в типе T функции c_str.
   * @tparam T Тип, который следует проверить.
   * @return has_no_c_str = true, если тип Т НЕ содержит функцию c_str. false - в противном случае.
   */
  template<typename T>
  struct has_no_c_str {
    using yes = char[1];
    using no = char[2];

    template<typename U>
    static no &
    test(decltype(&U::c_str));


    template<typename U>
    static yes &
    test(...);

    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
  };

  /**
   * @brief Преобразование представления IP-адреса из содержимового контейнера - в строку.
   * @tparam T Тип - контейнер.
   * @param ip константная ссылка на объект типа T.
   * @return Для T типа контейнер - возвращает строку, составленную из содержимого контейнера, разделённого точками.
   * Для типа T не предоставляющего необходимый интерфейс контейнера - данный вариант функции не скомпилируется.
   * @details Для работы функции требуется наличие константного итератора - это проверяется метафункцией
   * z80::has_const_iterator<T>.\n
   * Однако под данный критерий попадает и std::string, который имеет интерфейс практически идентичный контейнерам, но
   * std::string должен обрабатываться другим вариантом этой функции.\n
   * Для исключения применения данного варианта функции, std::string отбрасывается метафункцией z80::has_no_c_str<T>,
   * которая не должна обнаружить наличие метода c_str у типа T: в std::string этот метод есть, у контейнеров - нет.\n
   * Результаты работы этих двух метафункций: z80::has_const_iterator<T> и z80::has_no_c_str<T> - собираются по "И"
   * метафункцией std::conjunction.
   */
  template<typename T>
  std::enable_if_t
  <
    std::conjunction_v
    <
      z80::has_const_iterator<T>,
      z80::has_no_c_str<T>
    >,
    std::string
  >
  ip2string(const T &ip) {

    std::string rtn;

    for (const auto &byte: ip)
      rtn += std::to_string(byte) + ".";

    if (rtn.size() > 0)
      rtn.resize(rtn.size() - 1);

    return rtn;
  }
}
