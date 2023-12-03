#include <fstream>
#include <iostream>
#include <string>
#include <charconv>
#include <unordered_map>

int main() {
	std::ifstream file("games.txt");

	constexpr auto red = 12, green = 13, blue = 14;

	std::uint64_t gameId = 0;
	std::uint64_t sum = 0, sum2 = 0;
	std::string ln;
	while (std::getline(file, ln)) {
		std::string_view game = std::string_view(ln).substr(ln.find(':') + 2); // Skip the colon and space

		std::unordered_map<std::string, std::size_t> maxValues = {{
			{"blue", 0},
			{"red", 0},
			{"green", 0},
		}};

		bool possible = true;
		std::size_t pos = 0;
		while (pos < game.size()) {
			auto comma = game.find(',', pos);
			auto semic = game.find(';', pos);
			auto delim = comma < semic ? comma : semic;
			auto space = game.find(' ', pos);

			std::size_t count;
			std::from_chars(&game[pos], &game[space], count);

			auto color = std::string(game.substr(space + 1, delim - space - 1));
			if (color == "blue" && count > blue) {
				possible = false;
			} else if (color == "red" && count > red) {
				possible = false;
			} else if (color == "green" && count > green) {
				possible = false;
			}
			if (maxValues[color] < count)
				maxValues[color] = count;

			if (delim == std::string::npos)
				break;
			pos = delim + 2;
		}

		++gameId;
		if (possible) {
			sum += gameId;
		}
		sum2 += maxValues["blue"] * maxValues["red"] * maxValues["green"];
	}
	std::cout << sum << '\n';
	std::cout << sum2;
}
