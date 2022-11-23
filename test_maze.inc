TEST(test_zeroing_multiplicity, zeroing_multiplicity_1) {
  s21::MazeGenerate test;
  test.SetRows(5);
  test.SetCols(5);
  std::vector<std::vector<int>> test_multiplicity(test.GetMaze().GetRows());
  test.ZeroingMultiplicity(test_multiplicity);

  for (size_t i = 0; i < test.GetMaze().GetRows(); i++) {
    for (size_t j = 0; j < test.GetMaze().GetCols(); j++) {
      ASSERT_EQ(test_multiplicity[i][j], 0);
    }
  }
}

TEST(test_set_multiplicity_row, set_multiplicity_row_1) {
  s21::MazeGenerate test(5, 5);
  std::vector<std::vector<int>> test_multiplicity(test.GetMaze().GetRows());
  test.ZeroingMultiplicity(test_multiplicity);
  test.SetMultiplicityRow(test_multiplicity[0]);
  int true_arr[5] = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < test.GetMaze().GetCols(); i++) {
      ASSERT_EQ(test_multiplicity[0][i], true_arr[i]);
    }
}

TEST(test_merge_multiplicity, merge_multiplicity_1) {
  s21::MazeGenerate test(5, 5);
  std::vector<int> test_row = {1, 1, 2, 2, 2};
  test.MergeMultiplicity(test_row, 2, 1);
  int true_arr[5] = {1, 1, 1, 1, 1};

    for (size_t i = 0; i < test.GetMaze().GetCols(); i++) {
      ASSERT_EQ(test_row[i], true_arr[i]);
    }
}

TEST(test_check_single_multiplicity, check_single_multiplicity_1) {
  s21::MazeGenerate test(5, 5);
  std::vector<int> test_row_1 = {1, 2, 2, 2, 2};
  std::vector<int> test_row_2 = {2, 2, 2, 2, 2};

  ASSERT_EQ(test.CheckSingleMultiplicity(test_row_1, 1), 0);
  ASSERT_EQ(test.CheckSingleMultiplicity(test_row_2, 2), 1);
}

TEST(test_check_single_without_border_multiplicity, check_single_without_border_multiplicity_1) {
  s21::MazeGenerate test(5, 5);
  std::vector<int> test_row_1 = {1, 2, 2, 2, 2};
  std::vector<int> test_row_2 = {1, 2, 2, 2, 1};

  std::vector<bool> down_border = {0, 1, 1, 0, 0};

  ASSERT_EQ(test.CheckSingleWithoutBorderMultiplicity(test_row_1, 2, down_border), 1);
  ASSERT_EQ(test.CheckSingleWithoutBorderMultiplicity(test_row_2, 2, down_border), 0);
}

TEST(test_copy_prev_row, copy_prev_row_1) {
  s21::MazeGenerate test(5, 5);
  std::vector<int> test_prev_row = {1, 2, 3, 3, 5};
  std::vector<int> test_row = {0, 0, 0, 0, 0};
  std::vector<bool> down_border = {1, 0, 0, 1, 0};
  int true_arr[5] = {0, 2, 3, 0, 5};

  test.CopyPrevRow(test_prev_row, test_row, down_border);

  for (size_t i = 0; i < test.GetMaze().GetCols(); i++) {
      ASSERT_EQ(test_row[i], true_arr[i]);
  }
}

TEST(test_end_maze, end_maze_1) {
  s21::MazeGenerate test(5, 5);
  std::vector<std::vector<int>> test_multiplicity(test.GetMaze().GetRows());
  test.ZeroingMultiplicity(test_multiplicity);

  std::vector<int> test_row = {1, 2, 2, 3, 5};
  std::vector<bool> right_border = {1, 0, 0, 1, 1};

  std::vector<int> true_arr = {1, 1, 1, 1, 1};
  std::vector<bool> true_right_border = {0, 0, 0, 0, 1};

  test.EndMaze(test_row, right_border);

  for (size_t i = 0; i < test.GetMaze().GetCols(); i++) {
      ASSERT_EQ(test_row[i], true_arr[i]);
  }

    for (size_t i = 0; i < test.GetMaze().GetCols(); i++) {
      ASSERT_EQ(right_border[i], true_right_border[i]);
  }
}

TEST(test_generation_maze, generation_maze_1) {
  s21::Maze test;
  test.GenerateMaze(15, 15);
  test.SetBeginI(0);
  test.SetBeginJ(0);

  for (size_t i = 0; i < test.GetObject().GetRows(); i++) {
    for (size_t j = 1; j < test.GetObject().GetCols(); j++) {
      test.SetEndI(i);
      test.SetEndJ(j);
      ASSERT_EQ(test.ShortestPathGeneration(), true);
    }
  }
}

TEST(parsing_file_maze, parsing_file_maze_test) {
  std::string filepath("example_file/10x10.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), false);
}

TEST(parsing_file_maze_check_error, check_error_test_1) {
  std::string filepath("example_file/test_maze1.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_2) {
  std::string filepath("example_file/test_maze2.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_3) {
  std::string filepath("example_file/test_maze3.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_4) {
  std::string filepath("example_file/test_maze4.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_5) {
  std::string filepath("example_file/test_maze5.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_6) {
  std::string filepath("example_file/test_maze6.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_7) {
  std::string filepath("example_file/test_maze7.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_8) {
  std::string filepath("example_file/test_maze8.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_9) {
  std::string filepath("example_file/test_maze9.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(parsing_file_maze_check_error, check_error_test_10) {
  std::string filepath("example_file/10x10_cave.txt");
  s21::Maze test;
  ASSERT_EQ(test.ParsingFile(filepath), true);
}

TEST(test_path_count_generation_check_error, check_error_test_1) {
  std::string filepath("example_file/4x4.txt");
  s21::Maze test;

  ASSERT_EQ(test.ParsingFile(filepath), false);

  test.SetBeginI(0);
  test.SetBeginJ(0);
  test.SetEndI(3);
  test.SetEndJ(3);

  ASSERT_EQ(test.ShortestPathGeneration(), false);
}

TEST(save_file_maze, save_file_maze_test) {
  s21::Maze test;
  test.GenerateMaze(10, 10);
  test.SaveFile("example_file/test_maze10.txt");

  ASSERT_EQ(test.ParsingFile("example_file/test_maze10.txt"), false);
}
