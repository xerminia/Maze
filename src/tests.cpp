#include <gtest/gtest.h>

#include "model/cave.h"
#include "model/maze.h"
#include "test_cave.inc"
#include "test_maze.inc"

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}