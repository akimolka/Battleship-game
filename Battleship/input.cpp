#include "Input.h"

bool ConsoleInput::check_input(const std::string& word) {
    if (word.size() < 2 || word.size() > 3)
        return false;
    if (!('a' <= word[0] && word[0] <= 'j' || 'A' <= word[0] && word[0] <= 'J'))
        return false;
    return (word.size() == 2 && '0' <= word[1] && word[1] <= '9') ||
           (word.size() == 3 && word[1] == '1' && word[2] == '0');
}


std::vector<Coord> ConsoleInput::read() {
    std::string line, word;
    std::getline(std::cin, line);
    std::stringstream ss;
    ss << line;

    std::vector<Coord> ans;
    while (ss >> word) {
        if (!check_input(word)) {
            std::cout << "Incorrect input" << std::endl; // TODO move output out of input
            return {};
        }
        ans.emplace_back(word);
    }
    return std::move(ans);
}

