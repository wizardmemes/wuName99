#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <cstdlib>
#include <cstdio>

#if defined(_WIN32)
#include <windows.h>
#endif

#include "words.h"

// Print help message
void printHelp() {
    std::cout <<
        "WuName99 - Random Wu-Tang style username generator\n\n"
        "Usage:\n"
        "  wuname99                 Generate one name\n"
        "  wuname99 --count N       Generate N names (e.g. --count 5)\n"
        "  wuname99 --copy | -c     Copy last generated name to clipboard\n"
        "  wuname99 --help | -h     Show this message\n\n"
        "Notes:\n"
        "  - Clipboard support uses pbcopy (macOS), xclip/xsel (Linux), or clip (Windows)\n"
        "  - Example: wuname99 --count 3 --copy\n";
}

// Copy text to the system clipboard (cross-platform)
bool copyToClipboard(const std::string& text) {
#if defined(__APPLE__)
    FILE* pipe = popen("pbcopy", "w");
#elif defined(__linux__)
    FILE* pipe = popen("xclip -selection clipboard", "w");
#elif defined(_WIN32)
    FILE* pipe = _popen("clip", "w");
#else
    FILE* pipe = nullptr;
#endif

    if (!pipe) {
        std::cerr << "Clipboard copy not supported on this system.\n";
        return false;
    }

    fwrite(text.c_str(), sizeof(char), text.size(), pipe);
    fflush(pipe);

#if defined(_WIN32)
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    std::cout << "(Copied to clipboard)\n";
    return true;
}

// Generate a random Wu-Tang style name
std::string generateName(std::mt19937& rng) {
    std::uniform_int_distribution<int> adjDist(0, adjectives.size() - 1);
    std::uniform_int_distribution<int> nounDist(0, nouns.size() - 1);

    const std::string& adj = adjectives[adjDist(rng)];
    const std::string& noun = nouns[nounDist(rng)];
    return adj + " " + noun;
}

int main(int argc, char* argv[]) {
    bool copyFlag = false;
    int count = 1;

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            printHelp();
            return 0;
        } 
        else if (arg == "--copy" || arg == "-c") {
            copyFlag = true;
        } 
        else if (arg == "--count") {
            if (i + 1 < argc) {
                try {
                    count = std::stoi(argv[++i]);
                    if (count < 1) count = 1;
                } catch (...) {
                    std::cerr << "Invalid count value. Example: --count 5\n";
                    return 1;
                }
            } else {
                std::cerr << "Missing number after --count.\n";
                return 1;
            }
        } 
        else {
            std::cerr << "Unknown argument: " << arg << "\n";
            return 1;
        }
    }

    // Initialize RNG
    std::mt19937 rng(static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()
    ));

    // Generate and display names
    std::string lastName;
    for (int i = 0; i < count; ++i) {
        lastName = generateName(rng);
        std::cout << lastName << '\n';
    }

    // Copy last generated name if requested
    if (copyFlag && !lastName.empty()) {
        copyToClipboard(lastName);
    }

    return 0;
}

