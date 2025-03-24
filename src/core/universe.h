#pragma once

#include <vector>

enum Cell { Dead = 0, Alive = 1 };

/*
 * The Universe stores the whole things of the lifegame.
 */
class Universe {
 public:
  using DataMatrix = std::vector<std::vector<Cell>>;

 private:
  /* Double Buffering for data updating */
  std::unique_ptr<DataMatrix> current_data, next_data;
  std::size_t height, width;

 public:
  explicit Universe(std::size_t size) : Universe(size, size) {}
  Universe(std::size_t height, std::size_t width);
  void fill_with(Cell);
  Cell get(std::size_t x, std::size_t y) const { return (*current_data)[x][y]; }
  void next() {
    compute_next();
    std::swap(current_data, next_data);
  }

 private:
  /* Core Algorithm: compute next universe into next_data*/
  void compute_next();
};