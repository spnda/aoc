#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

using ll = signed long long;

struct display {
    std::array<std::string, 10> patterns;
    std::array<std::string, 4> out;
};

bool containsChar(const std::string& str, char& c) {
    for (size_t i = 0; i < str.length(); ++i)
        if (str[i] == c)
            return true;
    return false;
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

    for (auto& p : d.patterns) {
        std::cout << p << " ";
    }
    std::cout << std::endl;

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

    for (auto& f : fiveLongValues)
        if (containsChar(f, aM[0]) && containsChar(f, aM[1]) && containsChar(f, aM[3]) && containsChar(f, aM[6]))
            for (auto& c : f)
                if (c != aM[0] && c != aM[1] && c != aM[3] && c != aM[6])
                    aM[5] = c;

    aM[2] = one[(one[0] == aM[5])];

    std::string map = { aM[0], aM[1], aM[2], aM[3], aM[5], aM[6] };
    aM[4] = diff(eight, map).front();

    std::string output = {};
    for (auto& o : d.out) {
        if (o.length() == 2) output.push_back('1');
        else if (o.length() == 3) output.push_back('7');
        else if (o.length() == 4) output.push_back('4');
        else if (o.length() == 7) output.push_back('8');
        else if (o.length() == 5) {
            if (!containsChar(o, aM[1]) && !containsChar(o, aM[4])) output.push_back('3');
            else if (containsChar(o, aM[2])) output.push_back('2');
            else output.push_back('5');
        } else if (o.length() == 6) {
            if (!containsChar(o, aM[3])) output.push_back('0');
            else if (containsChar(o, aM[2])) output.push_back('9');
            else output.push_back('6');
        }
    }
    return std::stoi(output);
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
