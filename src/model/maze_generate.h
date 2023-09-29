#ifndef SRC_MODEL_MAZE_GENERATE_H_
#define SRC_MODEL_MAZE_GENERATE_H_

#include <ctime>

#include "object.h"

namespace s21 {
class MazeGenerate {
 public:
  MazeGenerate();
  MazeGenerate(size_t rows, size_t cols);
  ~MazeGenerate() = default;

  inline void SetRows(size_t num) { maze_.SetRows(num); }
  inline void SetCols(size_t num) { maze_.SetCols(num); }

  inline Object GetMaze() { return maze_; }

  void MazeGen();

  void ZeroingMultiplicity(std::vector<std::vector<int>> &multiplicity);
  void SetMultiplicityRow(std::vector<int> &row);
  void MergeMultiplicity(std::vector<int> &row, const int element,
                         const int mul);
  bool CheckSingleMultiplicity(const std::vector<int> &row, int number);
  bool CheckSingleWithoutBorderMultiplicity(const std::vector<int> &row,
                                            int number,
                                            std::vector<bool> multiplicity);
  void CopyPrevRow(const std::vector<int> &prev_row, std::vector<int> &row,
                   const std::vector<bool> down_walls_row);
  void EndMaze(std::vector<int> &multiplicity,
               std::vector<bool> &right_walls_row);

 private:
  Object maze_;
  size_t multiplicity_count_;

 private:
  void SetRightBorder(std::vector<int> &row);
  void SetDownBorder(std::vector<int> &row);
  void AddEndDownBorder(std::vector<bool> &down_walls_row);
  int CountNumberInRow(const std::vector<int> &row, const int &number);
};
}  // namespace s21

#endif  // SRC_MODEL_MAZE_GENERATE_H_
