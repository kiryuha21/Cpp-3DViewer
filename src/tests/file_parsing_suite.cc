#include <gtest/gtest.h>

#include "../model/ParserModel.h"

namespace s21 {
const std::string path = "tests/obj/";

TEST(file_parsing_suite, parse_not_existing) {
  ObjectModel* object_model = new ObjectModel;
  ParserModel parser_model;

  ASSERT_THROW(parser_model.read_from_file(object_model, "not_exist.obj"),
               std::logic_error);

  delete object_model;
}

TEST(file_parsing_suite, parse_broken) {
  ObjectModel* object_model = new ObjectModel;
  ParserModel parser_model;

  ASSERT_THROW(
      parser_model.read_from_file(object_model, "tests/obj/broken.tobj"),
      std::logic_error);

  delete object_model;
}

TEST(file_parsing_suite, parse_normal) {
  ObjectModel* object_model = new ObjectModel;
  ParserModel parser_model;

  ASSERT_NO_THROW(
      parser_model.read_from_file(object_model, "tests/obj/test1.cobj"));

  delete object_model;
}
}  // namespace s21
