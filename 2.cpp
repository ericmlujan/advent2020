#include <iostream>

struct PasswordPolicy {
  char letter = '\0';
  int min = 0;
  int max = 0;
};

PasswordPolicy parsePolicy(const std::string& policyString) {
  PasswordPolicy res;
  size_t splitIdx = 0;
  for (size_t i = 0; i < policyString.size(); ++i) {
    if (policyString[i] == '-') {
      res.min = std::atoi(policyString.substr(0, i).c_str());
      splitIdx = i;
      continue;
    }
    if (policyString[i] == ' ') {
      res.max = std::atoi(policyString.substr(splitIdx + 1, i).c_str());
      splitIdx = i;
      continue;
    }
    res.letter = policyString.back();
  }

  return res;
}

bool passwordValidPartOne(const PasswordPolicy& policy, const std::string& password) {
  size_t letterCount = 0;
  for (char letter : password) {
    if (letter == policy.letter) {
      ++letterCount;
    }
  }
  return letterCount >= policy.min && letterCount <= policy.max;
}

bool passwordValidPartTwo(const PasswordPolicy& policy, const std::string& password) {
  size_t matchCount = 0;

  if (password[policy.min - 1] == policy.letter) {
    ++matchCount;
  }
  if (password[policy.max - 1] == policy.letter) {
    ++matchCount;
  }

  return matchCount == 1;
}

int main(int argc, char** argv) {
  size_t validCountPartOne = 0;
  size_t validCountPartTwo = 0;

  for (std::string line; std::getline(std::cin, line);) {
    // Split string on colon-space
    auto splitIdx = line.find(": ");
    std::string policyString = line.substr(0, splitIdx);
    std::string passwordString = line.substr(splitIdx + 2);

    auto policy = parsePolicy(policyString);
    if (passwordValidPartOne(policy, passwordString)) {
      ++validCountPartOne;
    }

    if (passwordValidPartTwo(policy, passwordString)) {
      ++validCountPartTwo;
    }
  }

  std::cout << validCountPartOne << std::endl;
  std::cout << validCountPartTwo << std::endl;
  return 0;
}
