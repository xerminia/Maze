TEST(parsing_file, parsing_file_test) {
  std::string filepath("example_file/10x10_cave.txt");
  s21::Cave test;
  bool ok = test.ParsingFile(filepath);
  ASSERT_EQ(ok, false);
  ASSERT_EQ(test.GetRows(), 10U);
  ASSERT_EQ(test.GetCols(), 10U);
  bool expected[100] = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0,
                        0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
                        1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
                        1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
                        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0,
                        1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0};
  int n = 0;
  for (size_t i = 0; i < test.GetCols(); i++) {
    for (size_t j = 0; j < test.GetRows(); j++) {
      ASSERT_EQ(test.GetValue(i, j), expected[n]);
      n++;
    }
  }
}

TEST(one_step, one_step_test) {
  std::string filepath("example_file/10x10_cave.txt");
  s21::Cave test;
  test.ParsingFile(filepath);
  test.OneStep();
  bool expected[100] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0,
                        0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1,
                        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
                        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
                        1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1};
  int n = 0;
  for (size_t i = 0; i < test.GetCols(); i++) {
    for (size_t j = 0; j < test.GetRows(); j++) {
      ASSERT_EQ(test.GetValue(i, j), expected[n]);
      n++;
    }
  }
}

TEST(all_live, all_live_test) {
  s21::Cave test;
  test.SetRowsAndColsCave(50U, 50U);
  test.GenerateCave();
  test.SetLimitBirth(7U);
  test.SetLimitOfDeath(7U);
  for (int i = 0; i < 5; i++) test.OneStep();
  for (size_t i = 0; i < test.GetCols(); i++) {
    for (size_t j = 0; j < test.GetRows(); j++) {
      ASSERT_EQ(test.GetValue(i, j), false);
    }
  }
}

TEST(all_death, all_death_test) {
  s21::Cave test;
  test.SetRowsAndColsCave(50U, 50U);
  test.GenerateCave();
  test.SetLimitBirth(0U);
  test.SetLimitOfDeath(0U);
  for (int i = 0; i < 5; i++) test.OneStep();
  for (size_t i = 0; i < test.GetCols(); i++) {
    for (size_t j = 0; j < test.GetRows(); j++) {
      ASSERT_EQ(test.GetValue(i, j), true);
    }
  }
}

TEST(parsing_file_error, parsing_file_error_test_1) {
  std::string filepath("example_file/10x10.txt");
  s21::Cave test;
  bool ok = test.ParsingFile(filepath);
  ASSERT_EQ(ok, true);
}

TEST(parsing_file_error, parsing_file_error_test_2) {
  std::string filepath("example_file/test_cave1.txt");
  s21::Cave test;
  bool ok = test.ParsingFile(filepath);
  ASSERT_EQ(ok, true);
}

TEST(parsing_file_error, parsing_file_error_test_3) {
  std::string filepath("example_file/test_cave2.txt");
  s21::Cave test;
  bool ok = test.ParsingFile(filepath);
  ASSERT_EQ(ok, true);
}

TEST(parsing_file_error, parsing_file_error_test_4) {
  std::string filepath("example_file/test_cave3.txt");
  s21::Cave test;
  bool ok = test.ParsingFile(filepath);
  ASSERT_EQ(ok, true);
}

TEST(parsing_file_error, parsing_file_error_test_5) {
  std::string filepath("example_file/test_cave4.txt");
  s21::Cave test;
  bool ok = test.ParsingFile(filepath);
  ASSERT_EQ(ok, true);
}

TEST(parsing_file_max_50, parsing_file_max_50) {
  std::string filepath("example_file/test_cave5.txt");
  s21::Cave test;
  bool ok = test.ParsingFile(filepath);
  ASSERT_EQ(ok, true);
}

TEST(save_file, save_file_test) {
  s21::Cave test;
  test.SetRowsAndColsCave(10U, 10U);
  test.GenerateCave();
  test.SaveFile("example_file/test_cave6.txt");
}
