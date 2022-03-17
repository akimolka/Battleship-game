#include "BattleshipEntities.h"
#include "Output.cpp"
#include "Input.cpp"

class ShipSet {
public:
    virtual std::vector<const Figure*> get() const = 0;
};

class StandardShips: public ShipSet {
    const Figure patrol_boat;  // ◊
    const Figure submarine;    // ◊◊
    const Figure destroyer;   // ◊◊◊
    const Figure carrier;      // ◊◊◊◊

public:
    StandardShips()
        : patrol_boat({0, 0}, {0, 0}), submarine({0, 0}, {0, 1}),
          destroyer({0, 0}, {0, 2}), carrier({0, 0}, {0, 3}) {};

    std::vector<const Figure*> get() const override {
        return {&patrol_boat, &patrol_boat, &patrol_boat, &patrol_boat,
                      &submarine, &submarine, &submarine,
                      &destroyer, &destroyer,
                      &carrier};
    }
};


class Game {
    Input* input = new ConsoleInput();
    Output* output = new ConsoleOutput();
    Board* A_board;
    Board* B_board;
    std::vector<const Figure*> ships;
public:
    Game(const ShipSet* shipset): A_board(nullptr), B_board(nullptr), ships(shipset->get()) {};

    Board* fill_board() {
        Board* board = new Board();
        std::vector<const Figure*> ships_to_place = ships;
        std::cout << "Enter ship coordinates\n";
        while (!ships_to_place.empty()) {
            std::vector<Coord> input_figure = input->read();
            for (auto it = ships_to_place.begin(); it < ships_to_place.end(); it++) // TODO message about incorrect ship
                if (**it == input_figure && board->add_ships(input_figure)) {
                    ships_to_place.erase(it);
                    break;
                }
            output->board_creation(board, ships_to_place);
        }
        return board;
    }
};
