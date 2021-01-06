/**
 * @file Файл содержит функции преобразования IP в строку в соответствии с заданием.
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
 * - найдите самый простой способ сделать для печати `std::string.
*/

#pragma once

#include <type_traits>
#include <string>

namespace z80 {
    template<typename T>
    std::enable_if_t<std::is_integral_v<T>, std::string>
    ip2string(const T& ip) {
        constexpr auto bytes = sizeof(T);
        std::string rtn;
        auto ip_ = ip;
        for (std::size_t byte = 0; byte < bytes; ++byte, ip_ >>= 8) {
            auto byteValue = ip_ & 0xFF;
            rtn =  ((bytes - byte) > 1 ? "." : "") + std::to_string(byteValue) + rtn;
        }
        return "integral: " + rtn;
    }

    template<typename T>
    std::enable_if_t<std::is_same_v<T, std::string>, std::string>
    ip2string(const T& ip) {
        return "string: " + ip;
    }

    template<typename T>
    struct has_const_iterator {
        using yes = char[1];
        using no  = char[2];
        template<typename C>
        static yes&
        test (typename C::const_iterator*);

        template<typename C>
        static no&
        test (...);

        static const bool value = sizeof(test<T>(nullptr)) == sizeof (yes);
    };

    template<typename T>
    struct has_no_c_str {
        using yes = char[1];
        using no  = char[2];

        template<typename U>
        static no&
        test (decltype(&U::c_str));


        template<typename U>
        static yes&
        test (...);

        static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
    };

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
    ip2string(const T& ip) {
        std::string rtn;
        for(const auto& byte: ip)
            rtn += std::to_string(byte) + ".";
        rtn.resize(rtn.size() - 1);
        return "container: " + rtn;
    }
}
