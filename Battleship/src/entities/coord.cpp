#include "coord.hpp"

Coord::Coord(std::string str) {
    if (str[0] < 'a')
        x = str[0] - 'A';
    else
        x = str[0] - 'a';

    str.erase(0, 1);
    y = std::stoi(str) - 1;
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

Coord& Coord::operator*=(int coef) {
    x *= coef;
    y *= coef;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Coord& coord) {
    out << char('A' + coord.x) << coord.y + 1;
    return out;
}
