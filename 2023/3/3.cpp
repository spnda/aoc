#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <charconv>
#include <unordered_set>

using number = std::tuple<std::size_t, std::size_t, std::size_t>;

int main() {
	std::ifstream file("engine.txt");

	std::vector<number> numbers;
	std::vector<std::tuple<std::size_t, char>> symbols;

	std::uint64_t lineSize = 0, lineCount = 0;
	{
		std::string ln;
		std::uint64_t pos = 0;
		while (std::getline(file, ln)) {
			for (std::size_t i = 0; i < ln.size(); ++i) {
				if (std::isdigit(ln[i])) {
					std::size_t j = i;
					while (j < ln.size()) {
						if (std::isdigit(ln[j])) {
							++j;
						} else {
							break;
						}
					}

					std::size_t value = 0;
					std::from_chars(&ln[i], &ln[j], value);

					numbers.emplace_back(pos + i, j - i, value);
					i = j - 1;
				} else if (ln[i] != '.') {
					symbols.emplace_back(pos + i, ln[i]);
				}
			}
			pos += ln.size();
			lineSize = ln.size();
			++lineCount;
		}
	}

	std::uint64_t sum = 0;
	auto check = [&symbols, lineSize, lineCount](std::size_t pos, std::size_t len) -> bool {
		return std::ranges::any_of(symbols.begin(), symbols.end(), [pos, len, lineSize, lineCount](auto& sym) -> bool {
			auto& [symbol, _] = sym;
			if (symbol == pos-1 || symbol == pos+len) {
				return true;
			}
			auto begin = pos % lineSize;
			auto ln = std::size_t(pos / lineSize);
			for (std::size_t i = begin == 0ULL ? begin : begin - 1; i < std::min(begin + len + 1, lineSize); ++i) {
				if (ln != 0 && symbol == (ln - 1) * lineSize + i)
					return true;
				if (ln != lineCount - 1 && symbol == (ln + 1) * lineSize + i)
					return true;
			}
			return false;
		});
	};

	for (auto&& [pos, len, val] : numbers)
		if (check(pos, len))
			sum += val;
	std::cout << sum;

	return 0;
}
