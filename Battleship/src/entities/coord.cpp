#include "coord.hpp"

Coord::Coord(const std::string& str) {
    if ('A' <= str[0] && str[0] <= 'J') // todo deal with invalid input
        x = str[0] - 'A';               // todo depend on size, not number 10
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

Coord& Coord::operator*=(int coef) {
    x *= coef;
    y *= coef;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Coord& coord) {
    out << char('A' + coord.x) << coord.y + 1;
    return out;
}
