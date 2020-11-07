/**
 * @file Реализация библиотеки работы с ip-адресами из самостоятельной работы otus.c++.1.2.
 * @author Владимир Лазарев solock@mail.ru
 */
#include <algorithm>
#include <stdexcept>
#include <limits>

#include "libIpAddr.h"

using namespace std;

ipAddr::ipAddr(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
  bytes[0] = byte1;
  bytes[1] = byte2;
  bytes[2] = byte3;
  bytes[3] = byte4;
  addr = 0;
  for(auto byte : bytes) addr = addr * 256 + byte;
}

/**
 * @brief Внутренняя функция библиотеки для преобразования строки в однобайтовое значение с контролем пределов значений байта.
 *
 * @param buffer Строковое представление байта.
 * @return Прочитанный из строки байт.
 * @throw При выходе значения за пределы байта - выбрасывает исключение std::invalid_argument.
 */
uint8_t
string2octet(const string& buffer) noexcept(false) {
  long octet = stol(buffer);

  if (octet < std::numeric_limits<uint8_t>::min() || octet > std::numeric_limits<uint8_t>::max())
    throw invalid_argument(string("Bad IP: ") + buffer);

  return octet;
}

ipAddr
string2ip(const std::string &buffer) {
  ipAddr ip;
  auto dotPos = buffer.find_first_of('.');
  decltype(dotPos) findStartPos = 0;
  auto byteCounter = 0;

  for (;
    byteCounter < bytesInAddr && findStartPos != string::npos;
    ++byteCounter,
    findStartPos = dotPos == string::npos? string::npos : dotPos + 1,
    dotPos = buffer.find_first_of('.', findStartPos))
  {
    ip.bytes[byteCounter] = string2octet(buffer.substr(findStartPos, dotPos));
    ip.addr = ip.addr * 256 + ip.bytes[byteCounter]; // Последовательное формирование 32х-битного значения из октетов.
  }

  if (byteCounter < bytesInAddr)            // Вывалился из цикла раньше времени
    throw invalid_argument("Bad IP: " + buffer);

  if (findStartPos != string::npos)                   // Лишняя точка в строке
    throw invalid_argument("Bad IP: " + buffer);

  return ip;
}

std::ostream&
operator<<(std::ostream &os, const ipAddr &ip) noexcept(false) {

  os << static_cast<uint16_t>(ip.bytes[0]);
  for (auto byte = 1; byte < bytesInAddr; ++byte)
    os << "." << static_cast<uint16_t>(ip.bytes[byte]);

  return os;
}

bool
operator>(const ipAddr &left, const ipAddr &right) noexcept {
  return left.addr > right.addr;
}

bool
operator==(const ipAddr &left, const ipAddr &right) noexcept {
  return left.addr == right.addr;
}

istream&
operator>>(istream &is, vector<ipAddr> &ips) noexcept(false) {
  string buffer;
  while (getline(is, buffer, '\t')){
    ips.push_back(string2ip(buffer));
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return is;
}

ostream&
operator<<(ostream &os, const vector<ipAddr> &ips) noexcept(false) {
  for (auto ip: ips)
    os << ip << endl;
  return os;
}
