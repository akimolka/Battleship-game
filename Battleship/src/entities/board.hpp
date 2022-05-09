#ifndef BATTLESHIP_BOARD_HPP
#define BATTLESHIP_BOARD_HPP

#include "coord.hpp"
#include "ship.hpp"
#include <vector>

class Board {
    std::vector<Ship> ships;

    std::vector<std::vector<HitResult>> board;
    std::vector<std::vector<int>> ship_indices;

    bool put_ship_on_board(const Ship& ship, int indx);
    void remove_ship_from_board(const Ship& ship);
    bool is_valid();

public:
    const int size = 10;
    Board(int board_size);

    bool add_ships(const Ship& ship);
    bool add_ships(const std::vector<Ship>& additional);
    HitResult hit(const Coord& coord);
    const std::vector<std::vector<HitResult>>& get_board() const;
    const std::vector<std::vector<int>>& get_ships() const;
};

#endif //BATTLESHIP_BOARD_HPP
