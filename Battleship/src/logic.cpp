#include "logic.hpp"

void Game::run() {
    std::vector<Player*> players = {player_a, player_b};
    std::vector<Board*> boards = {board_a, board_b};
    std::vector<int> count(2);
    count[0] = count[1] = shipset->get().size();
    int turn = 0;
    while (count[0] && count[1]) {
        Coord shot = players[turn]->get_move();
        HitResult result = boards[(turn + 1) % 2]->hit(shot);
        players[turn]->report_success(result);
        players[(turn + 1) % 2]->report_losses(shot, result, boards[(turn + 1) % 2]);
        if (result == HitResult::MISS)
            turn = (turn + 1) % 2;
        else if (result == HitResult::KILL)
            count[(turn + 1) % 2]--;
    }
    if (count[0])
        interface->winning_message("Player A");
    else
        interface->winning_message("Player B");
}


Game::Game(const ShipSet* shipset): shipset(shipset), board_a(nullptr), board_b(nullptr),
    player_a(nullptr), player_b(nullptr) {}


Board* Game::fill_board() {
    Board* board = new Board();
    std::vector<const Figure*> ships_to_place = shipset->get();
    interface->board_creation(board, ships_to_place);
    while (true) {
        std::vector<Coord> input_figure = interface->read();
        for (auto it = ships_to_place.begin(); it < ships_to_place.end(); it++)
            if (**it == input_figure && board->add_ships(input_figure)) {
                ships_to_place.erase(it);
                break;
            }
        if (ships_to_place.empty())
            break;
        interface->board_creation(board, ships_to_place);
    }
    interface->board_creation_finished(board);
    return board;
}


void Game::add_board(Board* board) {
    board_a = board;
};


void Game::add_boards(Board* first_board, Board* second_board) {
    board_a = first_board;
    board_b = second_board;
}

void Game::play(Mode mode) {
    if (mode == Mode::TWO_PLAYERS && (board_a == nullptr || board_b == nullptr))
        std::cout << "Initialize two boards first with add_boards method!"; //TODO move all interface to interface
    else if (mode == Mode::TWO_PLAYERS) {
        std::cout << "Enter your names\n";
        std::string name_a, name_b;
        std::cin >> name_a >> name_b;
        player_a = new LivePlayer(name_a, board_b, interface);
        player_b = new LivePlayer(name_b, board_a, interface);
    }
    else if (board_a == nullptr) {
        std::cout << "Initialize your board with add_board method first!";
    }
    else {
        std::cout << "Enter your name\n";
        std::string name_a;
        std::cin >> name_a;
        board_b = board_gen->get(shipset);
        player_a = new LivePlayer(name_a, board_b, interface);
        switch (mode) {
            case Mode::AGAINST_RANDOM:
                player_b = new RandomPlayer(board_a);
                break;
            case Mode::AGAINST_DUMMY:
                player_b = new DummyRectanglePlayer(board_a);
        }
    }

    run();
}

