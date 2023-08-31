#ifndef INC_3D_VIEWER_TEMPLATE_VISUALIZATIONMODEL_H
#define INC_3D_VIEWER_TEMPLATE_VISUALIZATIONMODEL_H

#include <gnuplot-iostream.h>

#include "utils.h"

namespace s21 {

constexpr auto kPointsFilename = "points.txt";
constexpr auto kImageFilename = "image.png";

class VisualizationModel {
 public:
  VisualizationModel(int width, int height);
  ~VisualizationModel() = default;

  void load_coord_delta(const std::string& x_delta, const std::string& y_delta,
                        const std::string& z_delta);
  void load_scale_delta(const std::string& x_delta, const std::string& y_delta,
                        const std::string& z_delta);
  void load_angle_delta(const std::string& delta, const std::string& type);
  void load_object_file(const std::string& filename);
  void visualize_object();

  struct Vector3 {
    double x = 0;
    double y = 0;
    double z = 0;
  };

 private:
  void call_gnuplot() const;

  int width_ = 0;
  int height_ = 0;

  Vector3 coord_delta_ = Vector3{};
  Vector3 scale_delta_ = Vector3{};
  Vector3 angle_delta_ = Vector3{};
};
}  // namespace s21

#endif  // INC_3D_VIEWER_TEMPLATE_VISUALIZATIONMODEL_H
