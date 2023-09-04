#ifndef SRC_DATA_AFFINE_MODEL_H
#define SRC_DATA_AFFINE_MODEL_H

#include "ObjectModel.h"
#include "RequestBuilder.h"

namespace s21 {

class AffineModel {
 public:
  AffineModel();
  ~AffineModel();

  void add_points_movement(const std::string &x, const std::string &y,
                           const std::string &z) const noexcept;
  void add_points_scaling(const std::string &x, const std::string &y,
                          const std::string &z) const;
  void add_points_rotation(const std::string &angle,
                           const std::string &type) const;
  void execute_changes(ObjectModel *object);

 private:
  static constexpr double kEps = 1e-7;
  RequestBuilder *request_builder_ = nullptr;
};

}  // namespace s21

#endif  // SRC_DATA_AFFINE_MODEL_H
