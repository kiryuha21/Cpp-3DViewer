#ifndef INC_3D_VIEWER_TEMPLATE_VISUALIZATIONCONTROLLER_H
#define INC_3D_VIEWER_TEMPLATE_VISUALIZATIONCONTROLLER_H

#include "../model/ObjectModel.h"

namespace s21 {
class VisualizationController {
 public:
  VisualizationController(int width, int height);
  ~VisualizationController();

  void move_object(const std::string& x_delta, const std::string& y_delta,
                   const std::string& z_delta);
  void scale_object(const std::string& x_delta, const std::string& y_delta,
                    const std::string& z_delta);
  void rotate_object(const std::string& delta, const std::string& type);
  void load_object_file(const std::string& filename);
  void visualize_object();

 private:
  ObjectModel* model_ = nullptr;
};
}  // namespace s21

#endif  // INC_3D_VIEWER_TEMPLATE_VISUALIZATIONCONTROLLER_H
