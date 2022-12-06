#include <array>
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    constexpr bool partTwo = true;
    constexpr size_t markerSize = partTwo ? 14 : 4;

    std::ifstream file("buffer.txt");
    std::array<char, markerSize> marker = {0, 0, 0, 0};
    char x;
    size_t offset = 0;
    while (file >> x) {
        ++offset;

        std::rotate(marker.begin(), marker.begin() + 1, marker.end());
        marker.back() = x;

        // Not enough chars to build a marker
        if (offset < 4)
            continue;

        // Check if any character is doubled
        bool doubled = false;
        for (size_t i = 0; i < markerSize; ++i) {
            for (size_t j = 0; j < markerSize; ++j) {
                if (i == j)
                    continue;
                if (marker[i] == marker[j]) {
                    doubled = true;
                    break;
                }
            }
            if (doubled)
                break;
        }
        if (!doubled)
            break;
    }

    std::cout << offset << std::endl;
}
