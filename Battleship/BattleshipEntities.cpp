#include "BattleshipEntities.h"

Coord::Coord(const std::string& str) {
    if ('A' <= str[0] && str[0] <= 'J') // todo deal with invalid input
        x = str[0] - 'A';
    else
        x = str[0] - 'a';

    if (str.size() == 3)
        y = 9;
    else
        y = str[1] - '1';
}

Coord::Coord(int x, int y): x(x), y(y) {};

Coord::Coord(): x(-1), y(-1) {};
bool Coord::operator==(const Coord& other) const {
    return x == other.x && y == other.y;
}

bool Coord::operator<(const Coord &other) const {
    if (x != other.x)
        return x < other.x;
    return y < other.y;
}

std::ostream& operator<<(std::ostream& out, const Coord& coord) {
    out << char('A' + coord.x) << coord.y + 1;
    return out;
}


Ship::Ship(std::vector<Coord> coords)
    : body(std::move(coords)), state(std::vector<HitResult> (body.size(), HitResult::NONE)) {};

Ship::Ship(const Coord& corner1, const Coord& corner2) { // upper-left and bottom-right
    for (int x = corner1.x; x <= corner2.x; x++)
        for (int y = corner1.y; y <= corner2.y; y++)
            body.emplace_back(x, y);
    state.resize(body.size(), HitResult::NONE);
}

HitResult Ship::hit(const Coord& coord) {
    HitResult result = HitResult::NONE;
    int pos = 0;
    for (; pos < body.size(); pos++)
        if (body[pos] == coord) break;
    if (state[pos] == HitResult::NONE) {
        state[pos] = HitResult::HIT;
        result = HitResult::HIT;
    }
    bool killed = true;
    for (HitResult cell_state : state)
        if (cell_state == HitResult::NONE) {
            killed = false;
            break;
        }
    if (killed) {
        result = HitResult::KILL;
        state.assign(body.size(), HitResult::KILL);
    }
    return result;
}

const std::vector<Coord>& Ship::get_coords() const {
    return body;
}




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

Board::Board() {
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


void Figure::rotate() {
    Coord head = body[0];
    for (int i = 1; i < body.size(); i++) {
        int delta_x = body[i].x - head.x;
        int delta_y = body[i].y - head.y;
        delta_y *= -1;
        body[i] = {head.x + delta_y, head.y + delta_x};
    }
}

void Figure::shift_to(const Coord& destination) {
    int delta_x = destination.x - body[0].x;
    int delta_y = destination.y - body[0].y;
    for (Coord& coord : body) {
        coord.x += delta_x;
        coord.y += delta_y;
    }
}

void Figure::reflect() {
    Coord head = body[0];
    for (Coord& coord : body) {
        coord.x += 2 * (body[0].x - coord.x);
    }
}

Figure::Figure(std::vector<Coord> coords): body(std::move(coords)) {};

Figure::Figure(const Coord& corner1, const Coord& corner2) { // upper-left and bottom-right
    for (int x = corner1.x; x <= corner2.x; x++)
        for (int y = corner1.y; y <= corner2.y; y++)
            body.emplace_back(x, y);
}

const std::vector<Coord>& Figure::get_coords() const {
    return body;
}

bool Figure::operator==(Figure other) const {
    if (body.size() != other.body.size())
        return false;

    std::vector<Coord> first = body;
    std::sort(first.begin(), first.end());

    for (int turn = 0; turn < 8; turn++) {
        if (turn == 4)
            other.reflect();
        std::sort(other.body.begin(), other.body.end());
        other.shift_to(first[0]);
        if (first == other.body) return true;
        other.rotate();
    }
    return false;
}

//Figure::operator std::vector<Coord> () {
//    return body;
//}
