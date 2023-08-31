#include "view/MainWindow.h"

int main(int argc, char** argv) {
  auto app = Gtk::Application::create(argc, argv);
  auto builder = Gtk::Builder::create_from_file("ui/main.ui");
  auto css_provider_ = Gtk::CssProvider::create();
  css_provider_->load_from_path("ui/styles.css");
  Gtk::StyleContext::add_provider_for_screen(
      Gdk::Screen::get_default(), css_provider_,
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  s21::MainWindow* mv = nullptr;
  builder->get_widget_derived("main_window", mv);

  std::setlocale(LC_NUMERIC, "C");
  auto res = app->run(*mv);
  delete mv;
  return res;
}
