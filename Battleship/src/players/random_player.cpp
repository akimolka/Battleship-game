#include "random_player.hpp"

RandomPlayer::RandomPlayer(const Board* board): Player(board, "AI firing randomly") {
    std::srand(std::time(nullptr));
}

Coord RandomPlayer::get_move() {
    int x = rand() % board_size;
    int y = rand() % board_size;
    return {x, y};
}

void RandomPlayer::report_success(HitResult result) {}
void RandomPlayer::report_losses(const std::vector<std::pair<Coord, HitResult>>& losses, const Board* board) {}
