/**
 * @file Реализация библиотеки работы с ip-адресами из самостоятельной работы otus.c++.1.2.
 * @author Владимир Лазарев solock@mail.ru
 */
#include <algorithm>
#include <stdexcept>
#include <limits>

#include "libIpAddr.h"

using namespace std;

/**
 * @brief Внутренняя функция библиотеки для преобразования строки в однобайтовое значение с контролем пределов значений байта.
 *
 * @param buffer Строковое представление байта.
 * @return Прочитанный из строки байт.
 * @throw При выходе значения за пределы байта - выбрасывает исключение std::invalid_argument.
 */
uint8_t
string2octet(const std::string_view& buffer) noexcept(false) {
  uint8_t octet = stol(buffer.data());

  if (octet < std::numeric_limits<uint8_t>::min() || octet > std::numeric_limits<uint8_t>::max())
    throw invalid_argument(string("Bad IP: ") + buffer.data());

  return octet;
}

ipAddr
string2ip(const std::string &buffer) {
  ipAddr ip;
  auto dotPos = buffer.find_first_of('.');
  decltype(dotPos) findStartPos = 0;
  auto byteCounter = 0;

  for (long octet = 0;
    byteCounter < bytesInAddr && findStartPos != string::npos;
    ++byteCounter,
    findStartPos = dotPos == string::npos? string::npos : dotPos + 1,
    dotPos = buffer.find_first_of('.', findStartPos))
  {
    octet = string2octet(buffer.substr(findStartPos, dotPos));
    ip.bytes[byteCounter] = octet;
    ip.addr = ip.addr * 256 + octet;            // Последовательное формирование 32х-битного значения из октетов.
  }

  if (byteCounter < bytesInAddr - 1)            // Вывалился из цикла раньше времени
    throw invalid_argument("Bad IP: " + buffer);

  if (dotPos != string::npos)                   // Лишняя точка в строке
    throw invalid_argument("Bad IP: " + buffer);

  return ip;
}

std::ostream&
operator<<(std::ostream &os, const ipAddr &ip) noexcept(false) {

  os << static_cast<uint16_t>(ip.bytes[0]);
  for (auto byte = 1; byte < bytesInAddr; ++byte)
    os << "." << static_cast<uint16_t>(ip.bytes[byte]);;

  return os;
}

bool
operator>(const ipAddr &left, const ipAddr &right) noexcept {
  return left.addr > right.addr;
}

istream &
operator>>(istream &is, vector<ipAddr> &ips) noexcept(false) {
  string buffer;
  while (getline(is, buffer, '\t')) {
    ips.push_back(string2ip(buffer));
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  };
  return is;
}

ostream &
operator<<(ostream &os, const vector<ipAddr> &ips) noexcept(false) {
  for (auto ip: ips)
    os << ip << endl;
  return os;
}
