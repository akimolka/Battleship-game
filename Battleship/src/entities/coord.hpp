#ifndef BATTLESHIP_COORD_HPP
#define BATTLESHIP_COORD_HPP

#include <string>
#include <istream>

struct Coord {
    int x;
    int y;
    explicit Coord(const std::string& str);
    Coord(int x, int y);
    Coord();
    bool operator==(const Coord& other) const;
    bool operator<(const Coord& other) const;
    Coord& operator*=(int coef);
};

std::ostream& operator<<(std::ostream& out, const Coord& coord);

#endif //BATTLESHIP_COORD_HPP
