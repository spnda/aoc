#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("calories.txt");

    std::string ln;
    std::vector<uint64_t> elfs = {};
    std::vector<uint64_t> calories;
    while (std::getline(file, ln)) {
        if (ln.empty()) {
            uint64_t count = 0;
            for (const auto& cal : calories)
                count += cal;
            elfs.emplace_back(count);
            calories.clear();
        } else {
            calories.emplace_back(std::stoll(ln));
        }
    }
    std::sort(elfs.begin(), elfs.end());
    std::cout << elfs.back() << std::endl;
    std::cout << elfs[elfs.size() - 3] + elfs[elfs.size() - 2] + elfs[elfs.size() - 1] << std::endl;
}
