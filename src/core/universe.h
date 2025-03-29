#pragma once

#include <vector>
#include <memory>

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
  Cell get(std::size_t index) const {
    return get(index % width, index / width);
  }
  void set(const std::size_t index, const Cell value) {
    set(index % width, index / width, value);
  }
  void set(const std::size_t x, const std::size_t y, const Cell value) {
    (*current_data)[x][y] = value;
  }
  void next() {
    compute_next();
    std::swap(current_data, next_data);
  }
  std::size_t get_height()const{return height;}
  std::size_t get_width()const{return height;}

 private:
  /* Core Algorithm: compute next universe into next_data*/
  void compute_next();
};