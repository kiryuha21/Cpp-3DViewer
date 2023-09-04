#ifndef SRC_DATA_GNUPLOT_SINGLETON_H
#define SRC_DATA_GNUPLOT_SINGLETON_H

#include "ObjectModel.h"

namespace s21 {

constexpr auto kPointsFilename = "points.txt";
constexpr auto kImageFilename = "image.png";

class GnuPlotSingleton {
 public:
  static GnuPlotSingleton& get_instance(int width, int height);

  void generate_data(const ObjectModel* object,
                     const std::string& filename) const;
  void call_gnuplot() const;

  GnuPlotSingleton(const GnuPlotSingleton&) = delete;
  GnuPlotSingleton& operator=(const GnuPlotSingleton&) = delete;

 private:
  GnuPlotSingleton(int width, int height) : width_(width), height_(height){};
  ~GnuPlotSingleton() = default;

  int width_ = 0, height_ = 0;
};

}  // namespace s21

#endif  // SRC_DATA_GNUPLOT_SINGLETON_H
