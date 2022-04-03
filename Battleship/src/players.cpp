#include "players.hpp"

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


Player::Player(const Board* board): opponent_board(board) {}


LivePlayer::LivePlayer(std::string  name, const Board* board, Input* input, Output* output)
        : Player(board), name(std::move(name)), input(input), output(output) {}

Coord LivePlayer::get_move() {
    output->move(name, opponent_board);
    while (true) {
        std::vector<Coord> shot = input->read();
        if (shot.size() == 1)
            return shot[0];
    }
}


void LivePlayer::report_success(HitResult result) {
    output->report_success(result);
}


void LivePlayer::report_losses(const Coord& shot, HitResult result, const Board* board) {
    output->report_losses(name, shot, result, board);
}


RandomPlayer::RandomPlayer(const Board* board): Player(board) {}

Coord RandomPlayer::get_move() {
    std::srand(std::time(nullptr));
    int x = rand() % Board::size;
    int y = rand() % Board::size;
    return {x, y};
}

void RandomPlayer::report_success(HitResult result) {}
void RandomPlayer::report_losses(const Coord& shot, HitResult result, const Board* board) {}


Coord DummyRectanglePlayer::find_interesting(int x, int y) {
    for (int i = x; true; i = (i + 1) % Board::size)
        for (int j = y, cnt = 0; cnt < Board::size; j = (j + 1) % Board::size, cnt++)
            if (interesting[i][j])
                return {i, j};
}


Coord DummyRectanglePlayer::find_another_hit(const Coord& coord) {
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


void DummyRectanglePlayer::make_neighbours_potential(const Coord& coord) {
    std::vector<std::pair<int, int>> straight_moves =
            {{-1, 0},{0, -1}, {0, 1}, {1, 0}};
    for (auto move : straight_moves) {
        int x = coord.x + move.first;
        int y = coord.y + move.second;
        if (is_valid({x, y}))
            potential_moves.push({x, y});
    }
}


DummyRectanglePlayer::DummyRectanglePlayer(const Board* board): Player(board) {
    interesting.resize(Board::size, std::vector<bool> (Board::size, true));
}


Coord DummyRectanglePlayer::get_move() {
    while (!potential_moves.empty()) {
        Coord coord = potential_moves.front();
        if (interesting[coord.x][coord.y])
            return coord;
        potential_moves.pop();
    }

    std::srand(std::time(nullptr));
    int starting_x = rand() % Board::size;
    int starting_y = rand() % Board::size;
    potential_moves.push(find_interesting(starting_x, starting_y));
    return potential_moves.front();
}


void DummyRectanglePlayer::report_success(HitResult result) {
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

void DummyRectanglePlayer::report_losses(const Coord& shot, HitResult result, const Board* board) {}
