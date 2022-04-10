#ifndef BATTLESHIP_BOARD_GENERATOR_HPP
#define BATTLESHIP_BOARD_GENERATOR_HPP

#include "modes/ship_sets.hpp"

class BoardGenerator {
protected:
    static const int size = 10;
public:
    virtual Board* get(const ShipSet* shipset) const = 0;
    virtual ~BoardGenerator() = default;
};

#endif //BATTLESHIP_BOARD_GENERATOR_HPP
