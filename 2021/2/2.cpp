#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream f("commands.txt");

    long long x, h1, d1, h2, d2, a;
    std::string ln;
    while (f >> ln >> x) {
        auto cmd = ln.substr(0, 1);
             if (cmd == "f") { h1 += x; h2 += x; d2 += a * x; }
        else if (cmd == "d") { d1 += x; a += x; }
        else if (cmd == "u") { d1 -= x; a -= x; }
    }

    std::cout << h1 * d1 << std::endl << h2 * d2 << std::endl;
}
