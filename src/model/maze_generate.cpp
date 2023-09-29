#include "maze_generate.h"

namespace s21 {
MazeGenerate::MazeGenerate() : multiplicity_count_(1) {
  maze_.SetRows(0);
  maze_.SetCols(0);
}

MazeGenerate::MazeGenerate(size_t rows, size_t cols) : multiplicity_count_(1) {
  maze_.SetRows(rows);
  maze_.SetCols(cols);
}

void MazeGenerate::MazeGen() {
  std::vector<std::vector<int>> multiplicity(maze_.GetRows());
  ZeroingMultiplicity(multiplicity);
  for (size_t i = 0; i < maze_.GetRows(); i++) {
    SetMultiplicityRow(multiplicity[i]);
    SetRightBorder(multiplicity[i]);
    SetDownBorder(multiplicity[i]);
    if (i != maze_.GetRows() - 1) {
      CopyPrevRow(multiplicity[i], multiplicity[i + 1],
                  maze_.GetDownWalls()[i]);
    }
  }
  AddEndDownBorder(maze_.GetDownWallsPointer()[maze_.GetRows() - 1]);
  EndMaze(multiplicity[maze_.GetRows() - 1],
          maze_.GetRightWallsPointer()[maze_.GetRows() - 1]);
}

void MazeGenerate::SetMultiplicityRow(std::vector<int> &row) {
  for (size_t i = 0; i < maze_.GetCols(); i++) {
    if (row[i] == 0) {
      row[i] = multiplicity_count_;
      multiplicity_count_++;
    }
  }
}

void MazeGenerate::SetRightBorder(std::vector<int> &row) {
  std::vector<bool> tmp(maze_.GetCols());

  for (size_t i = 0; i < maze_.GetCols() - 1; i++) {
    bool random_border = arc4random() % 2;
    if (row[i] == row[i + 1] || random_border == true) {
      tmp[i] = true;
    } else {
      MergeMultiplicity(row, row[i + 1], row[i]);
    }
  }
  tmp[maze_.GetCols() - 1] = true;
  maze_.SetRightWallsInLine(tmp);
}

void MazeGenerate::SetDownBorder(std::vector<int> &row) {
  std::vector<bool> tmp(maze_.GetCols());
  for (size_t i = 0; i < maze_.GetCols(); i++) {
    bool random_border = arc4random() % 2;
    if (random_border && CheckSingleMultiplicity(row, row[i]) &&
        CheckSingleWithoutBorderMultiplicity(row, row[i], tmp)) {
      tmp[i] = true;
    } else {
      tmp[i] = false;
    }
  }
  maze_.SetDownWallsInLine(tmp);
}

void MazeGenerate::CopyPrevRow(const std::vector<int> &prev_row,
                               std::vector<int> &row,
                               const std::vector<bool> down_walls_row) {
  for (size_t i = 0; i < maze_.GetCols(); i++) {
    if (down_walls_row[i] == false) {
      row[i] = prev_row[i];
    } else {
      row[i] = 0;
    }
  }
}

void MazeGenerate::EndMaze(std::vector<int> &multiplicity,
                           std::vector<bool> &right_walls_row) {
  for (size_t i = 0; i < maze_.GetCols() - 1; i++) {
    if (multiplicity[i] != multiplicity[i + 1]) {
      right_walls_row[i] = false;
      MergeMultiplicity(multiplicity, multiplicity[i + 1], multiplicity[i]);
    }
  }
}

void MazeGenerate::ZeroingMultiplicity(
    std::vector<std::vector<int>> &multiplicity) {
  for (size_t i = 0; i < maze_.GetRows(); i++) {
    for (size_t j = 0; j < maze_.GetCols(); j++) {
      multiplicity[i].push_back(0);
    }
  }
}

void MazeGenerate::AddEndDownBorder(std::vector<bool> &down_walls_row) {
  for (size_t i = 0; i < maze_.GetCols(); i++) {
    down_walls_row[i] = true;
  }
}

void MazeGenerate::MergeMultiplicity(std::vector<int> &row, const int element,
                                     const int mul) {
  for (size_t i = 0; i < maze_.GetCols(); i++) {
    if (row[i] == element) {
      row[i] = mul;
    }
  }
}

bool MazeGenerate::CheckSingleMultiplicity(const std::vector<int> &row,
                                           int number) {
  return (CountNumberInRow(row, number)) > 1;
}

bool MazeGenerate::CheckSingleWithoutBorderMultiplicity(
    const std::vector<int> &row, int number,
    const std::vector<bool> multiplicity) {
  int counter = 0;
  for (size_t i = 0; i < row.size(); i++) {
    if (row[i] == number && multiplicity[i] == 1) counter++;
  }
  return (CountNumberInRow(row, number) - 1) > counter;
}

int MazeGenerate::CountNumberInRow(const std::vector<int> &row,
                                   const int &number) {
  int counter = 0;
  for (size_t i = 0; i < row.size(); i++) {
    if (row[i] == number) counter++;
  }
  return counter;
}
}  // namespace s21
