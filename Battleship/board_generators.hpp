#ifndef BATTLESHIP_BOARDGENERATORS_H
#define BATTLESHIP_BOARDGENERATORS_H

#include "Entities.h"
#include "ShipSets.h"
#include <ctime>
#include <cstdlib>

class BoardGenerator {
protected:
    static const int size = 10;
public:
    virtual Board* get(const ShipSet* shipset) const = 0;
};

class RandomBoardGenerator: public BoardGenerator {
    static const int max_fill_board_tries = 3;
    static const int max_place_figure_tries = 3;
    static const int max_random_times = 7;

    static bool check_figure_coords(const Figure& figure);
    static bool place_figure(Figure& figure, Board* board);

public:
    RandomBoardGenerator();
    Board* get(const ShipSet* shipset) const override;
};

#endif //BATTLESHIP_BOARDGENERATORS_H