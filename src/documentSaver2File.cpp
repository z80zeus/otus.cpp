#include "documentSaver2File.h"

using namespace std;
using namespace z80;

documentSaver2File::documentSaver2File(const document& doc2save, string&& filename2save):
doc(doc2save), filename(forward(filename2save)){}

void
documentSaver2File::execute() {}
