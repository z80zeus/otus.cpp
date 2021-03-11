#include "libInterface.h"

#include "commandBlockFiler.h"
#include "commandBlockPrinter.h"
#include "commandStateMachine.h"
#include "publisherCommandsFromStream.h"

#include <vector>
#include <iostream>
#include <sstream>

using namespace async;
using namespace std;
using namespace z80;
/**
 * @brief Конечные автоматы, обрабатывающие команды.
 */
static vector<commandStateMachine>  commandMachines;

static commandBlockPrinter        printer (cout);

handle_t
async::connect (std::size_t bulk) {
  commandStateMachine csm;
  csm.setStaticBlockSize(bulk);
  csm.subscribe(printer);
  commandMachines.emplace_back(move(csm));
  return reinterpret_cast<handle_t>(commandMachines.size() - 1);
}

void
async::receive (handle_t handle, const char* data, size_t size) {
  istringstream is(string(data, size));
  publisherCommandsFromStream commandPublisher(is);
  commandPublisher.subscribe(commandMachines[reinterpret_cast<size_t>(handle)]);
  commandPublisher.start();
}

void
async::disconnect (handle_t handle) {
//  auto cMachineIndex = reinterpret_cast<size_t>(handle);
//  auto cMachine = commandMachines[cMachineIndex];
  commandMachines.erase(begin(commandMachines) + reinterpret_cast<size_t>(handle));
}
