#include "live_player.hpp"

LivePlayer::LivePlayer(const std::string& name, const Board* board, Interface* interface)
        : Player(board, name), interface(interface) {}


Coord LivePlayer::get_move() {
    interface->move(name, opponent_board);
    while (true) {
        std::vector<Coord> shot = interface->read(board_size);
        if (shot.size() == 1)
            return shot[0];
    }
}


void LivePlayer::report_success(HitResult result) {
    interface->report_success(result);
}


void LivePlayer::report_losses(const std::vector<std::pair<Coord, HitResult>>& losses, const Board* board) {
    interface->report_losses(name, losses, board);
}