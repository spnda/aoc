#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

uint64_t getPriority(char c) {
    if (c >= 'A' && c <= 'Z')
        return (c - 'A') + 27;
    else
        return (c - 'a') + 1;
}

template <typename A, typename B>
auto findCommon(A a, B b) {
    std::unordered_set<char> common = {};
    for (char i : a)
        for (char j : b)
            if (i == j)
                common.emplace(i);
    return common;
}

int main() {
    std::ifstream file("rucksacks.txt");

    std::string ln;
    uint64_t priorities1 = 0;

    uint64_t groupIndex = 0;
    uint64_t priorities2 = 0;
    std::array<std::string, 2> groupCommon = {};
    while (std::getline(file, ln)) {
        auto comp1 = std::string_view(ln).substr(0, ln.size() / 2);
        auto comp2 = std::string_view(ln).substr(ln.size() / 2);
        {
            auto common = findCommon(comp1, comp2);
            for (auto& c : common)
                priorities1 += getPriority(c);
        }

        if ((groupIndex + 1) % 3 == 0) {
            auto common = findCommon(groupCommon[0], groupCommon[1]);
            auto common2 = findCommon(common, ln);
            for (auto& c : common2)
                priorities2 += getPriority(c);
            groupIndex = 0;
        } else {
            groupCommon[groupIndex] = ln;
            ++groupIndex %= 3;
        }
    }
    std::cout << "Part one: " << priorities1 << std::endl;
    std::cout << "Part two: " << priorities2 << std::endl;
}
