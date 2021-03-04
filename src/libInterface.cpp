#include "libInterface.h"

#include "commandStateMachine.h"

using namespace std;
using namespace z80;

namespace async {
  static vector<commandStateMachine>  commandMachines;
};

using namespace async;

handle_t
connect (std::size_t bulk) {

  return nullptr;
}

void
receive (handle_t handle, const char* data, std::size_t size) {

}

void
disconnect (handle_t handle) {

}
