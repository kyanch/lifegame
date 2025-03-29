#include <cmath>
#include <cstddef>
#include <string>

#include "universe.h"

std::ostream& operator<<(std::ostream& out, const Universe& uni) {
  auto s = std::string(uni);
  out << s << std::endl;
  return out;
}
/*
 * Code about type cast writting here to avoid messup logi codes.
 */
Universe::Universe(const std::vector<Cell>& vec)
    : Universe(static_cast<std::size_t>(std::sqrt(vec.size()))) {
  // current_data may longer than vec
  std::copy(vec.begin(), vec.end(), current_data->begin());
}
Universe::operator std::vector<Cell>() const { return *current_data; }
Universe::Universe(const std::vector<int>& vec)
    : Universe(static_cast<std::size_t>(std::sqrt(vec.size()))) {
  std::transform(vec.begin(), vec.end(), current_data->begin(),
                 [](int d) { return static_cast<Cell>(d); });
}
Universe::operator std::vector<int>() const {
  std::vector<int> data(height * width);
  return std::vector<int>(current_data->begin(), current_data->end());
}

Universe::Universe(const char* str) : Universe(std::string_view(str)) {}
Universe::Universe(const std::string_view& str)
    : Universe((size_t)std::sqrt(str.length())) {
  size_t idx = 0;
  for (size_t i = 0; i < str.length(); i++) {
    auto value = char2Cell(str[i]);
    if (value) (*current_data)[idx++] = *value;
  }
}
Universe::operator std::string() const {
  std::string str(width * height, '\0');
  std::transform(current_data->begin(), current_data->end(), str.begin(),
                 [](Cell c) { return c == Alive ? 'X' : 'O'; });
  return str;
}