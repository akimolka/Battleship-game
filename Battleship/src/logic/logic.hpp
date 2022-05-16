#ifndef BATTLESHIP_LOGIC_HPP
#define BATTLESHIP_LOGIC_HPP

#include "entities/board.hpp"
#include "interface/console_interface.hpp"
#include "players/live_player.hpp"
#include "players/rectangle_player.hpp"
#include "players/random_player.hpp"
#include "board_generators/random_board_generator.hpp"
#include "modes/ship_set.hpp"
#include "modes/modes.hpp"
#include <queue>

class Game {
    Interface* interface = new ConsoleInterface();
    BoardGenerator* board_gen = new RandomBoardGenerator();
    const ShipSet* shipset;
    int board_size = 9;
    Board* board_a;
    Board* board_b;
    Player* player_a;
    Player* player_b;

    void run(Mode mode);
    void set_ai();

public:
    Board* fill_board();

    void play();
    ~Game();
};


#endif //BATTLESHIP_LOGIC_HPP
