#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Monkey {
    std::vector<uint64_t> items;
    std::string operation;
    size_t testDivisible;
    size_t monkeyTrue;
    size_t monkeyFalse;
    uint64_t inspections;
};

constexpr bool partTwo = true;

int main() {
    std::ifstream file("monkeys.txt");
    std::vector<Monkey> monkeys = {};
    std::string ln;
    while (std::getline(file, ln)) {
        if (ln.empty() || !ln.starts_with("Monkey"))
            continue;

        auto& monkey = monkeys.emplace_back();
        {
            // Parse item worry levels
            std::getline(file, ln);
            size_t idx = ln.find(':'), idx2 = 0;
            while ((idx2 = ln.find(',', idx + 1)) != -1) {
                monkey.items.emplace_back(std::stoll(ln.substr(idx + 1, idx2)));
                idx = idx2;
            }
            monkey.items.emplace_back(std::stoll(ln.substr(idx + 1)));
        }
        {
            std::getline(file, ln);
            monkey.operation = std::move(ln.substr(19));
            std::getline(file, ln);
            monkey.testDivisible = std::stoll(ln.substr(21));
        }
        {
            std::getline(file, ln);
            monkey.monkeyTrue = std::stoll(ln.substr(28));
            std::getline(file, ln);
            monkey.monkeyFalse = std::stoll(ln.substr(29));
        }
    }

    size_t lcm = 1;
    if constexpr (partTwo) {
        for (const auto& monkey: monkeys) {
            lcm *= monkey.testDivisible;
        }
    }

    constexpr size_t rounds = partTwo ? 10'000 : 20;
    for (size_t r = 0; r < rounds; ++r) {
        for (auto& monkey : monkeys) {
            for (auto& item : monkey.items) {
                if (auto idx = monkey.operation.find('*'); idx != -1) {
                    auto left = monkey.operation.substr(0, idx - 1);
                    auto right = monkey.operation.substr(idx + 2);
                    item = ((left == "old") ? item : std::stoll(left)) * ((right == "old") ? item : std::stoll(right));
                } else if (idx = monkey.operation.find('+'); idx != -1) {
                    auto left = monkey.operation.substr(0, idx - 1);
                    auto right = monkey.operation.substr(idx + 2);
                    item = ((left == "old") ? item : std::stoll(left)) + ((right == "old") ? item : std::stoll(right));
                }

                item = (item / (partTwo ? 1 : 3)) % lcm;
                if (item % monkey.testDivisible == 0) {
                    monkeys[monkey.monkeyTrue].items.emplace_back(item);
                } else {
                    monkeys[monkey.monkeyFalse].items.emplace_back(item);
                }
                ++monkey.inspections;
            }
            monkey.items.clear();
        }
    }

    std::sort(monkeys.begin(), monkeys.end(), [](Monkey& a, Monkey& b) { return a.inspections < b.inspections; });
    std::cout << monkeys[monkeys.size() - 1].inspections * monkeys[monkeys.size() - 2].inspections << std::endl;
}
