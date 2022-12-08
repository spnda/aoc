#include <bitset>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

size_t rowSize;
std::vector<uint8_t> trees;

inline bool isVisible(size_t x, size_t y) {
    auto check = [](size_t row, size_t column, uint8_t height, std::function<void(size_t&, size_t&)> cb) -> bool {
        while (true) {
            auto& cmp = trees[row * rowSize + column];
            if (height <= cmp) return false;
            if (row == 0 || row == (trees.size() / rowSize) - 1) break;
            if (column == 0 || column == (rowSize - 1)) break;
            cb(row, column);
        }
        return true;
    };

    auto height = trees[x * rowSize + y];
    std::bitset<4> visible = {};
    visible[0] = check(x - 1, y, height, [](size_t& x, size_t& y) { --x; }); // Top
    visible[1] = check(x + 1, y, height, [](size_t& x, size_t& y) { ++x; }); // Bottom
    visible[2] = check(x, y - 1, height, [](size_t& x, size_t& y) { --y; }); // Left
    visible[3] = check(x, y + 1, height, [](size_t& x, size_t& y) { ++y; }); // Right
    return visible.any();
}

inline uint64_t scenicScore(size_t x, size_t y) {
    auto score = [](size_t row, size_t column, uint8_t height, std::function<void(size_t&, size_t&)> cb) -> uint64_t {
        uint64_t i = 1;
        while (true) {
            auto& cmp = trees[row * rowSize + column];
            if (height <= cmp) break;
            if (row == 0 || row == (trees.size() / rowSize) - 1) break;
            if (column == 0 || column == (rowSize - 1)) break;
            ++i;
            cb(row, column);
        }
        return i;
    };

    auto height = trees[x * rowSize + y];
    uint64_t value = 1;
    value *= score(x - 1, y, height, [](size_t& x, size_t& y) { --x; }); // Top
    value *= score(x + 1, y, height, [](size_t& x, size_t& y) { ++x; }); // Bottom
    value *= score(x, y - 1, height, [](size_t& x, size_t& y) { --y; }); // Left
    value *= score(x, y + 1, height, [](size_t& x, size_t& y) { ++y; }); // Right
    return value;
}

int main() {
    std::ifstream file("trees.txt");

    std::string ln;
    while (std::getline(file, ln)) {
        rowSize = ln.size();
        for (auto& ch : ln)
            trees.emplace_back(ch - '0');
    }

    uint64_t visible = rowSize * 2 + (trees.size() / rowSize - 2) * 2; // The edges are always visible
    uint64_t highestScore = 0;
    for (size_t i = 1; i < (trees.size() / rowSize) - 1; ++i) {
        for (size_t j = 1; j < rowSize - 1; ++j) {
            if (isVisible(i, j))
                ++visible;
            if (auto score = scenicScore(i, j); score > highestScore)
                highestScore = score;
        }
    }
    std::cout << visible << std::endl;
    std::cout << highestScore << std::endl;
}
