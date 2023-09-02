#include "ObjectModel.h"

#include <gnuplot-iostream.h>


#include "utils.h"

namespace s21 {

int ObjectModel::get_facets_count() const noexcept { return facets_.size(); }

void ObjectModel::clear() {
  points_.clear();
  facets_.clear();

int ObjectModel::get_vertexes_count() const noexcept {
  return points_.size();
}

void ObjectModel::add_point(double x, double y, double z) {
  points_.emplace_back(x, y, z);
}

void ObjectModel::add_facet(const std::vector<int> &facet) {
  facets_.push_back(facet);
}

void ObjectModel::move_points(const std::string &x, const std::string &y,
                              const std::string &z) noexcept {
  double x_delta = to_double(x, 0);
  double y_delta = to_double(y, 0);
  double z_delta = to_double(z, 0);

  if (std::fabs(x_delta) <= kEps && std::fabs(y_delta) <= kEps &&
      std::fabs(z_delta) <= kEps) {
    return;
  }

  for (auto &point : points_) {
    point.x_ += x_delta;
    point.y_ += y_delta;
    point.z_ += z_delta;
  }
}

void ObjectModel::scale_points(const std::string &x, const std::string &y,
                               const std::string &z) {
  double x_delta = to_double(x, 1);
  double y_delta = to_double(y, 1);
  double z_delta = to_double(z, 1);
  if (std::fabs(x_delta) <= kEps || std::fabs(y_delta) <= kEps ||
      std::fabs(z_delta) <= kEps) {
    throw std::logic_error("Zero scaling");
  }

  if (std::fabs(x_delta - 1) <= kEps && std::fabs(y_delta - 1) <= kEps &&
      std::fabs(z_delta - 1) <= kEps) {
    return;
  }

  for (auto &point : points_) {
    point.x_ *= x_delta;
    point.y_ *= y_delta;
    point.z_ *= z_delta;
  }
}

void ObjectModel::rotate_points(const std::string &angle,
                                const std::string &type) {
  double dangle = to_double(angle, 0);
  if (std::fabs(dangle) <= kEps) {
    return;
  }

  for (auto &point : points_) {
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

  file << std::setprecision(kDefaultPrecision) << std::fixed;

  for (const auto &facet : facets_) {
    for (const auto &number : facet) {
      file << points_[number - 1].x_ << ' '
           << points_[number - 1].y_ << ' '
           << points_[number - 1].z_ << '\n';
    }
    file << '\n';
  }

  file.close();
}

}  // namespace s21
