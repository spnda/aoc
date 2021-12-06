#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using ll = signed long long;

struct fi {
    ll v = 0, c = 1;
    fi() = default;
    fi(ll v) : v(v) {};
    fi(ll v, ll c) : v(v), c(c) {};
};

size_t s = 0;
std::vector<fi> fish = {};

int main() {
    std::string ln;
    std::ifstream f("fish.txt");
    while (std::getline(f, ln, ','))
        fish.emplace_back(std::stoi(ln));

    s = fish.size();
    for (size_t i = 0; i < 256; ++i) {
        s = fish.size();
        ll newEights = 0;
        for (size_t j = 0; j < s; ++j) {
            if (fish[j].v == 0) {
                fish[j].v = 6;
                newEights += fish[j].c;
            } else {
                --fish[j].v;
            }
        }
        fish.emplace_back(8, newEights);
    }

    size_t count = 0;
    for (size_t i = 0; i < fish.size(); ++i)
        count += fish[i].c;
    std::cout << count << std::endl;
}
