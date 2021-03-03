/**
 * @brief Самостоятельная работа otus.c++.6: Команды.
 * @author Владимир Лазарев solock@mail.ru
 * @details
 * Задание 6
 * Разработать программу для пакетной обработки команд.
 * Команды считываются построчно из стандартного ввода и обрабатываются блоками по N команд.
 * Одна команда - одна строка, конкретное значение роли не играет. Если данные закончились - блок завершается
 * принудительно.
 * Параметр N передается как единственный параметр командной строки в виде целого числа.
 * Размер блока можно изменить динамически, если перед началом блока и сразу после дать команды `{` и `}` соответственно.
 * Предыдущий пакет при этом принудительно завершается.
 * Такие блоки могут быть включены друг в друга при этом вложенные команды `{` и `}` игнорируются (но не сами блоки).
 * Если данные закончились внутри динамического блока, весь динамический блок игнорируется.
 * Вместе с выводом в консоль блоки должны сохранятся в отдельные файлы с именами bulk1517223860.log ,
 * где 1517223860 - это время получения первой команды из блока. По одному файлу на блок.
 * Требования к реализации:
 * Бинарный файл должен называться bulk
 * Проверка:
 * Задание считается выполненным успешно, если после установки пакета и запуска с тестовыми данными вывод соответствует
 * описанию. Данные подаются на стандартный вход построчно с паузой в 1 секунду для визуального контроля.
 * Будет отмечена низкая связанность обработки данных, накопления пачек команд, вывода в консоль и сохранения в файлы.
 * Рекомендуется применить паттерны: Наблюдатель, Стратегия, возможно - Состояние.
 * Ремоендуется тщательно спроектировать архитектуру, т.к. в дальнейшем эта же задача будет ставиться в заданиях на
 * многопоточное, асинронное и сетевое программирование - и было бы хорошо применять заложенную архитектуру с
 * минимальными изменениями.
 */

#include "commandBlockFiler.h"
#include "commandBlockPrinter.h"
#include "commandStateMachine.h"
#include "publisherCommandsFromStream.h"

#include <cctype>     // std::isdigit
#include <iostream>   // std::cout, std::cin
#include <stdexcept>  // std::invalid_argument, std::out_of_range
#include <string>     // std::stoul

using namespace std;
using namespace z80;

/**
 * @brief Преобразование строки в положительное число.
 * @param param Строка для преобразования
 * @return Число, соответствующее строке.
 */
size_t getStaticBlockSizeFromArgv(const string& param);

int
main(int argc, char* argv[]) {
  try {
    publisherCommandsFromStream commandSrc(cin);
    commandStateMachine commandMachine;
    commandBlockPrinter commandPrinter(cout);
    commandBlockFiler commandFiler;

    if (argc > 1)
      commandMachine.setStaticBlockSize(getStaticBlockSizeFromArgv(argv[1]));

    commandSrc.subscribe(commandMachine);
    commandMachine.subscribe(commandPrinter);
    commandMachine.subscribe(commandFiler);

    commandSrc.start();
  }
  catch (const exception& e) {
    cerr << e.what() << endl;
  }
  return 0;
}

size_t
getStaticBlockSizeFromArgv(const string& param) {
  if (!all_of(cbegin(param), cend(param), [](auto sym) { return isdigit(sym); }))
    throw invalid_argument("Not number");
  size_t rtn;
  try {
    rtn = std::stoul(param, nullptr, 10);
  }
  catch (const out_of_range&) {
    throw out_of_range("Number too large");
  }
  return rtn;
}
