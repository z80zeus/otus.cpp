#include "commandBlockPrinter.h"

#include <iostream>

using namespace z80;
using namespace std;

void
commandBlockPrinter::update(const std::string& commandBlock) {
  cout << "bulk: " << commandBlock.substr(commandBlock.find_first_of(" ") + 1) << endl;
}
