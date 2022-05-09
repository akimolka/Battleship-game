#include "ship_set.hpp"


void ShipSet::build_standard_shipset(int board_size) {
    ships.clear();
    if (board_size == 3) {
        ships = {&ShipFigures::rectangle[0], &ShipFigures::rectangle[0]};
    }
    else if (board_size == 4) {
        ships = {&ShipFigures::rectangle[0], &ShipFigures::rectangle[0],
                 &ShipFigures::rectangle[1]};
    }
    else {
        std::vector<int> cnt(4);
        cnt[0] = std::max(board_size / 2 - 1, 2);
        cnt[1] = 1 + (board_size - 4) * 2 / 5;
        cnt[2] = 1 + (board_size - 3) / 5;
        cnt[3] = 1 + (board_size - 4) / 5;
        for (int figure = 0; figure < cnt.size(); figure++) {
            for (int i = 0; i < cnt[figure]; i++)
                ships.push_back(&ShipFigures::rectangle[figure]);
        }
    }
}

void ShipSet::build_triangle_shipset(int board_size) {
    ships.clear();
    if (board_size == 3) {
        ships = {&ShipFigures::triangle[0]};
    }
    else if (board_size == 4) {
        ships = {&ShipFigures::triangle[0], &ShipFigures::triangle[0]};
    }
    else {
        std::vector<int> cnt(3);
        cnt[0] = 2 + (board_size >= 7 ? 1 : 0);
        cnt[1] = 1 + (board_size >= 7 ? 1 : 0);
        cnt[2] = (board_size >= 8 ? 1 : 0);
        for (int figure = 0; figure < cnt.size(); figure++) {
            for (int i = 0; i < cnt[figure]; i++)
                ships.push_back(&ShipFigures::triangle[figure]);
        }
    }
}

void ShipSet::build_funny_shipset(int board_size) {
    ships.clear();
    if (board_size == 3) {
        ships = {&ShipFigures::triangle[0]};
    }
    else if (board_size == 4) {
        ships = {&ShipFigures::zigzag};
    }
    else {
        std::vector<int> cnt(4);
        std::vector<const Figure*> funny = {&ShipFigures::triangle[0], &ShipFigures::zigzag,
                                      &ShipFigures::t_shape, &ShipFigures::c_shape};
        cnt[0] = (board_size == 6 || board_size == 8 ? 1 : 0);
        cnt[1] = 1 + (board_size >= 7 ? 1 : 0);
        cnt[2] = 1 + (board_size >= 7 ? 1 : 0);
        cnt[3] = std::max(board_size - 8, 0);
        for (int figure = 0; figure < cnt.size(); figure++) {
            for (int i = 0; i < cnt[figure]; i++)
                ships.push_back(funny[figure]);
        }
    }
}

std::vector<const Figure *> ShipSet::get() const {
    return ships;
}

void ShipSet::build(ShipSetName ship_set, int board_size) {
    switch (ship_set) {
        case ShipSetName::STANDART:
            build_standard_shipset(board_size);
            break;
        case ShipSetName::TRIANGLE:
            build_triangle_shipset(board_size);
            break;
        case ShipSetName::FUNNY:
            build_funny_shipset(board_size);
    }
}
