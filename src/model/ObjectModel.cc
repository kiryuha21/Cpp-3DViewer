#include "ObjectModel.h"

#include <gnuplot-iostream.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

#include "utils.h"

namespace s21 {

void ObjectModel::add_point(double x, double y, double z) {
  points_coordinates_.push_back(ObjectModel::Coordinates{x, y, z});
}

void ObjectModel::add_facet(std::vector<int> facet) {
  facets_.push_back(facet);
}

void ObjectModel::read_from_file(const std::string &filename) {
  std::fstream file(filename, std::ios::in);
  if (!file.is_open()) {
    throw std::logic_error("File opening error");
  }

  std::string str;

  while (std::getline(file, str)) {
    std::replace(str.begin(), str.end(), ',', '.');
    std::stringstream ss(str);
    char start = '0';
    ss >> start;
    if (start == 'v') {
      double x = 0, y = 0, z = 0;
      ss >> x >> y >> z;
      add_point(x, y, z);
    } else if (start == 'f') {
      int point_number = 0;
      std::vector<int> numbers;
      while (!ss.eof()) {
        ss >> point_number;
        numbers.push_back(point_number);
      }
      add_facet(numbers);
    }
  }

  file.close();
}

void ObjectModel::write_to_file(const std::string &filename) const {
  std::fstream file(filename, std::ios::out);
  if (!file.is_open()) {
    throw std::logic_error("File opening error");
  }

  for (const auto &point : points_coordinates_) {
    file << "v " << point.x_ << " " << point.y_ << " " << point.z_ << "\n";
  }

  for (auto &facet : facets_) {
    file << "f ";
    for (const auto &point : facet) {
      file << point << " ";
    }
    file << "\n";
  }

  file.close();
}

void ObjectModel::move_points(const std::string &x, const std::string &y,
                              const std::string &z) noexcept {
  for (auto &point : points_coordinates_) {
    point.x_ += to_double(x, 0);
    point.y_ += to_double(y, 0);
    point.z_ += to_double(z, 0);
  }
}

void ObjectModel::scale_points(const std::string &x, const std::string &y,
                               const std::string &z) {
  if (fabs(to_double(x, 1)) <= kEps || fabs(to_double(y, 1)) <= kEps ||
      fabs(to_double(z, 1)) <= kEps) {
    throw std::logic_error("Zero scaling");
  }

  for (auto &point : points_coordinates_) {
    point.x_ *= to_double(x, 1);
    point.y_ *= to_double(y, 1);
    point.z_ *= to_double(z, 1);
  }
}

void ObjectModel::rotate_points(const std::string &angle,
                                const std::string &type) {
  double dangle = to_double(angle, 0);
  for (auto &point : points_coordinates_) {
    if (type == "x") {
      point.rotate_on_x(dangle);
    } else if (type == "y") {
      point.rotate_on_y(dangle);
    } else if (type == "z") {
      point.rotate_on_z(dangle);
    } else {
      throw std::logic_error("Bad type");
    }
  }
}

void ObjectModel::Coordinates::rotate_on_x(double angle) {
  angle = angle * M_PI / 180;
  double z = z_, y = y_;
  y_ = y * cos(angle) + z * sin(angle);
  z_ = -y * sin(angle) + z * cos(angle);
}

void ObjectModel::Coordinates::rotate_on_y(double angle) {
  angle = angle * M_PI / 180;
  double z = z_, x = x_;
  x_ = x * cos(angle) + z * sin(angle);
  z_ = -x * sin(angle) + z * cos(angle);
}

void ObjectModel::Coordinates::rotate_on_z(double angle) {
  angle = angle * M_PI / 180;
  double x = x_, y = y_;
  x_ = x * cos(angle) + y * sin(angle);
  y_ = -x * sin(angle) + y * cos(angle);
}

void ObjectModel::call_gnuplot() const {
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

void ObjectModel::generate_data(const std::string &filename) const {
  std::fstream file(filename, std::ios::out);
  if (!file.is_open()) {
    throw std::logic_error("File opening error");
  }

  for (const auto &facet : facets_) {
    for (const auto &number : facet) {
      file << points_coordinates_[number].x_ << ' '
           << points_coordinates_[number].y_ << ' '
           << points_coordinates_[number].z_ << '\n';
    }
  }

  file.close();
}

}  // namespace s21
