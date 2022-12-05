#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr bool partTwo = true;

int main() {
    std::ifstream f("stacks.txt");
    std::vector<std::vector<char>> stacks;
    std::string line;
    while (std::getline(f, line)) {
        if (stacks.size() == 0)
            stacks.resize(((line.size() - (line.size() % 4)) / 4) + 1);
        
        // The last numbered line
        if (line[1] >= '0' && line[1] <= '9')
            break;

        for (uint32_t i = 1, j = 0; i < line.size(); i += sizeof("] ["), ++j) {
            if (line[i] == ' ')
                continue;
            stacks[j].emplace_back(line[i]);
        }
    }

    for (auto& stack : stacks)
        std::reverse(stack.begin(), stack.end());

    std::getline(f, line); // Skip the empty line
    while (std::getline(f, line)) {
        // Split the string by whitespace, effectively extracting words.
        std::istringstream iss {line};
        std::vector<std::string> words {
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };
        uint32_t count = std::stoi(words[1]);
        size_t src = std::stoi(words[3]) - 1;
        size_t dst = std::stoi(words[5]) - 1;

        if constexpr (partTwo) {
            size_t prev = stacks[dst].size();
            stacks[dst].resize(prev + count);
            std::copy(stacks[src].end() - count, stacks[src].end(), stacks[dst].begin() + prev);
            stacks[src].resize(stacks[src].size() - count);
        } else {
            for (uint32_t i = 0; i < count; ++i) {
                stacks[dst].emplace_back(stacks[src].back());
                stacks[src].pop_back();
            }
        }
    }

    for (size_t i = 0; i < stacks.size(); ++i) {
        std::cout << stacks[i].back();
    }
    std::cout << std::endl;
}
