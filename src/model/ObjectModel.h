#ifndef SRC_DATA_OBJECT_MODEL_H
#define SRC_DATA_OBJECT_MODEL_H

#include <string>
#include <vector>

namespace s21 {

class ObjectModel {
 public:
  void add_point(double x, double y, double z);
  void add_facet(std::vector<int> facet);

  void read_from_file(const std::string &filename);
  void write_to_file(const std::string &filename) const;

  void move_points(double x, double y, double z) noexcept;
  void scale_points(double x, double y, double z);
  void rotate_points(double x, double y, double z);

 private:
  class Coordinates {
   public:
    Coordinates(double x, double y, double z) : x_(x), y_(y), z_(z){};

    void rotate_on_x(double angle);
    void rotate_on_y(double angle);
    void rotate_on_z(double angle);

    double x_, y_, z_;
  };

  std::vector<Coordinates> points_coordinates_;
  std::vector<std::vector<int>> facets_;

  static constexpr double kEps = 1e-7;
};

}  // namespace s21

#endif  // SRC_DATA_OBJECT_MODEL_H
