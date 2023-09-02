#ifndef SRC_DATA_OBJECT_MODEL_H
#define SRC_DATA_OBJECT_MODEL_H

#include <string>
#include <vector>

namespace s21 {

class ObjectModel {
 public:
  ObjectModel(int width, int height) : width_(width), height_(height) {}
  ~ObjectModel() = default;

  void get_facets_count() const noexcept;
  void get_points_count() const noexcept;

  void clear();

  void add_point(double x, double y, double z);
  void add_facet(const std::vector<int> &facet);

  void generate_data(const std::string &filename) const;
  void call_gnuplot() const;

  void move_points(const std::string &x, const std::string &y,
                   const std::string &z) noexcept;
  void scale_points(const std::string &x, const std::string &y,
                    const std::string &z);
  void rotate_points(const std::string &angle, const std::string &type);

  int get_facets_count() const noexcept;
  int get_vertexes_count() const noexcept;

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

  std::vector<Coordinates> points_;
  std::vector<std::vector<int>> facets_;

  static constexpr double kEps = 1e-7;
};

}  // namespace s21

#endif  // SRC_DATA_OBJECT_MODEL_H
