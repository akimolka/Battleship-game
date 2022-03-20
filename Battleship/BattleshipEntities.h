#ifndef BATTLESHIP_BATTLESHIPENTITIES_H
#define BATTLESHIP_BATTLESHIPENTITIES_H

#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct Coord {
    int x;
    int y;
    explicit Coord(const std::string& str);
    Coord(int x, int y);
    Coord();
    bool operator==(const Coord& other) const;
    bool operator<(const Coord& other) const;
};

std::ostream& operator<<(std::ostream& out, const Coord& coord);

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

class Board {
    std::vector<Ship> ships;

    std::vector<std::vector<HitResult>> board;
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
    const std::vector<std::vector<HitResult>>& get_board() const;
    const std::vector<std::vector<int>>& get_ships() const;
};

class Figure {
    std::vector<Coord> body;

public:
    void rotate();
    void shift_to(const Coord& destination);
    void reflect();
    Figure(std::vector<Coord> coords);
    Figure(const Coord& corner1, const Coord& corner2);
    const std::vector<Coord>& get_coords() const;
    bool operator==(Figure other) const;
    //operator std::vector<Coord>();
};

#endif //BATTLESHIP_BATTLESHIPENTITIES_H

