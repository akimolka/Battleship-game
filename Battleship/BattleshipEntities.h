#ifndef BATTLESHIP_BATTLESHIPENTITIES_H
#define BATTLESHIP_BATTLESHIPENTITIES_H

#include <utility>
#include <vector>
#include <string>
#include <algorithm>

struct Coord {
    int x;
    int y;
    explicit Coord(const std::string& str);
    Coord(int x, int y);
    Coord();
    bool operator==(const Coord& other) const;
    bool operator<(const Coord& other) const;
};

enum class HitResult { NONE, MISS, HIT, KILL };

class Ship {
    std::vector<Coord> body;
    std::vector<HitResult> state;
public:
    Ship(std::vector<Coord> coords);
    Ship(const Coord& corner1, const Coord& corner2);
    HitResult hit(const Coord& coord);
    const std::vector<Coord>& get_coords() const;
};

class Board;

struct Cell {
    HitResult state;
    Cell();
};

class Board {
    std::vector<Ship> ships;

    std::vector<std::vector<Cell>> board;
    std::vector<std::vector<int>> ship_indices;

    bool put_ship_on_board(const Ship& ship, int indx);
    void remove_ship_from_board(const Ship& ship);
    bool is_valid();

public:
    static const int size = 10;
    Board();

    bool add_ships(const Ship& ship);
    bool add_ships(const std::vector<Ship>& additional);
    HitResult hit(const Coord& coord);
    const std::vector<std::vector<Cell>>& get_board() const;
    const std::vector<std::vector<int>>& get_ships() const;
};

class Figure {
    std::vector<Coord> body;
    static void rotate(std::vector<Coord>& lst);
    static void shift_to(std::vector<Coord>& lst, const Coord& destination);
    static void reflect(std::vector<Coord>& lst);

public:
    Figure(std::vector<Coord> coords);
    Figure(const Coord& corner1, const Coord& corner2);
    const std::vector<Coord>& get_coords() const;
    bool operator==(const Figure& other) const;
};

#endif //BATTLESHIP_BATTLESHIPENTITIES_H

