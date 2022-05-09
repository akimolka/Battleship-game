#ifndef BATTLESHIP_BOARD_GENERATOR_HPP
#define BATTLESHIP_BOARD_GENERATOR_HPP

#include "modes/ship_set.hpp"

class BoardGenerator {
public:
    virtual Board* get(const ShipSet* shipset, int board_size) const = 0;
    virtual ~BoardGenerator() = default;
};

#endif //BATTLESHIP_BOARD_GENERATOR_HPP
