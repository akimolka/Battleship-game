#ifndef BATTLESHIP_INPUT_HPP
#define BATTLESHIP_INPUT_HPP

#include <sstream>
#include "entities.hpp"

class Input {
public:
    virtual std::vector<Coord> read() = 0;
};

class ConsoleInput: public Input {
    static bool check_input(const std::string& word);

public:
    std::vector<Coord> read() override;
};


#endif //BATTLESHIP_INPUT_HPP
