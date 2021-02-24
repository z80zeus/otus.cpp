#include <string> // getline

#include "publisherStream.h"

using namespace std;
using namespace z80;

publisherStream::publisherStream(istream& inputStream): is(inputStream) {
}

void
publisherStream::start() {
  string str;
  while (getline(is, str))
    notify(str);
}