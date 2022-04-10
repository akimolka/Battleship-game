#ifndef BATTLESHIP_LIVE_PLAYER_HPP
#define BATTLESHIP_LIVE_PLAYER_HPP

#include "player.hpp"

class LivePlayer: public Player {
    Interface* interface;
public:
    LivePlayer(const std::string& name, const Board* board, Interface* interface);
    Coord get_move() override;
    void report_success(HitResult result) override;
    void report_losses(const std::vector<std::pair<Coord, HitResult>>& losses, const Board* board) override;
};

#endif //BATTLESHIP_LIVE_PLAYER_HPP
