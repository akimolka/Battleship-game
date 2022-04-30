#ifndef BATTLESHIP_RECTANGLE_PLAYER_HPP
#define BATTLESHIP_RECTANGLE_PLAYER_HPP

#include "player.hpp"
#include <ctime>
#include <cstdlib>
#include <queue>

class RectanglePlayer: public Player {
    std::vector<std::vector<bool>> interesting;
    std::queue<Coord> potential_moves;

    Coord find_interesting(int x, int y);
    Coord find_another_hit(const Coord& coord);
    void make_neighbours_potential(const Coord& coord);

public:
    RectanglePlayer(const Board* board);

    Coord get_move() override;
    void report_success(HitResult result) override;
    void report_losses(const std::vector<std::pair<Coord, HitResult>>& losses, const Board* board) override;
};

#endif //BATTLESHIP_RECTANGLE_PLAYER_HPP
