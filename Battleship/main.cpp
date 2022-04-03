#include <iostream>
#include "logic.hpp"
#include "entities.hpp"
#include "ship_sets.hpp"
#include "board_generators.hpp"

using std::cout;
using std::cin;

void live_AI_manually() {  // 1 player against AI with a manually created board
    ShipSet* ships = new StandardShips();
    Game g(ships);
    Board* board = g.fill_board();
    g.add_board(board);
    g.play(Mode::AGAINST_DUMMY);
}

void live_AI_gen() {  // 1 player against AI with a generated board
    BoardGenerator* gen = new RandomBoardGenerator();
    ShipSet* ships = new StandardShips();
    Board* board_a = gen->get(ships);
    Game g(ships);
    g.add_board(board_a);
    g.play(Mode::AGAINST_DUMMY);
}

void live_live_gen() {  // 2 players with generated boards
    BoardGenerator* gen = new RandomBoardGenerator();
    ShipSet* ships = new StandardShips();
    Board* board_a = gen->get(ships);
    Board* board_b = gen->get(ships);
    Game g(ships);
    g.add_boards(board_a, board_b);
    g.play(Mode::TWO_PLAYERS);
}

int main() {
    cout << "Hello! To test the game please select the mode:\n";
    cout << "1 - play against AI with a manually created board\n";
    cout << "2 - play against AI with a generated board for you\n";
    cout << "3 - play against your friend with generated boards\n";
    int mode;
    cin >> mode;
    switch(mode) {
        case 1:
            live_AI_manually();
        case 2:
            live_AI_gen();
        case 3:
            live_live_gen();
    }
    return 0;
}
