#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum Choice {
    Rock = 1, Paper = 2, Scissors = 3,
};
enum Outcome {
    Lose = 1, Draw = 2, Win = 3,
};

uint64_t score(Choice choice, Choice opponent) {
    bool draw = choice == opponent;
    bool won = (choice == Rock && opponent == Scissors) ||
               (choice == Scissors && opponent == Paper) ||
               (choice == Paper && opponent == Rock);
    return (won ? 6 : 0) + (draw ? 3 : 0) + choice;
}

int main() {
    std::ifstream file("strategy.txt");
    std::string ln;
    uint64_t score1 = 0;
    uint64_t score2 = 0;
    while (std::getline(file, ln)) {
        auto opponent = (Choice)(ln[0] - 'A' + 1);
        score1 += score((Choice)(ln[2] - 'X' + 1), opponent);

        auto outcome = (Outcome)(ln[2] - 'X' + 1);
        Choice choice;
        if (outcome == Win) {
            choice = (opponent == Scissors) ? Rock : (Choice)(opponent + 1);
        } else if (outcome == Lose) {
            choice = (opponent == Rock) ? Scissors : (Choice)(opponent - 1);
        } else if (outcome == Draw) {
            choice = opponent;
        }
        score2 += score(choice, opponent);
    }
    std::cout << "Part one: " << score1 << std::endl;
    std::cout << "Part one: " << score2 << std::endl;
}
