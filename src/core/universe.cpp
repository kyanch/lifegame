#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>

#include "universe.h"

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
                     const std::array<int, 9> kernel) {
  // clang-format off
    return
     row1[-1]*kernel[0]+row1[0]*kernel[1]+row1[1]*kernel[2]+
     row2[-1]*kernel[3]+row2[0]*kernel[4]+row2[1]*kernel[5]+
     row3[-1]*kernel[6]+row3[0]*kernel[7]+row3[1]*kernel[8];
  // clang-format on
}

/* Get Cell from the result of convolution */
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

static std::vector<Cell> padding(const std::vector<Cell>& data, size_t height,
                                 size_t width) {
  /* Padding = 1 */
  size_t full_height = height + 2, full_width = width + 2;
  /* Filling with Dead value*/
  std::vector<Cell> new_vec(full_height * full_width, Dead);

  /* Copy origin data back */
  const Cell* row_iter = data.data();
  Cell* target_iter = new_vec.data() + full_width + 1;
  for (size_t row = 0; row < height; row++) {
    std::copy(row_iter, row_iter + width, target_iter);
    row_iter += width, target_iter += full_width;
  }
  return new_vec;
}
void Universe::compute_next() {
  auto vec_pad = padding(*current_data, height, width);

  size_t full_width = width + 2;
  /* Using 3x3 2D convolution to update next_data */
  /* begin at the second element to skip padding */
  auto row1 = vec_pad.data() + 1;
  auto row2 = row1 + full_width;
  auto row3 = row2 + full_width;
  // begin with second row to skip padding row.
  auto target_iter = next_data->data();
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      int status = conv2d_op(row1 + j, row2 + j, row3 + j, CONV_KERNEL);
      target_iter[j] = update_cell_with_status(status);
    }
    /* Target is not padded, add width only*/
    target_iter += width;
    row1 = row2, row2 = row3, row3 = row3 + full_width;
  }
}