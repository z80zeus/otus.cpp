#include <memory>

#include "xMainWindow.h"
#include "windowFactory.h"

using namespace std;
using namespace boost::program_options;
using namespace z80;

std::unique_ptr<mainWindow>
createWindow (const variables_map& param) {
  return make_unique<xMainWindow>(param);
}

