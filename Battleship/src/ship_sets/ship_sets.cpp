#include "ship_sets.hpp"

StandardShips::StandardShips()
: patrol_boat({0, 0}, {0, 0}), submarine({0, 0}, {0, 1}),
    destroyer({0, 0}, {0, 2}), carrier({0, 0}, {0, 3}) {};

std::vector<const Figure*> StandardShips::get() const {
    return {&patrol_boat, &patrol_boat, &patrol_boat, &patrol_boat,
            &submarine, &submarine, &submarine,
            &destroyer, &destroyer,
            &carrier};
}
