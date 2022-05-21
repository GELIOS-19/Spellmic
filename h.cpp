#include <array>
#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <tuple>
#include <vector>

inline float midpoint_formula(float left, float right) {
  return (left + right) / 2.0f;
}

template <typename Type>
int32_t vector_find_index(const std::vector<Type>& vector,
                          const Type& element) {
  auto it = std::find(vector.begin(), vector.end(), element);
  if (it != vector.end()) {
    return it - vector.begin();
  }
  return -1;
}

template <typename Type>
std::vector<Type> find_range(Type begin, Type end, Type step = 1) {
  std::vector<Type> values;
  for (Type value = begin; value < end; value += step) {
    values.push_back(value);
  }
  return values;
}

std::tuple<float, std::vector<std::array<float, 2>>> riemann_sum(
    const auto& equation, const std::array<float, 2>& range,
    const char algorithm[], const int& numberOfRectangles = 1) {
  float sum = 0.0F;
  std::vector<std::array<float, 2>> table;

  const float step =
      abs(range[1] - range[0]) / static_cast<float>(numberOfRectangles);
  for (const auto& value : find_range(range[0], range[1], step)) {
    table.push_back({value, equation(value)});
  }

  if (algorithm == "LRAM") {
    table.erase(table.begin() + table.size() - 1);
  } else if (algorithm == "RRAM") {
    table.erase(table.begin());
  } else if (algorithm == "MRAM") {
    std::vector<std::array<float, 2>> midPointTable;
    for (const auto& tableEntry : table) {
      const int32_t index = vector_find_index(table, tableEntry);
      try {
        auto midPointLValue =
            midpoint_formula(tableEntry.at(0), table.at(index + 1)[0]);
        midPointTable.push_back({midPointLValue, equation(midPointLValue)});
      } catch (...) {
        break;
      }
    }
    table = midPointTable.size() > 0 ? midPointTable : table;
  } else {
    std::cerr << std::format("\"{}\" Not a valid algorithm", algorithm);
    exit(-1);
  }

  for (const auto& tableEntry : table) {
    sum += abs(step * tableEntry[1]);
  }

  return std::make_tuple(sum, table);
}

int main(int argc, char const* argv[]) {
  const auto& result = riemann_sum(
      [](const float x) { return static_cast<float>(4 * x - pow(x, 2)); },
      {0, 4}, "MRAM", 100);
  const auto& sum = std::get<0>(result);
  const auto& table = std::get<1>(result);

  printf("sum:\n...%f\ntable:\n", sum);
  for (const auto& tableEntry : table) {
    printf("...(%f, %f)\n", tableEntry[0], tableEntry[1]);
  }

  return 0;
}
