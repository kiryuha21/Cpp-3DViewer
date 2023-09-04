#include "ParserModel.h"

#include <fstream>
#include <sstream>

namespace s21 {

void ParserModel::read_from_file(ObjectModel *object,
                                 const std::string &filename) {
  object->clear();
  std::fstream file(filename, std::ios::in);
  if (!file.is_open()) {
    throw std::logic_error("File opening error");
  }

  std::string str;
  while (std::getline(file, str)) {
    std::stringstream ss(str);
    char start = '0';
    ss >> start;
    if (start == 'v') {
      double x = 0, y = 0, z = 0;
      ss >> x >> y >> z;
      object->add_point(x, y, z);
    } else if (start == 'f') {
      int point_number = 0;
      std::vector<int> numbers;
      while (ss >> point_number) {
        if (point_number < 1) {
          throw std::logic_error("Point numbers in facet must be >= 1");
        }
        numbers.push_back(point_number);
      }
      object->add_facet(numbers);
    }
  }

  file.close();
}

std::string ParserModel::get_file_basename(const std::string &filename) const {
  return filename.substr(filename.rfind('/') + 1);
}

};  // namespace s21
