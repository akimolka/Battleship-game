#include "ship.hpp"

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