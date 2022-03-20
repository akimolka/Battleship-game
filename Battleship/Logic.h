#ifndef BATTLESHIP_LOGIC_H
#define BATTLESHIP_LOGIC_H

#include "Entities.h"
#include "Output.h"
#include "Input.h"
#include "Players.h"
#include "BoardGenerators.h"
#include "ShipSets.h"
#include <queue>

enum Mode { TWO_PLAYERS, AGAINST_RANDOM, AGAINST_DUMMY, AGAINST_PROFI };

class Game {
    Input* input = new ConsoleInput();
    Output* output = new ConsoleOutput();
    BoardGenerator* board_gen = new RandomBoardGenerator();
    const ShipSet* shipset;
    Board* board_a;
    Board* board_b;
    Player* player_a;
    Player* player_b;

    void run();

public:
    Game(const ShipSet* shipset);

    Board* fill_board();

    void add_board(Board* board);
    void add_boards(Board* first_board, Board* second_board);

    void play(Mode mode);
};


#endif //BATTLESHIP_LOGIC_H