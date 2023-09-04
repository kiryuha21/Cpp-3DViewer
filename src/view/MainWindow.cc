#include "MainWindow.h"

namespace s21 {
MainWindow::MainWindow(BaseObjectType *obj,
                       Glib::RefPtr<Gtk::Builder> const &builder)
    : Gtk::Window(obj), builder_{builder} {
  builder_->get_widget("file_selector", file_selector_);
  builder_->get_widget("load_file_button", load_file_button_);

  builder_->get_widget("viewer_label", viewer_label_);

  builder_->get_widget("x_coord_delta_entry", x_coord_delta_entry_);
  builder_->get_widget("y_coord_delta_entry", y_coord_delta_entry_);
  builder_->get_widget("z_coord_delta_entry", z_coord_delta_entry_);

  builder_->get_widget("x_scale_delta_entry", x_scale_delta_entry_);
  builder_->get_widget("y_scale_delta_entry", y_scale_delta_entry_);
  builder_->get_widget("z_scale_delta_entry", z_scale_delta_entry_);

  builder_->get_widget("angle_delta_entry", angle_delta_entry_);
  builder_->get_widget("angle_combo_box", angle_combo_box_);

  builder_->get_widget("visualization_image", visualization_image_);
  builder_->get_widget("render_button", render_button_);

  render_button_->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::on_render_button_clicked));
  load_file_button_->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::on_load_file_button_clicked));

  controller_ = new VisualizationController;
}

MainWindow::~MainWindow() { delete controller_; }

void MainWindow::on_render_button_clicked() const noexcept {
  try {
    controller_->load_object_movement(x_coord_delta_entry_->get_text(),
                                      y_coord_delta_entry_->get_text(),
                                      z_coord_delta_entry_->get_text());
    controller_->load_object_scaling(x_scale_delta_entry_->get_text(),
                                     y_scale_delta_entry_->get_text(),
                                     z_scale_delta_entry_->get_text());
    controller_->load_object_rotation(angle_delta_entry_->get_text(),
                                      angle_combo_box_->get_active_text());
    controller_->execute_object_changes();
    controller_->render_image(visualization_image_->get_allocated_width(),
                              visualization_image_->get_allocated_height());
  } catch (std::logic_error &e) {
    viewer_label_->set_text(e.what());
    return;
  }

  display_image();
}

void MainWindow::on_load_file_button_clicked() noexcept {
  chosen_file_path_ = file_selector_->get_filename();

  try {
    controller_->load_object_file(chosen_file_path_);
    controller_->render_image(visualization_image_->get_allocated_width(),
                              visualization_image_->get_allocated_height());
  } catch (std::logic_error &e) {
    viewer_label_->set_text(e.what());
    return;
  }

  display_image();
}

void MainWindow::display_image() const {
  visualization_image_->set(kImageFilename);
  visualization_image_->queue_draw();

  std::stringstream ss;
  ss << "Rendered " << controller_->get_file_basename(chosen_file_path_)
     << " with " << controller_->get_facets_count() << " facets and "
     << controller_->get_vertexes_count() << " vertexes";
  viewer_label_->set_text(ss.str());
}

}  // namespace s21
