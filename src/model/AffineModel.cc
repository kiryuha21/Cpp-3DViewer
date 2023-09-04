#include "AffineModel.h"

#include "utils.h"

namespace s21 {

AffineModel::AffineModel() { request_builder_ = new RequestBuilder; }

AffineModel::~AffineModel() { delete request_builder_; }

void AffineModel::add_points_movement(const std::string &x,
                                      const std::string &y,
                                      const std::string &z) const noexcept {
  double x_delta = to_double(x, 0);
  double y_delta = to_double(y, 0);
  double z_delta = to_double(z, 0);

  if (std::fabs(x_delta) <= kEps && std::fabs(y_delta) <= kEps &&
      std::fabs(z_delta) <= kEps) {
    return;
  }

  request_builder_->add_movement_component(x_delta, y_delta, z_delta);
}

void AffineModel::add_points_scaling(const std::string &x, const std::string &y,
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

  request_builder_->add_scale_component(x_delta, y_delta, z_delta);
}

void AffineModel::add_points_rotation(const std::string &angle,
                                      const std::string &type) const {
  double dangle = to_double(angle, 0);
  if (std::fabs(dangle) <= kEps) {
    return;
  }

  request_builder_->add_rotation_component(dangle, type);
}

void AffineModel::execute_changes(ObjectModel *object) {
  std::vector<Coordinates> points = object->pull_points();

  Request *request = request_builder_->build();
  for (auto &point : points) {
    if (request->movement != nullptr) {
      point.x_ += request->movement->x_;
      point.y_ += request->movement->y_;
      point.z_ += request->movement->z_;
    }
    if (request->scale != nullptr) {
      point.x_ *= request->scale->x_;
      point.y_ *= request->scale->y_;
      point.z_ *= request->scale->z_;
    }
    if (request->rotate_function != nullptr) {
      request->rotate_function(point, request->rotation_value);
    }
  }
  request_builder_->refresh();

  object->push_points(std::move(points));
}

};  // namespace s21
