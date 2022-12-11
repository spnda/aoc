#include <fstream>
#include <iostream>
#include <string>

using pair = std::pair<uint64_t, uint64_t>;

int main() {
    std::ifstream file("pairs.txt");
    std::string ln;
    uint64_t doubled = 0, overlap = 0;
    while (std::getline(file, ln)) {
        auto m1 = ln.find('-'), m2 = ln.find('-', m1 + 1);
        auto delim = ln.find(',');
        auto elf1 = pair { std::stoll(ln.substr(0, m1)), std::stoll(ln.substr(m1 + 1, delim)) };
        auto elf2 = pair { std::stoll(ln.substr(delim + 1, m2)), std::stoll(ln.substr(m2 + 1)) };
        if ((elf1.first >= elf2.first && elf1.second <= elf2.second) ||
            (elf2.first >= elf1.first && elf2.second <= elf1.second)) {
            ++doubled;
        }
        if ((elf1.first <= elf2.first && elf1.second >= elf2.first) ||
            (elf1.first <= elf2.first && elf1.second >= elf2.second) ||
            (elf2.first <= elf1.first && elf2.second >= elf1.first) ||
            (elf2.first <= elf1.first && elf2.second >= elf1.second))
            ++overlap;
    }
    std::cout << "Part one: " << doubled << std::endl;
    std::cout << "Part two: " << overlap << std::endl;
}
