#ifndef SRC_MODEL_MAZE_H_
#define SRC_MODEL_MAZE_H_

#include <fstream>

#include "maze_generate.h"

constexpr int kMaxRanger = 50;

namespace s21 {
class Maze {
 public:
  Maze() = default;
  ~Maze() = default;

  bool ParsingFile(std::string path);
  inline Object GetObject() { return object_; }
  bool ShortestPathGeneration();
  void FinalPathGeneration(std::vector<std::vector<int>> path_counting_, int x);
  bool PathCountGeneration(std::vector<std::vector<int>> &path_counting_,
                           int &x);
  void SaveFile(std::string path);
  void Clear() { object_.Clear(); }
  void GenerateMaze(int rows, int cols);

  inline void SetBeginI(int num) { object_.SetBeginI(num); }
  inline void SetBeginJ(int num) { object_.SetBeginJ(num); }
  inline void SetEndI(int num) { object_.SetEndI(num); }
  inline void SetEndJ(int num) { object_.SetEndJ(num); }

 private:
  Object object_;
  bool check_error_;

 private:
  void SetRowsAndCols(std::string line);
  void FillingVectors(std::string line);
};
}  // namespace s21

#endif  // SRC_MODEL_MAZE_H_
