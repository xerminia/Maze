#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "model/cave.h"
#include "model/maze.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;
  Controller(s21::Maze *maze, s21::Cave *cave) : maze_(maze), cave_(cave) {}
  ~Controller() = default;

  inline Object GetObject() { return maze_->GetObject(); }
  inline bool Parsing(std::string path) { return maze_->ParsingFile(path); }
  inline void ClearMaze() { maze_->Clear(); }
  inline void GenerateMaze(int rows, int cols) {
    maze_->GenerateMaze(rows, cols);
  };

  inline bool ParsingCave(std::string path) { return cave_->ParsingFile(path); }
  inline unsigned GetRowsCave() { return cave_->GetRows(); }
  inline unsigned GetColsCave() { return cave_->GetCols(); }
  inline bool GetValueCave(unsigned i, unsigned j) {
    return cave_->GetValue(i, j);
  }
  inline void SetRowsAndColsCave(unsigned row, unsigned col) {
    cave_->SetRowsAndColsCave(row, col);
  }
  inline void SetLimitBirth(int num) { cave_->SetLimitBirth(num); }
  inline void SetLimitOfDeath(int num) { cave_->SetLimitOfDeath(num); }
  inline void SetInitChance(int num) { cave_->SetInitChance(num); }
  inline void GenerateCave() { cave_->GenerateCave(); }
  inline void OneStep() { cave_->OneStep(); }
  inline void ClearCave() { cave_->Clear(); }

  inline bool ShortestPathGeneration() {
    return maze_->ShortestPathGeneration();
  }
  inline void SetBeginI(int num) { maze_->SetBeginI(num); }
  inline void SetBeginJ(int num) { maze_->SetBeginJ(num); }
  inline void SetEndI(int num) { maze_->SetEndI(num); }
  inline void SetEndJ(int num) { maze_->SetEndJ(num); }

  inline void SaveFileCave(std::string path) { cave_->SaveFile(path); }
  inline void SaveFileMaze(std::string path) { maze_->SaveFile(path); }

 private:
  s21::Maze *maze_;
  s21::Cave *cave_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
