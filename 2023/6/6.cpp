#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <vector>

std::vector<std::size_t> parse_integer_list(const std::string& ln) {
	std::vector<std::size_t> values;
	std::size_t pos = 0;
	while ((pos = ln.find(' ', pos)) != std::string::npos) {
		std::size_t nextpos = ln.find(' ', pos + 1);
		if (pos + 1 == nextpos) {
			++pos;
			continue;
		}

		auto token = std::string_view(ln).substr(pos+1, nextpos-pos);
		pos = nextpos;

		std::size_t value = 0;
		std::from_chars(token.data(), token.data() + token.size(), value);
		values.emplace_back(value);
	}
	return values;
}

std::size_t count_wins(std::size_t time, std::size_t target_distance) {
	std::size_t wins = 0;
	for (std::size_t n = 1; n < time - 1; ++n) {
		auto distance = n * (time - n);
		if (distance > target_distance)
			++wins;
	}
	return wins;
}

bool constexpr partTwo = true;

int main() {
	std::ifstream file("times.txt");

	if constexpr (partTwo) {
		auto parseValue = [&file]() -> std::size_t {
			std::string ln;
			std::getline(file, ln);
			std::erase_if(ln, [](auto x) { return x == ' '; });
			std::size_t value;
			std::from_chars(&ln[ln.find(':') + 1], ln.data() + ln.size(), value);
			return value;
		};
		std::size_t time = parseValue();
		std::size_t target_distance = parseValue();

		std::cout << count_wins(time, target_distance);
	} else {
		std::string ln;
		std::getline(file, ln);
		std::vector<std::size_t> times = parse_integer_list(ln);
		std::getline(file, ln);
		std::vector<std::size_t> distances = parse_integer_list(ln);

		std::uint64_t total = 1;
		for (std::size_t i = 0; i < times.size(); ++i) {
			total *= count_wins(times[i], distances[i]);
		}
		std::cout << total;
	}

	return 0;
}
