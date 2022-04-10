#ifndef BATTLESHIP_LOGIC_HPP
#define BATTLESHIP_LOGIC_HPP

#include "entities/board.hpp"
#include "interface/console_interface.hpp"
#include "players/live_player.hpp"
#include "players/rectangle_player.hpp"
#include "players/random_player.hpp"
#include "board_generators/random_board_generator.hpp"
#include "ship_sets/ship_sets.hpp"
#include <queue>

enum Mode { TWO_PLAYERS, AGAINST_RANDOM, AGAINST_DUMMY, AGAINST_PROFI };

class Game {
    Interface* interface = new ConsoleInterface();
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


#endif //BATTLESHIP_LOGIC_HPP
