#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using ll = signed long long;
using point = std::pair<ll, ll>;

struct line {
    ll x1, y1, x2, y2;
};

bool isPointOnLine(const line& l, ll x, ll y) {
    return x >= std::min(l.x1, l.x2)
        && x <= std::max(l.x1, l.x2)
        && y >= std::min(l.y1, l.y2)
        && y <= std::max(l.y1, l.y2)
        && (l.x1 == l.x2 || l.y1 == l.y2 || std::abs(x - l.x1) == std::abs(y - l.y1));
}

void overlaps(std::set<point>& points, const line& l1, const line& l2) {
    ll dx = l1.x2 - l1.x1;
    ll dy = l1.y2 - l1.y1;
    if (dx != 0) dx /= std::abs(dx);
    if (dy != 0) dy /= std::abs(dy);
    for (ll x = l1.x1, y = l1.y1; ; x += dx, y += dy) {
        if (isPointOnLine(l2, x, y))
            points.emplace(x, y);
        if (x == l1.x2 && y == l1.y2) break;
    }
}

int main() {
    std::ifstream f("vents.txt");
    std::string ln;
    line l;
    std::vector<line> lines;

    while (f >> ln) {
        l.x1 = std::stoi(ln.substr(0, ln.find(",")));
        l.y1 = std::stoi(ln.substr(ln.find(",") + 1));
        f >> ln >> ln;
        l.x2 = std::stoi(ln.substr(0, ln.find(",")));
        l.y2 = std::stoi(ln.substr(ln.find(",") + 1));
        lines.push_back(l);
    }

    std::set<point> points2, points1;
    for (const auto& l1 : lines)
        for (const auto& l2 : lines)
            if (&l1 != &l2) {
                overlaps(points2, l1, l2);
                if ((l1.x1 == l1.x2 || l1.y1 == l1.y2) && (l2.x1 == l2.x2 || l2.y1 == l2.y2))
                    overlaps(points1, l1, l2);
            }

    std::cout << points1.size() << std::endl;
    std::cout << points2.size() << std::endl;
}
