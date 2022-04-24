#ifndef BATTLESHIP_FIGURE_HPP
#define BATTLESHIP_FIGURE_HPP

#include "coord.hpp"
#include <vector>

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
    std::pair<int, int> get_proportions() const;
    void standardize();
};

#endif //BATTLESHIP_FIGURE_HPP
