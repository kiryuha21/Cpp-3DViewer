#include "RequestBuilder.h"

namespace s21 {
Request::~Request() {
  delete movement;
  delete scale;
}

RequestBuilder::RequestBuilder() { request_ = new Request; }

RequestBuilder::~RequestBuilder() { delete request_; }

void RequestBuilder::refresh() {
  delete request_;
  request_ = new Request;
}

RequestBuilder &RequestBuilder::add_movement_component(double x, double y,
                                                       double z) {
  request_->movement = new Coordinates(x, y, z);
  return *this;
}

RequestBuilder &RequestBuilder::add_scale_component(double x, double y,
                                                    double z) {
  request_->scale = new Coordinates(x, y, z);
  return *this;
}

RequestBuilder &RequestBuilder::add_rotation_component(
    double val, const std::string &type) {
  if (type == "x") {
    request_->rotate_function = &Coordinates::rotate_on_x;
  } else if (type == "y") {
    request_->rotate_function = &Coordinates::rotate_on_y;
  } else if (type == "z") {
    request_->rotate_function = &Coordinates::rotate_on_z;
  }
  request_->rotation_value = val;

  return *this;
}

Request *RequestBuilder::build() { return request_; }
}  // namespace s21
