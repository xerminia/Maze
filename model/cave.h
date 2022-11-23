#ifndef SRC_MODEL_CAVE_H_
#define SRC_MODEL_CAVE_H_

#include <fstream>

constexpr int kPercent = 100;
constexpr int kMaxRange = 50;

namespace s21 {
class Matrix {
 public:
  Matrix() = default;
  Matrix(unsigned rows, unsigned cols);
  ~Matrix() { Clear(); }

  void Clear();
  bool SetRowsAndCols(unsigned rows, unsigned cols);
  inline unsigned GetRows() { return rows_; }
  inline unsigned GetCols() { return cols_; }
  unsigned PopulationCell(unsigned x, unsigned y);
  bool &operator()(unsigned i, unsigned j);
  void Swap(Matrix &other);

 private:
  unsigned rows_{}, cols_{};
  bool **matrix_{nullptr};

 private:
  void MemoryAllocation();
};

class Cave {
 public:
  Cave();
  ~Cave() = default;

  bool ParsingFile(std::string path);
  void SaveFile(std::string path);
  inline unsigned GetCols() { return cave_matrix_.GetCols(); }
  inline unsigned GetRows() { return cave_matrix_.GetRows(); }
  inline bool GetValue(unsigned i, unsigned j) { return cave_matrix_(i, j); }
  inline void SetLimitBirth(int num) { limit_birth_ = num; }
  inline void SetLimitOfDeath(int num) { limit_of_death_ = num; }
  inline void SetInitChance(int num) { init_chance_ = num; }
  inline void SetRowsAndColsCave(unsigned row, unsigned col) {
    cave_matrix_.SetRowsAndCols(row, col);
  }
  void GenerateCave();
  void OneStep();
  void Clear() { cave_matrix_.Clear(); }

 private:
  Matrix cave_matrix_;
  unsigned limit_birth_;
  unsigned limit_of_death_;
  int init_chance_;
  bool check_error_;

 private:
  void FillingMatrix(std::string line, unsigned i);
  void SetRowsCols(std::string line);
  int RollCell();
};
}  // namespace s21

#endif  // SRC_MODEL_CAVE_H_
