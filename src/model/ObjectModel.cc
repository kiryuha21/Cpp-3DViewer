#include "ObjectModel.h"

#include "utils.h"

namespace s21 {

int ObjectModel::get_facets_count() const noexcept { return facets_.size(); }

void ObjectModel::clear() {
  points_.clear();
  facets_.clear();
}

int ObjectModel::get_points_count() const noexcept { return points_.size(); }

void ObjectModel::add_point(double x, double y, double z) {
  points_.emplace_back(x, y, z);
}

void ObjectModel::add_facet(const std::vector<int>& facet) {
  facets_.push_back(facet);
}

std::vector<Coordinates>&& ObjectModel::pull_points() {
  return std::move(points_);
}

void ObjectModel::push_points(std::vector<Coordinates>&& points) {
  points_ = std::move(points);
}

const std::vector<Coordinates>& ObjectModel::get_points() const noexcept {
  return points_;
}

const std::vector<std::vector<int>>& ObjectModel::get_facets() const noexcept {
  return facets_;
}

}  // namespace s21
