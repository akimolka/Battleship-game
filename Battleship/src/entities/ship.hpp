#ifndef BATTLESHIP_SHIP_HPP
#define BATTLESHIP_SHIP_HPP

#include "coord.hpp"
#include <vector>

enum class HitResult { NONE, MISS, HIT, KILL };

class Ship {
    std::vector<Coord> body;
    std::vector<HitResult> state;
public:
    Ship(std::vector<Coord> coords);
    Ship(const Coord& corner1, const Coord& corner2);
    HitResult hit(const Coord& coord);
    const std::vector<Coord>& get_coords() const;
};

#endif //BATTLESHIP_SHIP_HPP
