#ifndef SRC_DATA_OBJECT_MODEL_H
#define SRC_DATA_OBJECT_MODEL_H

#include <string>
#include <vector>

namespace s21 {

constexpr auto kPointsFilename = "points.txt";
constexpr auto kImageFilename = "image.png";

class ObjectModel {
 public:
  ObjectModel(int width, int height) : width_(width), height_(height) {}
  ~ObjectModel() = default;

  void add_point(double x, double y, double z);
  void add_facet(const std::vector<int> &facet);

  void read_from_file(const std::string &filename);
  void write_to_file(const std::string &filename) const;

  void generate_data(const std::string &filename) const;
  void call_gnuplot() const;

  void move_points(const std::string &x, const std::string &y,
                   const std::string &z) noexcept;
  void scale_points(const std::string &x, const std::string &y,
                    const std::string &z);
  void rotate_points(const std::string &angle, const std::string &type);

 private:
  class Coordinates {
   public:
    Coordinates(double x, double y, double z) : x_(x), y_(y), z_(z){};

    void rotate_on_x(double angle);
    void rotate_on_y(double angle);
    void rotate_on_z(double angle);

    double x_, y_, z_;
  };

  int width_ = 0;
  int height_ = 0;

  std::vector<Coordinates> points_coordinates_;
  std::vector<std::vector<int>> facets_;

  static constexpr double kEps = 1e-7;
};

}  // namespace s21

#endif  // SRC_DATA_OBJECT_MODEL_H
