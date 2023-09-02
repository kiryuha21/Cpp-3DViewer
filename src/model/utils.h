#ifndef CPP3_SMARTCALC_V2_0_1_UTILS_H
#define CPP3_SMARTCALC_V2_0_1_UTILS_H

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace s21 {
constexpr auto kDefaultPrecision = 7;

double to_double(const std::string& str);
double to_double(const std::string& str, double def_val);
std::string to_precised_string(double val) noexcept;

struct Coordinates {
  Coordinates(double x, double y, double z) : x_(x), y_(y), z_(z){};

  void rotate_on_x(double angle);
  void rotate_on_y(double angle);
  void rotate_on_z(double angle);

  double x_, y_, z_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_UTILS_H
