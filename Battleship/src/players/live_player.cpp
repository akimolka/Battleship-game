#include "live_player.hpp"

LivePlayer::LivePlayer(std::string  name, const Board* board, Interface* interface)
        : Player(board), name(std::move(name)), interface(interface) {}

Coord LivePlayer::get_move() {
    interface->move(name, opponent_board);
    while (true) {
        std::vector<Coord> shot = interface->read();
        if (shot.size() == 1)
            return shot[0];
    }
}


void LivePlayer::report_success(HitResult result) {
    interface->report_success(result);
}


void LivePlayer::report_losses(const Coord& shot, HitResult result, const Board* board) {
    interface->report_losses(name, shot, result, board);
}