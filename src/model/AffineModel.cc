#include "AffineModel.h"

#include "utils.h"

namespace s21 {

void AffineModel::move_points(ObjectModel *object, const std::string &x,
                              const std::string &y,
                              const std::string &z) const noexcept {
  double x_delta = to_double(x, 0);
  double y_delta = to_double(y, 0);
  double z_delta = to_double(z, 0);

  if (std::fabs(x_delta) <= kEps && std::fabs(y_delta) <= kEps &&
      std::fabs(z_delta) <= kEps) {
    return;
  }

  std::vector<Coordinates> points = object->pull_points();

  for (auto &point : points) {
    point.x_ += x_delta;
    point.y_ += y_delta;
    point.z_ += z_delta;
  }

  object->push_points(std::move(points));
}

void AffineModel::scale_points(ObjectModel *object, const std::string &x,
                               const std::string &y,
                               const std::string &z) const {
  double x_delta = to_double(x, 1);
  double y_delta = to_double(y, 1);
  double z_delta = to_double(z, 1);
  if (std::fabs(x_delta) <= kEps || std::fabs(y_delta) <= kEps ||
      std::fabs(z_delta) <= kEps) {
    throw std::logic_error("Zero scaling");
  }

  if (std::fabs(x_delta - 1) <= kEps && std::fabs(y_delta - 1) <= kEps &&
      std::fabs(z_delta - 1) <= kEps) {
    return;
  }

  std::vector<Coordinates> points = object->pull_points();

  for (auto &point : points) {
    point.x_ *= x_delta;
    point.y_ *= y_delta;
    point.z_ *= z_delta;
  }

  object->push_points(std::move(points));
}

void AffineModel::rotate_points(ObjectModel *object, const std::string &angle,
                                const std::string &type) const {
  double dangle = to_double(angle, 0);
  if (std::fabs(dangle) <= kEps) {
    return;
  }

  std::vector<Coordinates> points = object->pull_points();

  for (auto &point : points) {
    if (type == "x") {
      point.rotate_on_x(dangle);
    } else if (type == "y") {
      point.rotate_on_y(dangle);
    } else if (type == "z") {
      point.rotate_on_z(dangle);
    } else {
      throw std::logic_error("Bad type");
    }
  }

  object->push_points(std::move(points));
}

};  // namespace s21
