#include "ParserModel.h"

#include <gnuplot-iostream.h>

#include <fstream>
#include <sstream>

namespace s21 {

void ParserModel::read_from_file(ObjectModel *object,
                                 const std::string &filename) {
  object->clear();
  std::fstream file(filename, std::ios::in);
  if (!file.is_open()) {
    throw std::logic_error("File opening error");
  }

  std::string str;
  while (std::getline(file, str)) {
    std::stringstream ss(str);
    char start = '0';
    ss >> start;
    if (start == 'v') {
      double x = 0, y = 0, z = 0;
      ss >> x >> y >> z;
      object->add_point(x, y, z);
    } else if (start == 'f') {
      int point_number = 0;
      std::vector<int> numbers;
      while (ss >> point_number) {
        if (point_number < 1) {
          throw std::logic_error("Point numbers in facet must be >= 1");
        }
        numbers.push_back(point_number);
      }
      object->add_facet(numbers);
    }
  }

  file.close();
}

void ParserModel::call_gnuplot() const {
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

void ParserModel::generate_data(const ObjectModel *object,
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

std::string ParserModel::get_file_basename(const std::string &filename) const {
  return filename.substr(filename.rfind('/') + 1);
}

};  // namespace s21
