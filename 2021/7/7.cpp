#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using ll = signed long long;

int main() {
    std::ifstream f("positions.txt");
    std::vector<ll> nums;
    std::string ln;
    while (std::getline(f, ln, ','))
        nums.emplace_back(std::stoi(ln));

    std::sort(nums.begin(), nums.end());
    size_t s = nums.size() - 1;

    float medianf = (nums.size() % 2 == 0)
        ? ((nums[std::floor(s / 2)] + nums[std::floor(s / 2) + 1]) / 2)
        : nums[std::floor(s / 2)];
    ll median = std::floor(medianf);

    ll fuel = 0, fuel2 = INT64_MAX;
    for (size_t i = 0; i < nums.size(); ++i)
        fuel += std::abs(median - nums[i]);
    for (ll i = nums.front(); i <= nums.back(); ++i) {
        ll fuel2t = 0;
        for (size_t n = 0; n < nums.size(); ++n) {
            ll req = std::abs(i - nums[n]);
            fuel2t += req * (req + 1) / 2;
        }
        fuel2 = std::min(fuel2, fuel2t);
    }
    std::cout << fuel << std::endl << fuel2 << std::endl;
}
