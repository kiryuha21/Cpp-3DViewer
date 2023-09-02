#ifndef SRC_DATA_AFFINE_MODEL_H
#define SRC_DATA_AFFINE_MODEL_H

#include "ObjectModel.h"

namespace s21 {

class AffineModel {
 public:
  void move_points(ObjectModel *object, const std::string &x,
                   const std::string &y, const std::string &z) const noexcept;
  void scale_points(ObjectModel *object, const std::string &x,
                    const std::string &y, const std::string &z) const;
  void rotate_points(ObjectModel *object, const std::string &angle,
                     const std::string &type) const;

 private:
  static constexpr double kEps = 1e-7;
};

}  // namespace s21

#endif  // SRC_DATA_AFFINE_MODEL_H
