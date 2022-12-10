#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using vec = std::pair<int64_t, int64_t>;

auto distance(vec head, vec tail) {
    auto a = std::pow((double)(head.first) - (double)(tail.first), 2);
    auto b = std::pow((double)(head.second) - (double)(tail.second), 2);
    return (decltype(head.first))std::floor(std::sqrt(a + b));
}

namespace std {
    template<>
    struct hash<vec> {
        std::size_t operator()(const vec& k) const {
            auto a = hash<decltype(k.first)>()(k.first);
            return a ^ (hash<decltype(k.second)>()(k.second) + 0x9e3779b9 + (a << 6) + (a >> 2));
        }
    };
}

int main() {
    std::ifstream file("ropes.txt");

    constexpr bool partTwo = true;
    std::array<vec, partTwo ? 10 : 2> knots = {};
    std::string ln;
    std::unordered_set<vec> positions = {};
    positions.emplace(0, 0); // Start
    while (std::getline(file, ln)) {
        auto value = static_cast<decltype(vec::first)>(std::stoi(ln.substr(2)));
        while (value--) {
            switch (ln[0]) {
                case 'R': ++knots.begin()->first; break;
                case 'L': --knots.begin()->first; break;
                case 'U': ++knots.begin()->second; break;
                case 'D': --knots.begin()->second; break;
            }

            for (size_t i = 1; i < knots.size(); ++i) {
                auto& head = knots[i - 1];
                auto& tail = knots[i];

                auto dist = distance(head, tail);
                if (dist <= 1)
                    continue;
                if (head.first == tail.first) {
                    tail.second += (head.second > tail.second) ? 1 : (-1);
                }
                if (head.second == tail.second) {
                    tail.first += (head.first > tail.first) ? 1 : (-1);
                }
                if (head.first != tail.first && head.second != tail.second) {
                    tail.first += (head.first > tail.first) ? 1 : (-1);
                    tail.second += (head.second > tail.second) ? 1 : (-1);
                }
                if (i == knots.size() - 1)
                    positions.emplace(tail);
            }
        }
    }

    std::cout << positions.size() << std::endl;
}
