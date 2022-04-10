#include "player.hpp"

bool Player::is_valid(const Coord& coord) {
    return coord.x >= 0 && coord.y >= 0 && coord.x < Board::size && coord.y < Board::size;
}


void Player::mark_uninteresting_rec(const Coord& coord, std::vector<std::vector<bool>>& interesting,
                                    std::vector<std::vector<bool>>& used) {
    used[coord.x][coord.y] = true;
    interesting[coord.x][coord.y] = false;
    for (auto move : neighbour_moves) {
        int x = coord.x + move.first;
        int y = coord.y + move.second;
        if (!is_valid({x, y}))
            continue;
        interesting[x][y] = false;
        if (!used[x][y] && opponent_board->get_board()[x][y] == HitResult::KILL)
            mark_uninteresting_rec({x, y}, interesting, used);
    }
}


void Player::mark_uninteresting(const Coord& coord, std::vector<std::vector<bool>>& interesting) {
    std::vector<std::vector<bool>> used(Board::size, std::vector<bool> (Board::size));
    mark_uninteresting_rec(coord, interesting, used);
}


Player::Player(const Board* board, std::string  name): opponent_board(board), name(std::move(name)) {}