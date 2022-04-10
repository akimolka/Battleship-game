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

void Game::set_ai() {
    std::cout << "Enter your name\n";
    std::string name_a;
    std::cin >> name_a;
    board_b = board_gen->get(shipset);
    player_a = new LivePlayer(name_a, board_b, interface);
    player_b = player_b = new RectanglePlayer(board_a);
}

void Game::play() {
    Mode mode = interface->select_mode();

    switch (mode) {
        case Mode::AI_MANUALLY:
            board_a = fill_board();
            set_ai();
            break;
        case Mode::AI_GENERATED:
            board_a = board_gen->get(shipset);
            set_ai();
            break;
        case Mode::TWO_LIVE:
            std::cout << "Enter your names\n";
            std::string name_a, name_b;
            std::cin >> name_a >> name_b;
            board_a = fill_board();
            // flush
            board_b = fill_board();
            player_a = new LivePlayer(name_a, board_b, interface);
            player_b = new LivePlayer(name_b, board_a, interface);
            break;
    }

    run();
}

