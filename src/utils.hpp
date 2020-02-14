#include <iomanip>
#include <sstream>

template <class T> std::string numberToString(T number, int precision = 0) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << number;
  return stream.str();
}
