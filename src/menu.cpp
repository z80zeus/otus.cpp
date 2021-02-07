#include "menu.h"

#include <utility> // std::forward

using namespace z80;
using namespace std;

menu::menu(string&& menuName, shared_ptr<command> com_): name(forward<string>(menuName)), com(move(com_)) {}
