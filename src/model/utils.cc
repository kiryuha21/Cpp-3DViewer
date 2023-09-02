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

void Coordinates::rotate_on_x(double angle) {
  angle = angle * M_PI / 180;
  double z = z_, y = y_;
  y_ = y * cos(angle) + z * sin(angle);
  z_ = -y * sin(angle) + z * cos(angle);
}

void Coordinates::rotate_on_y(double angle) {
  angle = angle * M_PI / 180;
  double z = z_, x = x_;
  x_ = x * cos(angle) + z * sin(angle);
  z_ = -x * sin(angle) + z * cos(angle);
}

void Coordinates::rotate_on_z(double angle) {
  angle = angle * M_PI / 180;
  double x = x_, y = y_;
  x_ = x * cos(angle) + y * sin(angle);
  y_ = -x * sin(angle) + y * cos(angle);
}

}  // namespace s21
