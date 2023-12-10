#include <string>
#include <fstream>
#include <iostream>

struct vec {
	std::size_t x, y;
	vec(std::size_t x, std::size_t y) : x(x), y(y) {}
	bool operator==(vec other) const noexcept {
		return x == other.x && y == other.y;
	}
};

std::size_t follow_pipes(std::string& field, std::size_t line_size, vec start, vec current) {
	vec last = start;
	vec pos = current;
	std::size_t steps = 0;
	while (pos != start) {
		char value = field[pos.y * line_size + pos.x];
		vec cur_pos = pos;
		switch (value) {
			case '|':
				pos.y = last.y > pos.y ? pos.y - 1 : pos.y + 1;
				break;
			case '-':
				pos.x = last.x > pos.x ? pos.x - 1 : pos.x + 1;
				break;
			case 'L':
				if (last.y < pos.y)
					++pos.x;
				else
					--pos.y;
				break;
			case 'J':
				if (last.y < pos.y)
					--pos.x;
				else
					--pos.y;
				break;
			case '7':
				if (last.y > pos.y)
					--pos.x;
				else
					++pos.y;
				break;
			case 'F':
				if (last.y > pos.y)
					++pos.x;
				else
					++pos.y;
				break;
			case '.':
				return 0; // Only happens when we directly land on a ground tile
		}
		last = cur_pos;
		++steps;
	}
	return steps;
}

int main() {
	std::ifstream file("pipes.txt");

	std::size_t line_count = 0, line_size = 0;
	vec starting_pos(0,0);
	std::string pipes;
	{
		std::string ln;
		while (std::getline(file, ln)) {
			pipes += ln;
			if (auto spos = ln.find('S'); spos != std::string::npos) {
				starting_pos.x = spos;
				starting_pos.y = line_count;
			}
			++line_count;
			line_size = ln.size();
		}
	}

	auto length1 = follow_pipes(pipes, line_size, starting_pos, vec(starting_pos.x + 1, starting_pos.y));
	auto length2 = follow_pipes(pipes, line_size, starting_pos, vec(starting_pos.x,     starting_pos.y + 1));
	auto length3 = follow_pipes(pipes, line_size, starting_pos, vec(starting_pos.x - 1, starting_pos.y));
	auto length4 = follow_pipes(pipes, line_size, starting_pos, vec(starting_pos.x,     starting_pos.y - 1));
	auto max = std::max({length1, length2, length3, length4});
	std::cout << (max+1) / 2 << '\n';
}
