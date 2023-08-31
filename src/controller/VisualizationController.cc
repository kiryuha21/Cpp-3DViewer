#include "VisualizationController.h"

namespace s21 {
VisualizationController::VisualizationController(int width, int height) {
  model_ = new ObjectModel(width, height);
}

VisualizationController::~VisualizationController() { delete model_; }

void VisualizationController::load_coord_delta(const std::string& x_delta,
                                               const std::string& y_delta,
                                               const std::string& z_delta) {
  model_->move_points(x_delta, y_delta, z_delta);
}

void VisualizationController::load_scale_delta(const std::string& x_delta,
                                               const std::string& y_delta,
                                               const std::string& z_delta) {
  model_->scale_points(x_delta, y_delta, z_delta);
}

void VisualizationController::load_angle_delta(const std::string& delta,
                                               const std::string& type) {
  model_->rotate_points(delta, type);
}

void VisualizationController::load_object_file(const std::string& filename) {
  model_->read_from_file(filename);
}

void VisualizationController::visualize_object() {
  model_->generate_data(kPointsFilename);
  model_->call_gnuplot();
}

}  // namespace s21
