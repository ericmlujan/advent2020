#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Slope = std::pair<size_t, size_t>;

struct Board {
  size_t width = 0;
  size_t height = 0;
  std::vector<char> cells;

  char query(size_t x, size_t y) const {
    if (y > height || y < 0 || x < 0) {
      return '\0';
    }
    size_t xWrapped = x % width;
    size_t index = y * width + xWrapped;
    assert(index < cells.size());
    return cells[index];
  }
};

Board parseBoard(const std::string& input) {
  Board res;
  size_t width = 0;
  size_t height = 0;

  res.cells.reserve(input.size());

  for (size_t i = 0; i < input.size(); ++i) {
    if (width == 0 && input[i] == '\n') {
      width = i;
    }
    if (input[i] == '\n' || input[i] == '\0') {
      ++height;
      continue;
    }
    res.cells.push_back(input[i]);
  }

  res.width = width;
  res.height = height;

  return res;
}

size_t traverse(const Board& board, const Slope& slope) {
  size_t count = 0;
  std::pair<size_t, size_t> pos{0, 0};

  while (pos.second < board.height) {
    bool hasTree = board.query(pos.first, pos.second) == '#';
    if (hasTree) {
      ++count;
    }

    pos.first += slope.first;
    pos.second += slope.second;
  }

  return count;
}

int main(int argc, char** argv) {
  const std::vector<Slope> slopes{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

  std::string input;
  std::getline(std::cin, input, '\0');

  Board board = parseBoard(input);

  // Part one
  std::cout << traverse(board, slopes[1]) << std::endl;

  // Part two
  size_t product = 1;
  for (const auto& slope : slopes) {
    product *= traverse(board, slope);
  }
  std::cout << product << std::endl;

  return 0;
}
