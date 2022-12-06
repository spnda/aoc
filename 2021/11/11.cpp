#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using ll = signed long long;

struct Octopus {
    ll energy = 0, lastFlash = -1;
};

using ovv = std::vector<std::vector<Octopus>>;

ll flashes = 0;

void flash(ovv& in, ll& step, ll x, ll y) {
    if (in[x][y].energy > 9 && in[x][y].lastFlash != step) {
        in[x][y].lastFlash = step;
        ++flashes;

        for (ll x1 = x == 0 ? 0 : x - 1; x1 <= x + 1 && x1 < in.size(); ++x1)
            for (ll y1 = y == 0 ? 0 : y - 1; y1 <= y + 1 && y1 < in[x1].size(); ++y1) {
                if (x1 == x && y1 == y)
                    continue;
                if (++in[x1][y1].energy > 9)
                    flash(in, step, x1, y1);
            }
    }
}

int main() {
    std::ifstream f("octopus.txt");
    ovv octopus;
    for (std::string ln; f >> ln; ) {
        octopus.emplace_back();
        for (auto& c : ln)
            octopus.back().push_back(Octopus {std::stoll(std::string {c}), -1});
    }

    constexpr ll stepCount = 100;
    ll step = 0;
    bool partOne = false, partTwo = false;
    while(true) {
        for (auto& row : octopus)
            for (auto& col : row)
                ++col.energy;

        for (std::size_t x = 0; x < octopus.size(); ++x)
            for (std::size_t y = 0; y < octopus[x].size(); ++y)
                flash(octopus, step, x, y);

        std::size_t flashedCount = 0;
        for (auto& row : octopus)
            for (auto& col : row)
                if (col.lastFlash == step) {
                    col.energy = 0;
                    ++flashedCount;
                }

        ++step;

        // Part One
        if (stepCount - 1 == step) {
            std::cout << "Flashed " << flashes << " times after " << stepCount << " steps." << std::endl;
            partOne = true;
        }

        // Part two
        if (flashedCount == octopus.size() * octopus[0].size()) {
            std::cout << "All flashed simultaneously at step " << step << std::endl;
            partTwo = true;
        }

        if (partOne && partTwo)
            break;
    }
}
