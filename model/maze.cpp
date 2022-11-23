#include "maze.h"

namespace s21 {
bool Maze::ParsingFile(std::string path) {
  object_.Clear();
  check_error_ = false;
  std::ifstream file(path);
  std::string line;
  getline(file, line);
  SetRowsAndCols(line);
  if (object_.GetCols() > kMaxRanger || object_.GetRows() > kMaxRanger) {
    return true;
  }
  unsigned i{};
  while (getline(file, line) && !check_error_) {
    if (!line.empty()) {
      if (i >= object_.GetRows()) {
        object_.Clear();
        return true;
      }
      FillingVectors(line);
      i++;
    } else {
      if (i < object_.GetRows()) {
        object_.Clear();
        return true;
      }
      i = 0;
    }
  }
  if (check_error_ || object_.GetRows() != object_.GetDownWalls().size()) {
    object_.Clear();
    return true;
  }
  return check_error_;
}

void Maze::GenerateMaze(int rows, int cols) {
  MazeGenerate generated_maze(rows, cols);
  generated_maze.MazeGen();
  object_ = generated_maze.GetMaze();
}

bool Maze::ShortestPathGeneration() {
  std::vector<std::vector<int>> path_counting_;
  std::vector<int> tmp(object_.GetCols());

  for (size_t i = 0; i < object_.GetRows(); i++) {
    path_counting_.push_back(tmp);
  }

  path_counting_[object_.GetBeginI()][object_.GetBeginJ()] = 1;
  int x = 1;
  if (!PathCountGeneration(path_counting_, x)) {
    return false;
  }

  FinalPathGeneration(path_counting_, x);

  return true;
}

bool Maze::PathCountGeneration(std::vector<std::vector<int>> &path_counting_,
                               int &x) {
  bool flag_err;
  while (path_counting_[object_.GetEndI()][object_.GetEndJ()] == 0) {
    flag_err = false;
    for (size_t i = 0;
         i < object_.GetRows() &&
         path_counting_[object_.GetEndI()][object_.GetEndJ()] == 0;
         i++) {
      for (size_t j = 0;
           j < object_.GetCols() &&
           path_counting_[object_.GetEndI()][object_.GetEndJ()] == 0;
           j++) {
        if (path_counting_[i][j] == x) {
          if (i != 0 && !object_.GetDownWalls()[i - 1][j] &&
              !path_counting_[i - 1][j]) {
            path_counting_[i - 1][j] = x + 1;
            flag_err = true;
          }
          if (j < object_.GetCols() - 1 && !object_.GetRightWalls()[i][j] &&
              !path_counting_[i][j + 1]) {
            path_counting_[i][j + 1] = x + 1;
            flag_err = true;
          }
          if (i < object_.GetRows() - 1 && !object_.GetDownWalls()[i][j] &&
              !path_counting_[i + 1][j]) {
            path_counting_[i + 1][j] = x + 1;
            flag_err = true;
          }
          if (j != 0 && !object_.GetRightWalls()[i][j - 1] &&
              !path_counting_[i][j - 1]) {
            path_counting_[i][j - 1] = x + 1;
            flag_err = true;
          }
        }
      }
    }
    if (!flag_err) {
      return false;
    }
    x++;
  }
  return true;
}

void Maze::FinalPathGeneration(std::vector<std::vector<int>> path_counting_,
                               int x) {
  std::vector<std::vector<int>> final_path;
  std::vector<int> tmp(object_.GetCols());

  for (size_t i = 0; i < object_.GetRows(); i++) {
    final_path.push_back(tmp);
  }
  int tmp_i = object_.GetEndI(), tmp_j = object_.GetEndJ();
  final_path[object_.GetEndI()][object_.GetEndJ()] = x;

  while (tmp_i != object_.GetBeginI() || tmp_j != object_.GetBeginJ()) {
    if (tmp_i > 0 && path_counting_[tmp_i - 1][tmp_j] == x - 1 &&
        !object_.GetDownWalls()[tmp_i - 1][tmp_j]) {
      final_path[tmp_i - 1][tmp_j] = x - 1;
      tmp_i--;

    } else if (tmp_j > 0 && path_counting_[tmp_i][tmp_j - 1] == x - 1 &&
               !object_.GetRightWalls()[tmp_i][tmp_j - 1]) {
      final_path[tmp_i][tmp_j - 1] = x - 1;
      tmp_j--;

    } else if (tmp_i < (int)object_.GetRows() - 1 &&
               path_counting_[tmp_i + 1][tmp_j] == x - 1 &&
               !object_.GetDownWalls()[tmp_i][tmp_j]) {
      final_path[tmp_i + 1][tmp_j] = x - 1;
      tmp_i++;

    } else if (tmp_j < (int)object_.GetCols() - 1 &&
               path_counting_[tmp_i][tmp_j + 1] == x - 1 &&
               !object_.GetRightWalls()[tmp_i][tmp_j]) {
      final_path[tmp_i][tmp_j + 1] = x - 1;
      tmp_j++;
    }
    x--;
  }
  object_.SetFinalPath(final_path);
}

void Maze::SetRowsAndCols(std::string line) {
  if (*line.begin() < '1' || *line.begin() > '9') {
    check_error_ = true;
    return;
  }
  size_t pos{};
  object_.SetRows(stoi(line, &pos));
  line.erase(0, pos + 1);
  if (line.begin() == line.end() || *line.begin() < '1' ||
      *line.begin() > '9') {
    check_error_ = true;
    return;
  }

  object_.SetCols(stoi(line, &pos));
  line.erase(0, pos);
  if (line.begin() != line.end()) check_error_ = true;
}

void Maze::FillingVectors(std::string line) {
  std::vector<bool> tmp_vector;
  while (line.begin() != line.end()) {
    if (*line.begin() != '0' && *line.begin() != '1') {
      check_error_ = true;
      return;
    }
    tmp_vector.push_back(stoi(line));
    line.erase(0, 2);
  }
  if (tmp_vector.size() != object_.GetCols()) {
    check_error_ = true;
    return;
  }
  if (object_.GetRightWalls().size() < object_.GetRows()) {
    object_.SetRightWallsInLine(tmp_vector);
  } else {
    object_.SetDownWallsInLine(tmp_vector);
  }
}

void Maze::SaveFile(std::string path) {
  std::ofstream file(path);
  file << object_.GetRows() << " ";
  file << object_.GetCols() << std::endl;
  for (size_t i = 0; i < object_.GetCols(); i++) {
    for (size_t j = 0; j < object_.GetRows(); j++) {
      file << object_.GetRightWalls()[i][j];
      if (j < object_.GetRows() - 1) file << " ";
    }
    file << std::endl;
  }
  file << std::endl;

  for (size_t i = 0; i < object_.GetCols(); i++) {
    for (size_t j = 0; j < object_.GetRows(); j++) {
      file << object_.GetDownWalls()[i][j];
      if (j < object_.GetRows() - 1) file << " ";
    }
    file << std::endl;
  }
}
}  // namespace s21
