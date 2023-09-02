#ifndef SRC_DATA_PARSER_MODEL_H
#define SRC_DATA_PARSER_MODEL_H

#include "ObjectModel.h"

namespace s21 {

constexpr auto kPointsFilename = "points.txt";
constexpr auto kImageFilename = "image.png";

class ParserModel {
 public:
  ParserModel(int width, int height) : width_(width), height_(height) {}
  void read_from_file(ObjectModel* object, const std::string& filename);
  void generate_data(const ObjectModel* object,
                     const std::string& filename) const;
  void call_gnuplot() const;
  std::string get_file_basename(const std::string& filename) const;

 private:
  int width_ = 0, height_ = 0;
};

}  // namespace s21

#endif  // SRC_DATA_PARSER_MODEL_H
