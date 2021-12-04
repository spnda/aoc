#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using ll = signed long long;
using board = std::array<std::array<ll, 5>, 5>;

struct winc {
    ll sum = -1, winNum = -1, index = -1;
    bool operator <(const winc& other) const { return index < other.index; };
};

std::vector<int> nums = {};
std::vector<board> boards = {};
std::vector<winc> wins = {};

auto checkWin(board& board, size_t i, size_t j, bool vert) -> ll {
    for (int xy = 0; xy < 5; ++xy) {
        if ((vert ? board[i][xy] : board[xy][j]) >= 0)
            return 0;
    }

    ll sum = 0;
    for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
            sum += (board[x][y] >= 0) * board[x][y];
    return sum;
}

auto bingo(board& b, ll n) -> void {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (b[i][j] == nums[n])
                b[i][j] = -1;

            auto sum = checkWin(b, i, j, true);
            if (!sum) sum = checkWin(b, i, j, false);
            if (sum) {
                wins.back() = { sum, nums[n], n };
                return;
            }
        }
    }
};

int main() {
    std::ifstream f("boards.txt");

    std::string ln;
    f >> ln;
    std::stringstream ss {ln};
    while (std::getline(ss, ln, ','))
        nums.push_back(std::stoi(ln));

    while (std::getline(f, ln)) {
        boards.push_back({});
        wins.push_back({});
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                f >> ln;
                boards.back()[i][j] = std::stoi(ln);
            }
        }

        for (size_t i = 0; i < nums.size(); ++i)
            if (wins.back().index == -1)
                bingo(boards.back(), i);
    }

    std::sort(wins.begin(), wins.end());
    std::cout << "Part one: " << wins.front().sum * wins.front().winNum << std::endl;
    std::cout << "Part two: " << wins.back().sum * wins.back().winNum << std::endl;
}
