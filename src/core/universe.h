#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <vector>
#include <memory>

enum Cell { Dead = 0, Alive = 1 };

/*
 * The Universe stores the whole things of the lifegame.
 */
class Universe {
 public:
  using DataMatrix = std::vector<Cell>;

 private:
  /* Double Buffering for data updating */
  std::unique_ptr<DataMatrix> current_data, next_data;
  std::size_t height, width;

 public:
  explicit Universe(std::size_t size) : Universe(size, size) {}
  Universe(std::size_t height, std::size_t width)
      : height(height),
        width(width),
        current_data(
            std::make_unique<DataMatrix>(DataMatrix(height * width, Dead))),
        next_data(
            std::make_unique<DataMatrix>(DataMatrix(height * width, Dead))) {}

  std::size_t get_height() const { return height; }
  std::size_t get_width() const { return width; }

  void next() {
    compute_next();
    std::swap(current_data, next_data);
  }

 private:
  /* Core Algorithm: compute next universe into next_data*/
  void compute_next();

 public:
  /* Type Casting functions*/
  Universe(const std::vector<Cell>&);
  Universe(const std::vector<int>&);
  template <size_t N>
  Universe(const char (&)[N]);
  Universe(const char*);
  Universe(const std::string_view&);

  operator std::vector<Cell>() const;
  operator std::vector<int>() const;
  operator std::string() const;

  /* Some operator override. For test mainly*/
  bool operator==(const Universe& other) const {
    return (*current_data) == *(other.current_data);
  }
  friend std::ostream& operator<<(std::ostream& out, const Universe&);
  /* iter functions (maybe)*/
  Cell& operator[](std::size_t idx) { return (*current_data)[idx]; }
  Cell operator[](std::size_t idx) const { return (*current_data)[idx]; }

  DataMatrix::iterator begin() { return current_data->begin(); }
  DataMatrix::iterator end() { return current_data->end(); }
  DataMatrix::const_iterator cbegin() const { return current_data->cbegin(); }
  DataMatrix::const_iterator cend() const { return current_data->cend(); }
};

inline std::optional<Cell> char2Cell(char c) {
  switch (c) {
    case 'X':
    case '#':
    case '1':
    case '@':
      return Alive;
    case '\t':
    case '\r':
    case '\n':
    case '\v':
    case '\f':
    case ' ':
      /* Skip whitespace characters. */
      return std::nullopt;
    default:
      return Dead;
  }
}
template <size_t N>
Universe::Universe(const char (&str)[N]) : Universe((size_t)std::sqrt(N - 1)) {
  size_t idx = 0;
  for (size_t i = 0; i < N - 1; i++) {
    auto value = char2Cell(str[i]);
    if (value) (*current_data)[idx] = *value;
  }
}