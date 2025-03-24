#include "universe.h"

#include <cstddef>

using std::size_t;

/* macros and functions for convolution */
#define ALIVE_WITH_TWO_NEIGHBOR (0x10 + 2)
#define ALIVE_WITH_THREE_NEIGHBOR (0x10 + 3)
#define DEAD_WITH_THREE_NEIGHBOR (0x00 + 3)
#define AM_I_ALIVE(status) ((0xF0 & status) != 0)
#define NEIGHBOR_COUNT(status) (0x0F & status)

constexpr static std::array<int, 9> CONV_KERNEL = {1, 1, 1, 1, 0x10,
                                                   1, 1, 1, 1};
static int conv2d_op(const Cell* row1, const Cell* row2, const Cell* row3,
                     const std::array<int, 9> kernel, std::size_t center_idx) {
  // clang-format off
    return
     row1[center_idx-1]*kernel[0]+row1[center_idx]*kernel[1]+row1[center_idx+1]*kernel[2]+
     row2[center_idx-1]*kernel[3]+row2[center_idx]*kernel[4]+row2[center_idx+1]*kernel[5]+
     row3[center_idx-1]*kernel[6]+row3[center_idx]*kernel[7]+row3[center_idx+1]*kernel[8];
  // clang-format on
}
static Cell update_cell_with_status(int status) {
  if (AM_I_ALIVE(status)) {
    if (2 == NEIGHBOR_COUNT(status) || 3 == NEIGHBOR_COUNT(status)) {
      return Alive;
    } else {
      return Dead;
    }
  } else {
    if (3 == NEIGHBOR_COUNT(status))
      return Alive;
    else
      return Dead;
  }
}

/* Allocate Universe Data with Padding */
static Universe::DataMatrix allocate_data(size_t height, size_t width,
                                          Cell value) {
  return Universe::DataMatrix(height + 2, std::vector<Cell>(width + 2, value));
}

Universe::Universe(size_t height, size_t width)
    : height(height),
      width(width),
      current_data(
          std::make_unique<DataMatrix>(allocate_data(height, width, Dead))),
      next_data(
          std::make_unique<DataMatrix>(allocate_data(height, width, Dead))) {}

void Universe::fill_with(Cell value) {
  auto data = *current_data;
  for (auto row : data) {
    std::fill(row.begin() + 1, row.end() - 1, value);
    /* Add paddings on two endpoints of a row. */
    *row.begin() = *(row.end() - 1) = Dead;
  }
  /* Add padding on first and last rows.*/
  std::fill(data[0].begin(), data[0].end(), Dead);
  std::fill(data[height + 1].begin(), data[height + 1].end(), Dead);
}

void Universe::compute_next() {
  /* Using 3x3 2D convolution to update next_data */
  auto row_iter = current_data->cbegin();
  auto row1 = (row_iter++)->data();
  auto row2 = (row_iter++)->data();
  auto row3 = (row_iter++)->data();
  // begin with second row to skip padding row.
  auto target_row_iter = next_data->begin()++;
  auto target_row = (target_row_iter++)->data();
  while (row_iter != current_data->cend()) {
    // Identically, begin with second column to skip padding column.
    for (size_t col_idx = 1; col_idx < this->width; col_idx++) {
      int status = conv2d_op(row1, row2, row3, CONV_KERNEL, col_idx);
      target_row[col_idx] = update_cell_with_status(status);
    }
    target_row = (target_row_iter++)->data();
    row1 = row2, row2 = row3, row3 = (row_iter++)->data();
  }
}