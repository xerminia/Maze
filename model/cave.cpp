#include "cave.h"

namespace s21 {
Cave::Cave()
    : cave_matrix_{},
      limit_birth_(4),
      limit_of_death_(4),
      init_chance_(50),
      check_error_(false) {}

bool Cave::ParsingFile(std::string path) {
  cave_matrix_.Clear();
  check_error_ = false;
  std::ifstream file(path);
  std::string line;
  getline(file, line);
  SetRowsCols(line);
  if (cave_matrix_.GetCols() > kMaxRange ||
      cave_matrix_.GetRows() > kMaxRange) {
    cave_matrix_.Clear();
    return true;
  }
  unsigned i{};
  while (getline(file, line) && !check_error_) {
    if (!line.empty()) {
      if (i >= cave_matrix_.GetRows()) {
        cave_matrix_.Clear();
        return true;
      }
      FillingMatrix(line, i);
      i++;
    }
  }
  if (check_error_) cave_matrix_.Clear();
  return check_error_;
}

void Cave::SaveFile(std::string path) {
  std::ofstream file(path);
  file << cave_matrix_.GetCols() << " ";
  file << cave_matrix_.GetRows() << std::endl;
  for (size_t i = 0; i < cave_matrix_.GetCols(); i++) {
    for (size_t j = 0; j < cave_matrix_.GetRows(); j++) {
      file << cave_matrix_(i, j);
      if (j < cave_matrix_.GetRows() - 1) file << " ";
    }
    file << std::endl;
  }
}

void Cave::SetRowsCols(std::string line) {
  if (*line.begin() < '1' || *line.begin() > '9') {
    check_error_ = true;
    return;
  }
  size_t pos{};
  unsigned rows{static_cast<unsigned int>(stoi(line, &pos))};
  line.erase(0, pos + 1);
  if (line.begin() == line.end() || *line.begin() < '1' ||
      *line.begin() > '9') {
    check_error_ = true;
    return;
  }
  check_error_ = cave_matrix_.SetRowsAndCols(
      rows, static_cast<unsigned int>(stoi(line, &pos)));
  line.erase(0, pos);
  if (line.begin() != line.end()) check_error_ = true;
}

int Cave::RollCell() { return arc4random() % kPercent; }

void Cave::FillingMatrix(std::string line, unsigned i) {
  for (unsigned j{}; line.begin() != line.end(); j++) {
    if ((*line.begin() == '0' || *line.begin() == '1') &&
        j < cave_matrix_.GetCols()) {
      cave_matrix_(i, j) = stoi(line);
      line.erase(0, 2);
    } else {
      check_error_ = true;
      break;
    }
  }
}

void Cave::GenerateCave() {
  for (size_t i = 0; i < cave_matrix_.GetRows(); i++) {
    for (size_t j = 0; j < cave_matrix_.GetCols(); j++) {
      if (RollCell() < init_chance_)
        cave_matrix_(i, j) = true;
      else
        cave_matrix_(i, j) = false;
    }
  }
}

void Cave::OneStep() {
  Matrix new_matrix(cave_matrix_.GetRows(), cave_matrix_.GetCols());
  for (unsigned i{}; i < cave_matrix_.GetRows(); i++) {
    for (unsigned j{}; j < cave_matrix_.GetCols(); j++) {
      unsigned population = cave_matrix_.PopulationCell(i, j);
      if (cave_matrix_(i, j)) {
        if (limit_of_death_ > population)
          new_matrix(i, j) = false;
        else
          new_matrix(i, j) = true;
      } else {
        if (limit_birth_ < population)
          new_matrix(i, j) = true;
        else
          new_matrix(i, j) = false;
      }
    }
  }
  cave_matrix_.Swap(new_matrix);
}

Matrix::Matrix(unsigned rows, unsigned cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) throw std::out_of_range("out_of_range");
  MemoryAllocation();
}

void Matrix::Clear() {
  if (matrix_ != nullptr) {
    if (matrix_[0] != nullptr) {
      delete[] matrix_[0];
      matrix_[0] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

bool &Matrix::operator()(unsigned i, unsigned j) {
  if (i >= rows_ || j >= cols_) throw std::out_of_range("out_of_range");
  return matrix_[i][j];
}

bool Matrix::SetRowsAndCols(unsigned rows, unsigned cols) {
  if (rows < 1 || cols < 1) return true;
  if (rows_ != rows || cols_ != cols) {
    Clear();
    rows_ = rows;
    cols_ = cols;
    MemoryAllocation();
  }
  return false;
}

unsigned Matrix::PopulationCell(unsigned x, unsigned y) {
  int res = 0;
  for (int i = x - 1; i < (int)x + 2; i++) {
    for (int j = y - 1; j < (int)y + 2; j++) {
      if (i < 0 || i >= (int)rows_ || j < 0 || j >= (int)cols_) {
        res++;
      } else if (i != (int)x || j != (int)y) {
        if (matrix_[i][j]) res++;
      }
    }
  }
  return res;
}

void Matrix::Swap(Matrix &other) {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
}

void Matrix::MemoryAllocation() {
  matrix_ = new bool *[rows_];
  matrix_[0] = new bool[rows_ * cols_];
  for (unsigned i{1}; i < rows_; i++) matrix_[i] = matrix_[0] + cols_ * i;
  for (unsigned i{}; i < rows_ * cols_; i++) matrix_[0][i] = false;
}
}  // namespace s21
