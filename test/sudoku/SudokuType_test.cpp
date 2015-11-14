#include "../../example/sudoku/SudokuType.hpp"

#include <gtest/gtest.h>

namespace {

TEST(SudokuType_test, ctor_default) {
  SudokuType type;
  EXPECT_EQ(9, type.n());
  EXPECT_EQ(81, type.size());
}

TEST(SudokuType_test, ctor_nxn_region) {
  EXPECT_EQ(1, SudokuType(1).n());
  EXPECT_EQ(1, SudokuType(1).size());
  EXPECT_EQ(4, SudokuType(4).n());
  EXPECT_EQ(16, SudokuType(4).size());
  EXPECT_EQ(9, SudokuType(9).n());
  EXPECT_EQ(81, SudokuType(9).size());
  EXPECT_EQ(16, SudokuType(16).n());
  EXPECT_EQ(256, SudokuType(16).size());

  // Not squares
  EXPECT_THROW(SudokuType(0), std::invalid_argument);
  EXPECT_THROW(SudokuType(3), std::invalid_argument);
  EXPECT_THROW(SudokuType(5), std::invalid_argument);
  EXPECT_THROW(SudokuType(8), std::invalid_argument);
}

TEST(SudokuType_test, ctor_nxm_region) {
  EXPECT_THROW(SudokuType(0, 5), std::invalid_argument);
  EXPECT_THROW(SudokuType(5, 0), std::invalid_argument);

  EXPECT_EQ(1, SudokuType(1, 1).n());
  EXPECT_EQ(2, SudokuType(1, 2).n());
  EXPECT_EQ(2, SudokuType(2, 1).n());
  EXPECT_EQ(9, SudokuType(1, 9).n());

  EXPECT_EQ(6, SudokuType(2, 3).n());
  EXPECT_EQ(8, SudokuType(2, 4).n());
  EXPECT_EQ(10, SudokuType(2, 5).n());
}

TEST(SudokuType_test, ctor_custom_region) {
  // size is not a square
  EXPECT_THROW(SudokuType(std::vector<unsigned>()), std::invalid_argument);
  EXPECT_THROW((SudokuType{0, 1}), std::invalid_argument);

  // invalid regions
  EXPECT_THROW((SudokuType{0, 0, 0, 1}), std::invalid_argument);
  EXPECT_THROW((SudokuType{0, 0, 1, 2}), std::invalid_argument);

  EXPECT_NO_THROW(SudokuType{0});
  EXPECT_NO_THROW(SudokuType{1});
  EXPECT_NO_THROW(SudokuType{999});
  EXPECT_NO_THROW((SudokuType{0, 0, 1, 1}));
  EXPECT_NO_THROW((SudokuType{0, 1, 1, 0}));
}

TEST(SudokuType_test, guess_type) {
  EXPECT_ANY_THROW(SudokuType::guess(
    "...."
    "...."
    "...."
    "..."
  ));
  EXPECT_ANY_THROW(SudokuType::guess(
    "...."
    "...."
    "...."
    "....."
  ));
  EXPECT_EQ(*SudokuType::make(4), *SudokuType::guess(
    "...."
    "...."
    "...."
    "...."
  ));
  EXPECT_EQ(*SudokuType::make(4), *SudokuType::guess(
    ".1|..\n"
    "..|2.\n"
    "-----\n"
    "z.|..\n"
    ".a|..\n"
  ));
}

}
