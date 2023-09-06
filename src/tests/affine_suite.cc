#include <gtest/gtest.h>

#include <fstream>

#include "../model/FacadeModel.h"

namespace s21 {

constexpr double kEps = 1e-7;
const std::string path = "tests/obj/";

void ASSERT_POINTS(const std::string& filename, std::fstream& file2,
                   const FacadeModel& model) {
  model.generate_data(path + filename);

  std::fstream file1(path + filename, std::ios::in);
  if (!file1.is_open()) {
    throw std::logic_error("File opening error[tests/affine_suite.cc/17]");
  }

  std::string str1, str2;
  while (std::getline(file1, str1) && std::getline(file2, str2)) {
    ASSERT_EQ(str1, str2);
  }

  ASSERT_FALSE(std::getline(file1, str1));
  ASSERT_FALSE(std::getline(file2, str2));

  file1.close();
  file2.close();
}

FacadeModel create_model(const std::string& filename) {
  FacadeModel model;
  model.read_from_file(path + filename);
  return model;
}

std::fstream open_file(const std::string& filename) {
  std::fstream file(path + filename, std::ios::in);
  if (!file.is_open()) {
    throw std::logic_error("File opening error[tests/affine_suite.cc/32]");
  }
  return file;
}

TEST(affine_suite, suite_2) {
  FacadeModel model = create_model("test1.cobj");
  std::fstream file = open_file("test1.robj");

  model.add_points_scaling("2", "2", "1");
  model.execute_changes();

  ASSERT_POINTS("test1.tobj", file, model);
}

}  // namespace s21
