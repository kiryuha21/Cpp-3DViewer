#ifndef INC_3D_VIEWER_TEMPLATE_VISUALIZATIONCONTROLLER_H
#define INC_3D_VIEWER_TEMPLATE_VISUALIZATIONCONTROLLER_H

#include "../model/FacadeModel.h"

namespace s21 {
class VisualizationController {
 public:
  VisualizationController();
  ~VisualizationController();

  void load_object_movement(const std::string& x_delta,
                            const std::string& y_delta,
                            const std::string& z_delta);
  void load_object_scaling(const std::string& x_delta,
                           const std::string& y_delta,
                           const std::string& z_delta);
  void load_object_rotation(const std::string& delta, const std::string& type);
  void execute_object_changes();

  void load_object_file(const std::string& filename);
  void render_image(int width, int height);

  int get_facets_count() const noexcept;
  int get_vertexes_count() const noexcept;

  std::string get_file_basename(const std::string& filename) const;

 private:
  FacadeModel* model_ = nullptr;
};
}  // namespace s21

#endif  // INC_3D_VIEWER_TEMPLATE_VISUALIZATIONCONTROLLER_H
