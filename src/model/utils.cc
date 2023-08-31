#include "utils.h"

namespace s21 {

double to_double(const std::string& str) {
  size_t ptr = 0;
  double res = 0;

  try {
    res = std::stod(str, &ptr);
  } catch (std::invalid_argument& e) {
    throw std::logic_error("Conversion error!");
  }
  if (ptr != str.size()) {
    throw std::logic_error("Conversion error!");
  }

  return res;
}

double to_double(const std::string& str, double def_val) {
  if (str.empty()) {
    return def_val;
  }

  return to_double(str);
}

std::string to_precised_string(double val) noexcept {
  std::stringstream ss;
  ss << std::setprecision(kDefaultPrecision) << std::fixed << val;
  return ss.str();
}

}  // namespace s21
