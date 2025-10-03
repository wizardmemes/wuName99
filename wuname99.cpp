#include <iostream>
#include <random>
#include <chrono>
#include "words.h"

int main(int argc, char* argv[]) {
  //Random Engine, seeded with current time
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> adjDist(0, adjectives.size() - 1);
  std::uniform_int_distribution<int> nounDist(0, nouns.size() - 1);
  std::uniform_int_distribution<int> numDist(10, 99);

  //Default = 1 name
  int count = 1;
  if (argc > 1) {
    std::string arg = argv[1];
    if (arg.rfind("--", 0) ==0) {
      try {
          count = std::stoi(arg.substr(2));
      } catch (...) {
          std::cerr << "Invalid argument. Usage: wuname99 [--N]\n";
          return 1;
      }
    }
  }

  for (int i = 0; i < count; i++) {
    std::string username =
      adjectives[adjDist(rng)] +
      nouns[nounDist(rng)] +
      std::to_string(numDist(rng));
    std::cout << username << std::endl;
  }

  return 0;
}

