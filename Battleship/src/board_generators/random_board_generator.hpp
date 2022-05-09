#ifndef BATTLESHIP_RANDOM_BOARD_GENERATOR_HPP
#define BATTLESHIP_RANDOM_BOARD_GENERATOR_HPP

#include "entities/figure.hpp"
#include "entities/board.hpp"
#include "modes/ship_sets.hpp"
#include "board_generator.hpp"
#include <ctime>
#include <cstdlib>

class RandomBoardGenerator: public BoardGenerator {
    static const int max_fill_board_tries = 3;
    static const int max_place_figure_tries = 3;
    static const int max_random_times = 7;

    static bool check_figure_coords(const Figure& figure);
    static bool place_figure(Figure& figure, Board* board);

public:
    RandomBoardGenerator();
    Board* get(const ShipSet* shipset, int board_size) const override;
};

#endif //BATTLESHIP_RANDOM_BOARD_GENERATOR_HPP
