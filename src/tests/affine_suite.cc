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
    if (str1 != str2) {
      double x1, y1, z1, x2, y2, z2;
      std::stringstream ss1(str1), ss2(str2);
      ss1 >> x1 >> y1 >> z1;
      ss2 >> x2 >> y2 >> z2;
      ASSERT_NEAR(x1, x2, kEps);
      ASSERT_NEAR(y1, y2, kEps);
      ASSERT_NEAR(z1, z2, kEps);
    }
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

TEST(affine_suite, suite_1) {
  FacadeModel model = create_model("test1.cobj");
  std::fstream file = open_file("test1.robj");

  model.add_points_scaling("2", "2", "1");
  model.execute_changes();

  ASSERT_POINTS("test1.tobj", file, model);
}

TEST(affine_suite, suite_2) {
  FacadeModel model = create_model("test2.cobj");
  std::fstream file = open_file("test2.robj");

  model.add_points_rotation("90", "x");

  model.execute_changes();
  model.add_points_rotation("90", "y");
  model.execute_changes();

  ASSERT_POINTS("test2.tobj", file, model);
}

TEST(affine_suite, suite_3) {
  FacadeModel model = create_model("test3.cobj");
  std::fstream file = open_file("test3.robj");

  model.add_points_movement("-1", "-5", "-9");
  model.execute_changes();
  model.add_points_movement("1", "5", "9");
  model.execute_changes();

  ASSERT_POINTS("test3.tobj", file, model);
}

TEST(affine_suite, suite_4) {
  FacadeModel model = create_model("test4.cobj");
  std::fstream file = open_file("test4.robj");

  model.add_points_scaling("2", "2", "10");
  model.execute_changes();
  model.add_points_rotation("90", "x");
  model.execute_changes();
  model.add_points_rotation("270", "x");
  model.execute_changes();
  model.add_points_scaling("0.5", "0.5", "0.1");
  model.execute_changes();

  ASSERT_POINTS("test4.tobj", file, model);
}

TEST(affine_suite, suite_5) {
  FacadeModel model = create_model("test5.cobj");
  std::fstream file = open_file("test5.robj");

  for (const auto& i : {"x", "y", "z", "z", "z", "y", "x", "y"}) {
    model.add_points_rotation("360", i);
    model.execute_changes();
  }

  ASSERT_POINTS("test5.tobj", file, model);
}

}  // namespace s21
