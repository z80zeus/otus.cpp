#include "commandBlockPrinter.h"

#include <iostream> // std::endl, std::flush

using namespace z80;
using namespace std;

commandBlockPrinter::commandBlockPrinter(ostream& outputStream) : os(outputStream) {}

void
commandBlockPrinter::update(const string& commandBlock) {
  // Часть строки до первого пробела - идентификатор блока команд. В поток не выводится.
  os << "bulk: " << commandBlock.substr(commandBlock.find_first_of(' ') + 1) << endl << flush;
}
