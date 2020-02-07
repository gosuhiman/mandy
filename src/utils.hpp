#include <iomanip>
#include <sstream>

std::string floatToString(float number) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(0) << number;
  return stream.str();
}
