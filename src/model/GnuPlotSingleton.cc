#include "GnuPlotSingleton.h"

#include <gnuplot-iostream.h>

#include <fstream>

namespace s21 {

GnuPlotSingleton &GnuPlotSingleton::get_instance(int width, int height) {
  static GnuPlotSingleton instance_(width, height);
  return instance_;
}

void GnuPlotSingleton::generate_data(const ObjectModel *object,
                                     const std::string &filename) const {
  std::fstream file(filename, std::ios::out);
  if (!file.is_open()) {
    throw std::logic_error("File opening error");
  }

  file << std::setprecision(kDefaultPrecision) << std::fixed;

  std::vector<Coordinates> points = object->get_points();
  for (const auto &facet : object->get_facets()) {
    for (const auto &number : facet) {
      file << points[number - 1].x_ << ' ' << points[number - 1].y_ << ' '
           << points[number - 1].z_ << '\n';
    }
    file << '\n';
  }

  file.close();
}

void GnuPlotSingleton::call_gnuplot() const {
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
     << "splot '" << kPointsFilename << "' "
     << "notitle with polygons fs transparent solid 0.8 fc \"gray75\"\n";
}

}  // namespace s21
