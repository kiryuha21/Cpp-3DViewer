#ifndef INC_3D_VIEWER_TEMPLATE_REQUESTBUILDER_H
#define INC_3D_VIEWER_TEMPLATE_REQUESTBUILDER_H

#include <functional>

#include "utils.h"

namespace s21 {
struct Request {
  Request() = default;
  ~Request();

  Coordinates* movement = nullptr;
  Coordinates* scale = nullptr;

  double rotation_value = 0;
  std::function<void(Coordinates*, double)> rotate_function = nullptr;
};

class RequestBuilder {
 public:
  RequestBuilder();
  ~RequestBuilder();

  RequestBuilder& add_movement_component(double x, double y, double z);
  RequestBuilder& add_scale_component(double x, double y, double z);
  RequestBuilder& add_rotation_component(double val, const std::string& type);
  Request* build();

 private:
  Request* request_ = nullptr;
};
}  // namespace s21

#endif  // INC_3D_VIEWER_TEMPLATE_REQUESTBUILDER_H
