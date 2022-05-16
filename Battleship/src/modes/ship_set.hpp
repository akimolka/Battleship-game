#ifndef BATTLESHIP_SHIP_SET_HPP
#define BATTLESHIP_SHIP_SET_HPP

#include <vector>
#include "ship_figures.hpp"

enum class ShipSetName {STANDART, TRIANGLE, FUNNY};

class ShipSet {
    std::vector<const Figure*> ships;
    void build_standard_shipset(int board_size);
    void build_triangle_shipset(int board_size);
    void build_funny_shipset(int board_size);
public:
    void build(ShipSetName ship_set, int board_size);
    std::vector<const Figure*> get() const;
};

#endif //BATTLESHIP_SHIP_SET_HPP
