/**
 * @brief Самостоятельная работа otus.c++.2: Аллокатор
 * @author Владимир Лазарев solock@mail.ru
 * @details Прикладной код использует оригинальный аллокатор и контейнер, написанные в соответствии
 * с условием задания.
 * Функция main должна содержать следующие вызовы:
 * - создание экземпляра std::map<int, int>
 * - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
 * - создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
 * - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
 * - вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
 * - создание экземпляра своего контейнера для хранения значений типа int
 * - заполнение 10 элементами от 0 до 9
 * - создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
 * ограниченным 10 элементами
 * - заполнение 10 элементами от 0 до 9
 * - вывод на экран всех значений, хранящихся в контейнере
 */

#include <iostream>
#include <map>
#include <boost/math/special_functions/factorials.hpp>

#include "lib/allocator.h"
#include "lib/container.h"

using namespace std;

constexpr auto numbers = 10;

const auto factorial = &boost::math::factorial<float>;
using stdContainer_stdAllocator = map<int, int>;
using stdContainer_z80Allocator = map<int, int, std::less<>, z80::allocator<std::pair < int, int>, numbers, false>>;
using z80Container_stdAllocator = z80::container<int>;
using z80Container_z80Allocator = z80::container<long, z80::allocator<long>>; // long, потому что аллокатор требует раззмер элемента не меньше указателя

int main() {

    stdContainer_stdAllocator c1;
    for (auto i = 0; i < numbers; i++)
        c1[i] = static_cast<int>(factorial(i));

    stdContainer_z80Allocator c2;
    for (auto i = 0; i < numbers; i++)
        c2[i] = static_cast<int>(factorial(i));

    for (const auto &pair: c2)
        cout << pair.first << " " << pair.second << " " << endl;

    z80Container_stdAllocator c3;
    for (auto i = 0; i < numbers; ++i)
        c3.push_back(i);

    z80Container_z80Allocator c4;
    for (auto i = 0; i < numbers; ++i)
        c4.push_back(i);

    for (auto i = 0; i < numbers; ++i)
        cout << c4[i] << endl;

    return 0;
}
