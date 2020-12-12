#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Board {
  size_t width = 0;
  size_t height = 0;
  std::vector<char> cells;

  char query(size_t x, size_t y) {
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

int main(int argc, char** argv) {
  std::pair<size_t, size_t> pos{0, 0};
  const std::pair<size_t, size_t> slope{3, 1}; // Right, Down
  size_t countTrees = 0;

  std::string input;
  std::getline(std::cin, input, '\0');

  Board board = parseBoard(input);

  // Traverse board
  while (pos.first < board.height) {
    bool hasTree = board.query(pos.first, pos.second) == '#';
    if (hasTree) {
      ++countTrees;
    }

    pos.first += slope.first;
    pos.second += slope.second;
  }

  std::cout << "Got board of width " << board.width << " and height " << board.height << std::endl;

  std::cout << countTrees << std::endl;

  return 0;
}
