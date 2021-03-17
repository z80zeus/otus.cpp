#include "commandBlockFiler.h"

#include <fstream>  // std::ofstream

using namespace z80;
using namespace std;

void
commandBlockFiler::update(const string& commandBlock) {
  // Всё что находится до первого пробела - поле, в котором передаётся служебная информация, позволяющая
  // индентифицировать блок команд. На основе этого поля строится имя файла, в котором будет сохранён блок команд.
  auto endOfTime = commandBlock.find_first_of(' ');
  ofstream out("bulk" + commandBlock.substr(0, endOfTime) + ".log");
  out << commandBlock.substr(endOfTime + 1) << endl << flush;
}
