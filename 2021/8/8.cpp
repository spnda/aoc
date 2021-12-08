#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <span>

using ll = signed long long;

struct display {
    std::array<std::string, 10> patterns;
    std::array<std::string, 4> out;
};

bool containsChar(const std::string& str, char& c) {
    return str.find(c, 0) != std::string::npos;
}

std::string diff(std::string a, std::string& b) {
    std::erase_if(a, [b](char& v) {
        return b.find(v, 0) != std::string::npos;
    });
    return a;
}

ll calcSum(display& d) {
    std::sort(d.patterns.begin(), d.patterns.end(), [](const auto& a, const auto& b) {
        return a.length() < b.length();
    });

    std::array<char, 7> aM = {};
    std::vector<std::string> fiveLongValues = { d.patterns[3], d.patterns[4], d.patterns[5] };
    std::string one = d.patterns[0],
                three,
                four = d.patterns[2],
                seven = d.patterns[1],
                eight = d.patterns[9];

    aM[0] = diff(seven, one).front();

    for (auto& f : fiveLongValues) {
        auto dif = diff(f, one);
        if (dif.length() == 3)
            three = f;
    }

    for (auto& c : four)
        if (containsChar(three, c) && !containsChar(one, c)) {
            aM[3] = c;
        } else if (!containsChar(three, c) && !containsChar(one, c)) {
            aM[1] = c;
        }

    for (auto& f : fiveLongValues)
        if (containsChar(f, aM[0]) && containsChar(f, aM[1]) && containsChar(f, aM[3]))
            for (auto& c : f)
                if (!containsChar(one, c) && c != aM[0] && c != aM[1] && c != aM[3])
                    aM[6] = c;

    for (auto& f : fiveLongValues) {
        std::string m = { aM[0], aM[1], aM[3], aM[6] };
        auto dif = diff(f, m);
        if (dif.length() == 1)
            aM[5] = dif.front();
    }

    aM[2] = one[(one[0] == aM[5])];

    auto map = std::string { aM[0], aM[1], aM[2], aM[3], aM[5], aM[6] };
    aM[4] = diff(eight, map).front();

    std::array<std::string, 10> digits = { "abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg" };
    ll out = 0;
    for (auto& o : d.out) {
        for (auto& c : o)
            c = (std::find(aM.begin(), aM.end(), c) - aM.begin()) + 'a';
        std::sort(o.begin(), o.end());
        out = (out * 10) + (std::find(digits.begin(), digits.end(), o) - digits.begin());
    }
    return out;
}

int main() {
    std::ifstream f("displays.txt");
    std::string ln, del;
    display d;
    ll sumUniqueNums = 0, totalSum = 0;
    while (std::getline(f, ln)) {
        std::stringstream ss { ln };
        d = {};
        for (size_t i = 0; i < 10; ++i)
            ss >> d.patterns[i];
        ss >> del;    
        for (size_t j = 0; j < 4; ++j) {
            ss >> d.out[j];
            sumUniqueNums += (d.out[j].length() - 2 <= 2) || (d.out[j].length() == 7);
        }
        totalSum += calcSum(d);
    }
    std::cout << sumUniqueNums << std::endl;
    std::cout << totalSum << std::endl;
}
