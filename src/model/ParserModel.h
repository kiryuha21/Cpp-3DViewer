#ifndef SRC_DATA_PARSER_MODEL_H
#define SRC_DATA_PARSER_MODEL_H

#include "ObjectModel.h"

namespace s21 {

class ParserModel {
 public:
  void read_from_file(ObjectModel* object, const std::string& filename);
  std::string get_file_basename(const std::string& filename) const;

 private:
  int width_ = 0, height_ = 0;
};

}  // namespace s21

#endif  // SRC_DATA_PARSER_MODEL_H
