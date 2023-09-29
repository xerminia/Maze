#ifndef SRC_MODEL_OBJECT_H_
#define SRC_MODEL_OBJECT_H_

#include <cstdlib>
#include <vector>

namespace s21 {
class Object {
 public:
  Object()
      : rows_(0), cols_(0), begin_i_(0), begin_j_(0), end_i_(0), end_j_(0) {}
  ~Object() {}

  inline std::vector<std::vector<bool>> GetRightWalls() { return right_walls_; }
  inline void SetRightWallsInLine(std::vector<bool> vec) {
    right_walls_.push_back(vec);
  }

  inline std::vector<std::vector<bool>> GetDownWalls() { return down_walls_; }
  inline void SetDownWallsInLine(std::vector<bool> vec) {
    down_walls_.push_back(vec);
  }

  inline std::vector<std::vector<int>> GetFinalPath() { return final_path_; }
  inline void SetFinalPath(std::vector<std::vector<int>> vec) {
    final_path_ = vec;
  }

  inline size_t GetRows() { return rows_; }
  inline size_t GetCols() { return cols_; }
  inline auto &GetRightWallsPointer() { return right_walls_; }
  inline auto &GetDownWallsPointer() { return down_walls_; }

  inline void SetRows(size_t num) { rows_ = num; }
  inline void SetCols(size_t num) { cols_ = num; }

  inline int GetBeginI() { return begin_i_; }
  inline int GetBeginJ() { return begin_j_; }
  inline void SetBeginI(int num) { begin_i_ = num; }
  inline void SetBeginJ(int num) { begin_j_ = num; }

  inline int GetEndI() { return end_i_; }
  inline int GetEndJ() { return end_j_; }
  inline void SetEndI(int num) { end_i_ = num; }
  inline void SetEndJ(int num) { end_j_ = num; }

  inline void ZeroWriteFinalPath() {
    std::vector<int> tmp(rows_);
    for (size_t i = 0; i < cols_; i++) {
      final_path_.push_back(tmp);
    }
  }

  inline void Clear() {
    final_path_.clear();
    right_walls_.clear();
    down_walls_.clear();
    rows_ = 0;
    cols_ = 0;
  }

 private:
  std::vector<std::vector<bool>> right_walls_, down_walls_;
  size_t rows_, cols_;

  std::vector<std::vector<int>> final_path_;
  int begin_i_, begin_j_;
  int end_i_, end_j_;
};
}  // namespace s21

#endif  // SRC_MODEL_OBJECT_H_
