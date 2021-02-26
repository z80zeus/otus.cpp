#include "publisherStream.h"

#include <string>   // getline
#include <iostream> // std::cout


using namespace std;
using namespace z80;

publisherStream::publisherStream(istream& inputStream): is(inputStream) {
}

publisherStream::~publisherStream() {
  cout << "~publisherStream" << endl;
}

void
publisherStream::start() {
  string str;
  while (getline(is, str))
    notify(str);
}