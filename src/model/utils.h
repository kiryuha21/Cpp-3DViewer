#ifndef CPP3_SMARTCALC_V2_0_1_UTILS_H
#define CPP3_SMARTCALC_V2_0_1_UTILS_H

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace s21 {
constexpr auto kDefaultPrecision = 7;

double to_double(const std::string& str);
std::string to_precised_string(double val) noexcept;

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_UTILS_H
