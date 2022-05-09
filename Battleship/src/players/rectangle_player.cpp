#include "rectangle_player.hpp"

Coord RectanglePlayer::find_interesting(int x, int y) {
    for (int i = x; true; i = (i + 1) % board_size)
        for (int j = y, cnt = 0; cnt < board_size; j = (j + 1) % board_size, cnt++)
            if (interesting[i][j])
                return {i, j};
}


Coord RectanglePlayer::find_another_hit(const Coord& coord) {
    std::vector<std::pair<int, int>> straight_moves =
            {{-1, 0},{0, -1}, {0, 1}, {1, 0}};
    for (auto move : straight_moves) {
        int x = coord.x + move.first;
        int y = coord.y + move.second;
        if (is_valid({x, y}) && opponent_board->get_board()[x][y] == HitResult::HIT)
            return {x, y};
    }
    return {-1, -1};
}


void RectanglePlayer::make_neighbours_potential(const Coord& coord) {
    std::vector<std::pair<int, int>> straight_moves =
            {{-1, 0},{0, -1}, {0, 1}, {1, 0}};
    for (auto move : straight_moves) {
        int x = coord.x + move.first;
        int y = coord.y + move.second;
        if (is_valid({x, y}))
            potential_moves.push({x, y});
    }
}


RectanglePlayer::RectanglePlayer(const Board* board): Player(board, "Adequate AI player") {
    interesting.resize(board_size, std::vector<bool> (board_size, true));
}


Coord RectanglePlayer::get_move() {
    while (!potential_moves.empty()) {
        Coord coord = potential_moves.front();
        if (interesting[coord.x][coord.y])
            return coord;
        potential_moves.pop();
    }

    std::srand(std::time(nullptr));
    int starting_x = rand() % board_size;
    int starting_y = rand() % board_size;
    potential_moves.push(find_interesting(starting_x, starting_y));
    return potential_moves.front();
}


void RectanglePlayer::report_success(HitResult result) {
    Coord curr = potential_moves.front();
    interesting[curr.x][curr.y] = false;

    if (result == HitResult::KILL)
        mark_uninteresting(curr, interesting);
    else if (result == HitResult::HIT) {
        Coord another_hit = find_another_hit(curr);

        if (another_hit.x == -1)
            make_neighbours_potential(curr);
        else {
            Coord potential = {another_hit.x + 2 * (curr.x - another_hit.x), another_hit.y + 2 * (curr.y - another_hit.y)};
            if (is_valid(potential))
                potential_moves.push(potential);
            interesting[another_hit.x + (another_hit.y - curr.y)][another_hit.y + (another_hit.x - curr.x)] = false;
            interesting[another_hit.x - (another_hit.y - curr.y)][another_hit.y - (another_hit.x - curr.x)] = false;
        }
    }

    potential_moves.pop();
}

void RectanglePlayer::report_losses(const std::vector<std::pair<Coord, HitResult>>& losses, const Board* board) {}
