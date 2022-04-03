#include <iostream>
#include "logic.hpp"
#include "entities.hpp"
#include "ship_sets.hpp"
#include "board_generators.hpp"

int main() {
    // 1 player against AI with manually created board
//    ShipSet* ships = new StandardShips();
//    Game g(ships);
//    Board* board = g.fill_board();
//    g.add_board(board);
//    g.play(Mode::AGAINST_DUMMY);

    // 2 players with generated boards:
//    BoardGenerator* gen = new RandomBoardGenerator();
//    ShipSet* ships = new StandardShips();
//    Board* board_a = gen->get(ships);
//    Board* board_b = gen->get(ships);
//    Game g(ships);
//    g.add_boards(board_a, board_b);
//    g.play(Mode::TWO_PLAYERS);

    // 1 player against AI with generated board
    BoardGenerator* gen = new RandomBoardGenerator();
    ShipSet* ships = new StandardShips();
    Board* board_a = gen->get(ships);
    Game g(ships);
    g.add_board(board_a);
    g.play(Mode::AGAINST_DUMMY);
    return 0;
}
