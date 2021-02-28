#include "publisherCommandsFromStream.h"

#include <string>   // getline
#include <iostream> // std::cout


using namespace std;
using namespace z80;

publisherCommandsFromStream::publisherCommandsFromStream(istream& inputStream): is(inputStream) {
}

void
publisherCommandsFromStream::start() {
  string str;
  while (getline(is, str))
    notify(str);
  unsubscribeAll();
}