#include "publisherCommandsFromStream.h"

#include <string>   // std::getline

using namespace z80;
using namespace std;

publisherCommandsFromStream::publisherCommandsFromStream(istream& inputStream) : is(inputStream) {
}

void
publisherCommandsFromStream::start() {
  string str;
  while (getline(is, str))
    notify(str);
  unsubscribeAll();
}
