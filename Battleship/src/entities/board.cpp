#include "board.hpp"

bool Board::put_ship_on_board(const Ship& ship, int indx) {
    const std::vector<Coord>& ship_coords = ship.get_coords();
    for (int i = 0; i < ship_coords.size(); i++) {
        Coord coord = ship_coords[i];
        if (indx != -1 && ship_indices[coord.x][coord.y] != -1) { // putting ship above existing ship;
            for (int j = 0; j < i; j++)
                ship_indices[ship_coords[j].x][ship_coords[j].y] = -1;
            return false;
        }
        ship_indices[coord.x][coord.y] = indx;
    }
    return true;
}

void Board::remove_ship_from_board(const Ship& ship) {
    put_ship_on_board(ship, -1);
}

bool Board::is_valid() {
    static std::vector<std::pair<int, int>> moves = {{-1, -1}, {-1, 0}, {-1, 1},
                                                     {0, -1}, {0, 1},
                                                     {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            if (ship_indices[i][j] == -1) continue;
            for (auto& move : moves) {
                int x = i + move.first;
                int y = j + move.second;
                if (x < 0 || y < 0 || x >= size || y >= size)
                    continue;
                if (ship_indices[x][y] != -1 && ship_indices[x][y] != ship_indices[i][j])
                    return false;
            }
        }
    return true;
}

Board::Board(int board_size): size(board_size) {
    board.resize(size, std::vector<HitResult> (size));
    ship_indices.resize(size, std::vector<int> (size, -1));
}

bool Board::add_ships(const Ship& ship) {
    if (!put_ship_on_board(ship, ships.size()))
        return false;
    ships.push_back(ship);
    if (!is_valid()) {
        remove_ship_from_board(ships.back());
        ships.pop_back();
        return false;
    }
    return true;
}

bool Board::add_ships(const std::vector<Ship>& additional) {
    if (additional.empty()) return false;

    for (const Ship& ship : additional)
        if (!add_ships(ship)) return false;
    return true;
}

const std::vector<std::vector<HitResult>>& Board::get_board() const {
    return board;
}

const std::vector<std::vector<int>>& Board::get_ships() const {
    return ship_indices;
}

HitResult Board::hit(const Coord& coord) {
    if (ship_indices[coord.x][coord.y] == -1) {
        board[coord.x][coord.y] = HitResult::MISS;
        return HitResult::MISS;
    }
    board[coord.x][coord.y] = ships[ship_indices[coord.x][coord.y]].hit(coord);
    if (board[coord.x][coord.y] == HitResult::KILL) {
        for (Coord coord : ships[ship_indices[coord.x][coord.y]].get_coords())
            board[coord.x][coord.y] = HitResult::KILL;
    }
    return board[coord.x][coord.y];
}