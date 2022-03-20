#ifndef BATTLESHIP_INPUT_H
#define BATTLESHIP_INPUT_H

#include <sstream>
#include "Entities.h"

class Input {
public:
    virtual std::vector<Coord> read() = 0;
};

class ConsoleInput: public Input {
    static bool check_input(const std::string& word);

public:
    std::vector<Coord> read() override;
};


#endif //BATTLESHIP_INPUT_H
