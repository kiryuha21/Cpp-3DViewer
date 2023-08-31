#include "VisualizationModel.h"

namespace s21 {
VisualizationModel::VisualizationModel(int width, int height)
    : width_(width), height_(height) {}

void VisualizationModel::load_coord_delta(const std::string& x_delta,
                                          const std::string& y_delta,
                                          const std::string& z_delta) {
  coord_delta_.x = to_double(x_delta);
  coord_delta_.y = to_double(y_delta);
  coord_delta_.z = to_double(z_delta);
}

void VisualizationModel::load_scale_delta(const std::string& x_delta,
                                          const std::string& y_delta,
                                          const std::string& z_delta) {
  scale_delta_.x = to_double(x_delta);
  scale_delta_.y = to_double(y_delta);
  scale_delta_.z = to_double(z_delta);
}

void VisualizationModel::load_angle_delta(const std::string& delta,
                                          const std::string& type) {
  if (type == "x") {
    angle_delta_.x = to_double(delta);
  } else if (type == "y") {
    angle_delta_.y = to_double(delta);
  } else {
    angle_delta_.z = to_double(delta);
  }
}

void VisualizationModel::load_object_file(const std::string& filename) {
  if (filename.empty()) {
    throw std::logic_error("Missing object file!");
  }

  // TODO: implement remaining logic
}

void VisualizationModel::visualize_object() {}

void VisualizationModel::call_gnuplot() const {
  Gnuplot gp;
  gp << "set terminal pngcairo size " << width_ << "," << height_ << "\n"
     << "set output '" << kImageFilename << "'\n"
     << "set xyplane at 0\n"
     << "set view equal xyz\n"
     << "unset border\n"
     << "set xlabel \"X-Axis\"\n"
     << "set ylabel \"Y-Axis\"\n"
     << "set zlabel \"Z-Axis\"\n"
     << "set pm3d depth\n"
     << "set pm3d border lc \"black\" lw 1.5\n"
     << "splot '" << kImageFilename << "' "
     << "notitle with polygons fs transparent solid 0.8 fc \"gray75\"\n";
}
}  // namespace s21
