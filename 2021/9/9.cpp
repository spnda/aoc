#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using ll = signed long long;
using llv = std::vector<ll>;
using llvv = std::vector<llv>;
using point = std::pair<ll, ll>;
using pset = std::set<point>;

std::vector<point> adjacentPoints(llvv& in, ll x, ll y) {
    std::vector<point> pts = { {x - 1, y}, {x, y - 1}, {x + 1, y}, {x, y + 1} };
    std::erase_if(pts, [in, x](point& p) {
        return p.first < 0 || p.second < 0 || p.first > (in.size() - 1) || p.second > (in[x].size() - 1);
    });
    return pts;
}

bool isLow(llvv& in, const std::vector<point>& pts, ll v) {
    return pts.end() == std::find_if(pts.begin(), pts.end(), [in, v](const point& p) {
        return in[p.first][p.second] <= v;
    });
}

void basinSize(llvv& in, pset& tset, ll x, ll y) {
    auto ret = adjacentPoints(in, x, y);
    std::erase_if(ret, [in, tset](point& p) {
        return tset.find(p) != tset.end() || in[p.first][p.second] == 9;
    });

    for (auto& v : ret) {
        tset.insert(v);
        basinSize(in, tset, v.first, v.second);
    }
}

int main() {
    std::ifstream f("vents.txt");
    llvv heightmap;
    for (std::string ln; f >> ln;) {
        heightmap.push_back({});
        for (auto& c : ln)
            heightmap.back().push_back(c - '0');
    }

    ll sum = 0;
    llv sizes = {};
    pset tset;
    for (ll x = 0; x < heightmap.size(); ++x) {
        for (ll y = 0; y < heightmap[x].size(); ++y) {
            if (isLow(heightmap, adjacentPoints(heightmap, x, y), heightmap[x][y])) {
                sum += 1 + heightmap[x][y];
                tset.clear();
                basinSize(heightmap, tset, x, y);
                sizes.push_back(tset.size());
            }
        }
    }

    std::sort(sizes.begin(), sizes.end(), std::greater {});
    std::cout << sum << std::endl << sizes[0] * sizes[1] * sizes[2] << std::endl;
}
