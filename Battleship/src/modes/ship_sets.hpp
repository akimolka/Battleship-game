#ifndef BATTLESHIP_SHIP_SETS_HPP
#define BATTLESHIP_SHIP_SETS_HPP

#include <vector>
#include "entities/figure.hpp"

class ShipSet {
public:
    virtual std::vector<const Figure*> get() const = 0;
    virtual ~ShipSet() = default;
};


class StandardShips: public ShipSet {
    const Figure patrol_boat;  // ◊    x4
    const Figure submarine;    // ◊◊   x3
    const Figure destroyer;    // ◊◊◊  x2
    const Figure carrier;      // ◊◊◊◊ x1

public:
    StandardShips();
    std::vector<const Figure*> get() const override;
};


class TriangleShips: public ShipSet {
    const Figure patrol_boat;
    const Figure submarine;
    const Figure destroyer;
    //  ◊      ◊       ◊
    //  ◊◊ x3  ◊◊◊ x2  ◊◊◊◊ x1

public:
    TriangleShips();
    std::vector<const Figure*> get() const override;
};


class FunnyShips: public ShipSet {
    const Figure zigzag;
    const Figure t_shape;
    const Figure c_shape;
    //  ◊◊       ◊      ◊◊
    //   ◊◊ x2   ◊◊ x2   ◊ x2
    //           ◊      ◊◊

public:
    FunnyShips();
    std::vector<const Figure*> get() const override;
};

#endif //BATTLESHIP_SHIP_SETS_HPP
