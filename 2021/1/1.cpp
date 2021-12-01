#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::fstream f("sea_depth.txt");
    std::vector<int> values;
    std::string str;
    long long j = 0, k = 0, last = 0;
    while (std::getline(f, str)) {
        values.push_back(std::stoi(str));
        if (values.size() == 1 && values[values.size() - 2] < values[values.size() - 1])
            ++j;

        if (values.size() <= 3) continue;
        if (values.size() == 3)
            last = values[0] + values[1] + values[2];
        int l = values.size() - 1;
        long long sum = values[l - 2] + values[l - 1] + values[l];
        if (sum > last)
            ++k;
        last = sum;
    }

    std::cout << j << std::endl;
    std::cout << k << std::endl;
}
