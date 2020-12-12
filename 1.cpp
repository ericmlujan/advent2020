#include <iostream>
#include <optional>
#include <unordered_set>
#include <utility>

std::optional<std::pair<int, int>> findNumber(const std::unordered_set<int>& s, const int target) {
  for (const int i : s) {
    int dual = target - i;
    const auto value = s.find(dual);
    if (value != s.end()) {
      return std::make_pair(i, *value);
    }
  }
  return std::nullopt;
}

int main(int argc, char** argv) {
  std::unordered_set<int> s;
  int line;
  while (std::cin) {
    std::cin >> line;
    s.insert(line);
  }

  // Part one
  {
    auto result = findNumber(s, 2020);
    if (result.has_value()) {
      std::cout << result.value().first * result.value().second << std::endl;
    }
  }

  // Part two
  {
    for (const int i : s) {
      int target = 2020 - i;
      auto result = findNumber(s, target);
      if (result.has_value()) {
        std::cout << i * result.value().first * result.value().second << std::endl;
        break;
      }
    }
  }

  return 0;
}
