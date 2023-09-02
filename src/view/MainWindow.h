#ifndef INC_3D_VIEWER_TEMPLATE_MAINWINDOW_H
#define INC_3D_VIEWER_TEMPLATE_MAINWINDOW_H

#include <gtkmm.h>

#include "../controller/VisualizationController.h"

namespace s21 {
class MainWindow : public Gtk::Window {
 public:
  MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder);
  ~MainWindow() override;

 private:
  void on_render_button_clicked() const noexcept;
  void on_load_file_button_clicked() noexcept;
  void display_image() const;

  Glib::RefPtr<Gtk::Builder> builder_;

  Gtk::Label* viewer_label_ = nullptr;

  Gtk::FileChooserButton* file_selector_ = nullptr;
  Gtk::Button* load_file_button_ = nullptr;

  Gtk::Entry* x_coord_delta_entry_ = nullptr;
  Gtk::Entry* y_coord_delta_entry_ = nullptr;
  Gtk::Entry* z_coord_delta_entry_ = nullptr;

  Gtk::Entry* x_scale_delta_entry_ = nullptr;
  Gtk::Entry* y_scale_delta_entry_ = nullptr;
  Gtk::Entry* z_scale_delta_entry_ = nullptr;

  Gtk::Entry* angle_delta_entry_ = nullptr;
  Gtk::ComboBoxText* angle_combo_box_ = nullptr;

  Gtk::Image* visualization_image_ = nullptr;
  Gtk::Button* render_button_ = nullptr;

  std::string chosen_file_path_;
  VisualizationController* controller_ = nullptr;
};
}  // namespace s21

#endif  // INC_3D_VIEWER_TEMPLATE_MAINWINDOW_H
