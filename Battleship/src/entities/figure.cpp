#include "figure.hpp"

void Figure::rotate() {
    Coord head = body[0];
    for (int i = 1; i < body.size(); i++) {
        int delta_x = body[i].x - head.x;
        int delta_y = body[i].y - head.y;
        delta_y *= -1;
        body[i] = {head.x + delta_y, head.y + delta_x};
    }
}

void Figure::shift_to(const Coord& destination) {
    int delta_x = destination.x - body[0].x;
    int delta_y = destination.y - body[0].y;
    for (Coord& coord : body) {
        coord.x += delta_x;
        coord.y += delta_y;
    }
}

void Figure::reflect() {
    Coord head = body[0];
    for (Coord& coord : body) {
        coord.x += 2 * (body[0].x - coord.x);
    }
}

Figure::Figure(std::vector<Coord> coords): body(std::move(coords)) {};

Figure::Figure(const Coord& corner1, const Coord& corner2) { // upper-left and bottom-right
    for (int x = corner1.x; x <= corner2.x; x++)
        for (int y = corner1.y; y <= corner2.y; y++)
            body.emplace_back(x, y);
}

const std::vector<Coord>& Figure::get_coords() const {
    return body;
}

bool Figure::operator==(Figure other) const {
    if (body.size() != other.body.size())
        return false;

    std::vector<Coord> first = body;
    std::sort(first.begin(), first.end());

    for (int turn = 0; turn < 8; turn++) {
        if (turn == 4)
            other.reflect();
        std::sort(other.body.begin(), other.body.end());
        other.shift_to(first[0]);
        if (first == other.body) return true;
        other.rotate();
    }
    return false;
}

std::pair<int, int> Figure::get_proportions() const {
    std::pair<int, int> height = {body[0].x, body[0].x};
    std::pair<int, int> width = {body[0].y, body[0].y};
    for (auto& coord: body) {
        height.first = std::min(height.first, coord.x);
        width.first = std::min(width.first, coord.y);
        height.second = std::max(height.second, coord.x);
        width.second = std::max(width.second, coord.y);
    }
    return {height.second - height.first + 1, width.second - width.first + 1};
}

void Figure::standardize() {
    Coord limits = {INT_MAX, INT_MAX};
    for (auto& coord : body) {
        limits.x = std::min(limits.x, coord.x);
        limits.y = std::min(limits.y, coord.y);
    }
    limits *= -1;
    shift_to(limits);
}