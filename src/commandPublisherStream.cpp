#include <string> // getline

#include "commandPublisherStream.h"

using namespace std;
using namespace z80;

commandPublisherStream::commandPublisherStream(istream& inputStream): is(inputStream) {
}

void
commandPublisherStream::start() {
  string str;
  while (getline(is, str)) notify(str);
}