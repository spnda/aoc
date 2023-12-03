#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <optional>

constexpr bool partTwo = true;

static std::unordered_map<std::string_view, std::size_t> values = {{
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9}
}};

int main() {
	std::ifstream file("calibration.txt");

	std::uint64_t sum = 0;
	std::string ln;
	while (std::getline(file, ln)) {
		if constexpr (partTwo) {
			std::optional<std::uint64_t> first, last;
			for (std::size_t i = 0; i < ln.size(); ++i) {
				if (!first.has_value() && std::isdigit(ln[i]))
					first = ln[i] - '0';
				if (!last.has_value() && std::isdigit(ln[ln.size() - i - 1]))
					last = ln[ln.size() - i - 1] - '0';
				for (std::size_t j = i + 1; j < ln.size(); ++j) {
					if (!first.has_value()) {
						auto substr = std::string_view(ln).substr(i, j - i);
						if (values.contains(substr))
							first = values[substr];
					}
					if (!last.has_value()) {
						auto substr = std::string_view(ln).substr(ln.size() - j, j - i);
						if (values.contains(substr))
							last = values[substr];
					}
				}
				if (first.has_value() && last.has_value())
					break;
			}
			sum += *first * 10 + *last;
		} else {
			auto first = std::find_if(ln.begin(), ln.end(), std::isdigit);
			auto last = std::find_if(ln.rbegin(), ln.rend(), std::isdigit);
			sum += (*first - '0') * 10 + (*last - '0');
		}
	}
	std::cout << sum;

	return 0;
}
