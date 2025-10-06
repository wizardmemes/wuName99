#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include "words.h"


void printHelp() {
  std::cout <<
  "WuName99 - Random Wu-Tang style username generator\n\n"
    "Usage:\n"
    "  wuname99              Generate one name\n"
    "  wuname99 --N          Generate N names (e.g. --5)\n"
    "  wuname99 --copy       Copy last generated name to clipboard\n"
    "  wuname99 --help       Show this message\n\n"
    "Notes:\n"
    "  • Clipboard support uses pbcopy (macOS), xclip/xsel (Linux), or clip (Windows)\n"
    "  • Example: wuname99 --3 --copy\n";
}

void copyToClipboard(const std::string& text) {
  FILE* pipe= popen("pbcopy", "w");
  if (pipe) {
    fwrite(text.c_str(), sizeof(char), text.size(), pipe);
    pclose(pipe);
    std::cout << "Copied to Clipboard." << std::endl;
  } else {
    std::cerr << "failed to access clipboard." << std::endl;
  }
}

int main(int argc, char* argv[]) {
    bool copyFlag = false;
    int count = 1;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--help") {
            printHelp();
            return 0;
        } else if (arg == "--copy") {
            copyFlag = true;
        } else if (arg.rfind("--", 0) == 0) {
            try {
                count = std::stoi(arg.substr(2));
                if (count < 1) count = 1;
            } catch (...) {
                std::cerr << "Invalid argument. Usage: wuname99 [--N] [--copy]\n";
                return 1;
            }
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            return 1;
        }
    }

    // Random Engine, seeded with current time
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> adjDist(0, adjectives.size() - 1);
    std::uniform_int_distribution<int> nounDist(0, nouns.size() - 1);
    std::uniform_int_distribution<int> numDist(10, 99);

    std::string lastName;

    for (int i = 0; i < count; i++) {
        lastName = adjectives[adjDist(rng)] +
                   nouns[nounDist(rng)] +
                   std::to_string(numDist(rng));
        std::cout << lastName << "\n";
    }

    if (copyFlag && !lastName.empty()) {
        copyToClipboard(lastName);
    }

    return 0;
}

