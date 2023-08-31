#include "ObjectModel.h"

#include <cmath>
#include <fstream>
#include <sstream>

namespace s21 {

void ObjectModel::add_point(double x, double y, double z) {
  points_coordinates_.push_back(ObjectModel::Coordinates{x, y, z});
}

void ObjectModel::add_facet(std::vector<int> facet) {
  facets_.push_back(facet);
}

void ObjectModel::read_from_file(const std::string &filename) {
  std::fstream file(filename, std::ios::in);

  std::string str;

  while (std::getline(file, str)) {
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
      ss >> point_number;
      while (point_number != 0) {
        numbers.push_back(point_number);
        ss >> point_number;
      }
      add_facet(numbers);
    }
  }

  file.close();
}

void ObjectModel::write_to_file(const std::string &filename) const {
  std::fstream file(filename, std::ios::out);

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

void ObjectModel::move_points(double x, double y, double z) noexcept {
  for (auto &point : points_coordinates_) {
    point.x_ += x;
    point.y_ += y;
    point.z_ += z;
  }
}

void ObjectModel::scale_points(double x, double y, double z) {
  if (fabs(x) <= kEps || fabs(y) <= kEps || fabs(z) <= kEps) {
    throw std::logic_error("yopta");
  }

  for (auto &point : points_coordinates_) {
    point.x_ *= x;
    point.y_ *= y;
    point.z_ *= z;
  }
}

void ObjectModel::rotate_points(double x, double y, double z) {
  for (auto &point : points_coordinates_) {
    point.rotate_on_x(x);
    point.rotate_on_y(y);
    point.rotate_on_z(z);
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

}  // namespace s21
