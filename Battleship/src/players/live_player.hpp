#ifndef BATTLESHIP_LIVE_PLAYER_HPP
#define BATTLESHIP_LIVE_PLAYER_HPP

#include "player.hpp"

class LivePlayer: public Player {
    const std::string name;
    Interface* interface;
public:
    LivePlayer(std::string  name, const Board* board, Interface* interface);
    Coord get_move() override;
    void report_success(HitResult result) override;
    void report_losses(const Coord& shot, HitResult result, const Board* board) override;
};

#endif //BATTLESHIP_LIVE_PLAYER_HPP
