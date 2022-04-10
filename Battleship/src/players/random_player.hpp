#ifndef BATTLESHIP_RANDOM_PLAYER_HPP
#define BATTLESHIP_RANDOM_PLAYER_HPP

#include "player.hpp"
#include <ctime>
#include <cstdlib>

class RandomPlayer: public Player {
public:
    explicit RandomPlayer(const Board* board);
    Coord get_move() override;
    void report_success(HitResult result) override;
    void report_losses(const std::vector<std::pair<Coord, HitResult>>& losses, const Board* board) override;
};

#endif //BATTLESHIP_RANDOM_PLAYER_HPP
