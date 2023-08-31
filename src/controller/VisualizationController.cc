#include "VisualizationController.h"

namespace s21 {
VisualizationController::VisualizationController(int width, int height) {
  model_ = new VisualizationModel(width, height);
}

VisualizationController::~VisualizationController() { delete model_; }

void VisualizationController::load_coord_delta(const std::string& x_delta,
                                               const std::string& y_delta,
                                               const std::string& z_delta) {
  model_->load_coord_delta(x_delta, y_delta, z_delta);
}

void VisualizationController::load_scale_delta(const std::string& x_delta,
                                               const std::string& y_delta,
                                               const std::string& z_delta) {
  model_->load_scale_delta(x_delta, y_delta, z_delta);
}

void VisualizationController::load_angle_delta(const std::string& delta,
                                               const std::string& type) {
  model_->load_angle_delta(delta, type);
}

void VisualizationController::load_object_file(const std::string& filename) {
  model_->load_object_file(filename);
}

void VisualizationController::visualize_object() { model_->visualize_object(); }

}  // namespace s21
