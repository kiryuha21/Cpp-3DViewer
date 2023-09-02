#include "VisualizationController.h"

namespace s21 {
VisualizationController::VisualizationController(int width, int height) {
  model_ = new ObjectModel(width, height);
}

VisualizationController::~VisualizationController() { delete model_; }

void VisualizationController::move_object(const std::string& x_delta,
                                          const std::string& y_delta,
                                          const std::string& z_delta) {
  model_->move_points(x_delta, y_delta, z_delta);
}

void VisualizationController::scale_object(const std::string& x_delta,
                                           const std::string& y_delta,
                                           const std::string& z_delta) {
  model_->scale_points(x_delta, y_delta, z_delta);
}

void VisualizationController::rotate_object(const std::string& delta,
                                            const std::string& type) {
  model_->rotate_points(delta, type);
}

void VisualizationController::load_object_file(const std::string& filename) {
  model_->read_from_file(filename);
}

void VisualizationController::render_image() {
  model_->generate_data(kPointsFilename);
  model_->call_gnuplot();
}

int VisualizationController::get_facets_count() const noexcept {
  return model_->get_facets_count();
}

int VisualizationController::get_vertexes_count() const noexcept {
  return model_->get_vertexes_count();
}

}  // namespace s21
