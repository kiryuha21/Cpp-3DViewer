#ifndef SRC_DATA_OBJECT_MODEL_H
#define SRC_DATA_OBJECT_MODEL_H

#include <string>
#include <vector>

#include "utils.h"

namespace s21 {

class ObjectModel {
 public:
  int get_facets_count() const noexcept;
  int get_points_count() const noexcept;

  void add_facet(const std::vector<int>& facet);
  void add_point(double x, double y, double z);

  void clear();

  std::vector<Coordinates>&& pull_points();
  void push_points(std::vector<Coordinates>&& points);

  const std::vector<Coordinates>& get_points() const noexcept;
  const std::vector<std::vector<int>>& get_facets() const noexcept;

 private:
  std::vector<Coordinates> points_;
  std::vector<std::vector<int>> facets_;
};

}  // namespace s21

#endif  // SRC_DATA_OBJECT_MODEL_H
