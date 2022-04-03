#ifndef BATTLESHIP_SHIPSETS_H
#define BATTLESHIP_SHIPSETS_H

#include <vector>
#include <ctime>
#include <cstdlib>
#include "Entities.h"

class ShipSet {
public:
    virtual std::vector<const Figure*> get() const = 0;
};

class StandardShips: public ShipSet {
    const Figure patrol_boat;  // ◊
    const Figure submarine;    // ◊◊
    const Figure destroyer;   // ◊◊◊
    const Figure carrier;      // ◊◊◊◊

public:
    StandardShips();
    std::vector<const Figure*> get() const override;
};

#endif //BATTLESHIP_SHIPSETS_H
