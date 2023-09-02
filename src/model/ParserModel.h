#ifndef SRC_DATA_PARSER_MODEL_H
#define SRC_DATA_PARSER_MODEL_H

#include "ObjectModel.h"

namespace s21 {

constexpr auto kPointsFilename = "points.txt";
constexpr auto kImageFilename = "image.png";

class ParserModel {
  public:
  void read_from_file(ObjectModel* object, const std::string &filename);
  void write_to_file(const ObjectModel* object, const std::string &filename) const;
};


}  // namespace s21

#endif  // SRC_DATA_PARSER_MODEL_H
