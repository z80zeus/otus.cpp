#include "commandBlockPrinter.h"

#include <iostream>

using namespace z80;
using namespace std;

commandBlockPrinter::commandBlockPrinter(ostream& outputStream) : os(outputStream) {}

void
commandBlockPrinter::update(const std::string& commandBlock) {
  os << "bulk: " << commandBlock.substr(commandBlock.find_first_of(" ") + 1) << endl;
}
