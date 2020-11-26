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
#include <functional>
#include <boost/math/special_functions/factorials.hpp>
#include "lib/allocator.h"

using namespace std;

constexpr auto numbers = 10;

using dataType = uint64_t;

int main(/*int argc, char const *argv[]*/) {

  map<dataType, dataType, std::less<>, z80::allocator<std::pair<dataType, dataType>>> map1;
  for (auto i = 0; i < numbers; i++)
    map1[i] = static_cast<dataType>(boost::math::factorial<float>(i));

  cout << "map1: ";
  for (const auto& pair: map1) cout << pair.first << ":" << pair.second << " ";
  cout << endl;

  auto map2 = map1;
  cout << "map2: ";
  for (const auto& pair: map2) cout << pair.first << ":" << pair.second << " ";
  cout << endl;


  vector<dataType, z80::allocator<dataType, 10>> vec1;
  for (auto i = 0; i < numbers; i++)
    vec1.push_back(static_cast<dataType>(boost::math::factorial<float>(i)));

  cout << "vec1: ";
  for (const auto& num: vec1) cout << num << " ";
  cout << endl;

  auto vec2 = vec1;
  vec2.push_back(42);
  cout << "vec2: ";
  for (const auto& num: vec2) cout << num << " ";
  cout << endl;

  return 0;
}

