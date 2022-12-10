#include <array>
#include <iostream>
#include <fstream>
#include <string>

std::array<char, 40 * 6> display = {};

void draw(uint64_t cycles, int64_t reg) {
    auto position = (cycles - 1) % 40;
    if (position == reg - 1 || position == reg || position == reg + 1)
        display[cycles - 1] = '#';
    else
        display[cycles - 1] = '.';
}

int main() {
    std::ifstream file("program.txt");

    int64_t signalStrength = 0;
    std::string ln;
    int64_t regX = 1;
    uint64_t cycles = 0;

    auto isCheckedCycle = [](uint64_t cycles) { return ((int64_t)cycles - 20) % 40 == 0; };
    while (std::getline(file, ln)) {
        if (isCheckedCycle(cycles + 1)) {
            signalStrength += static_cast<int64_t>(cycles + 1) * regX;
        }
        if (ln.starts_with("noop")) {
            ++cycles;
            draw(cycles, regX);
        } else if (ln.starts_with("addx")) {
            draw(cycles + 1, regX);
            draw(cycles + 2, regX);
            cycles += 2;

            if (isCheckedCycle(cycles)) {
                signalStrength += static_cast<int64_t>(cycles) * regX;
            }
            regX += std::stoll(ln.substr(4));
        }
    }
    std::cout << signalStrength << std::endl;
    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 40; ++j)
            std::cout << display[i * 40 + j];
        std::cout << "\n";
    }
    std::cout << std::endl;
}
