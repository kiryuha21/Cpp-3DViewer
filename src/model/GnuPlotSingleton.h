#ifndef SRC_DATA_GNUPLOT_SINGLETON_H
#define SRC_DATA_GNUPLOT_SINGLETON_H

#include "ObjectModel.h"

namespace s21 {

constexpr auto kPointsFilename = "points.txt";
constexpr auto kImageFilename = "image.png";

class GnuPlotSingleton {
 public:
  static GnuPlotSingleton& get_instance();

  void generate_data(const ObjectModel* object,
                     const std::string& filename) const;
  void call_gnuplot(int width, int height) const;

  GnuPlotSingleton(const GnuPlotSingleton&) = delete;
  GnuPlotSingleton& operator=(const GnuPlotSingleton&) = delete;

 private:
  GnuPlotSingleton() = default;
  ~GnuPlotSingleton() = default;
};

}  // namespace s21

#endif  // SRC_DATA_GNUPLOT_SINGLETON_H
