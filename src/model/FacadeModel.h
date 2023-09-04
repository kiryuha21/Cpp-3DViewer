#ifndef SRC_DATA_FACADE_MODEL_H
#define SRC_DATA_FACADE_MODEL_H

#include "AffineModel.h"
#include "GnuPlotSingleton.h"
#include "ObjectModel.h"
#include "ParserModel.h"
#include "utils.h"

namespace s21 {

class FacadeModel {
 public:
  FacadeModel(int width_, int height_);
  ~FacadeModel();

  int get_facets_count() const noexcept;
  int get_points_count() const noexcept;

  void move_points(const std::string &x, const std::string &y,
                   const std::string &z) const noexcept;
  void scale_points(const std::string &x, const std::string &y,
                    const std::string &z) const;
  void rotate_points(const std::string &angle, const std::string &type) const;

  void read_from_file(const std::string &filename) const;
  std::string get_file_basename(const std::string &filename) const;

  void generate_data(const std::string &filename) const;
  void call_gnuplot() const;

 private:
  ObjectModel *object_model_ = nullptr;
  AffineModel *affine_model_ = nullptr;
  ParserModel *parser_model_ = nullptr;
};

}  // namespace s21

#endif  // SRC_DATA_FACADE_MODEL_H
