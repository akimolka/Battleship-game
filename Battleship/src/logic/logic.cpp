#include "logic.hpp"

void Game::run(Mode mode) {
    std::vector<Player*> players = {player_a, player_b};
    std::vector<Board*> boards = {board_a, board_b};
    std::vector<int> count(2);
    count[0] = count[1] = shipset->get().size();
    int turn = 0;
    std::vector<std::pair<Coord, HitResult>> losses;
    while (count[0] && count[1]) {
        Coord shot = players[turn]->get_move();
        HitResult result = boards[(turn + 1) % 2]->hit(shot);
        players[turn]->report_success(result);
        losses.emplace_back(shot, result);
        if (result == HitResult::MISS) {
            if (mode == Mode::TWO_LIVE)
                interface->change_players();
            turn = (turn + 1) % 2;
            players[turn]->report_losses(losses, boards[turn]);
            losses.clear();
        }
        else if (result == HitResult::KILL)
            count[(turn + 1) % 2]--;
    }
    if (count[0])
        interface->winning_message(player_a->name);
    else
        interface->winning_message(player_b->name);
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
    std::string name_a = interface->enter_name();
    board_b = board_gen->get(shipset);
    player_a = new LivePlayer(name_a, board_b, interface);
    player_b = new RandomPlayer(board_a);
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
            interface->board_generation_finished(board_a);
            set_ai();
            break;
        case Mode::TWO_LIVE:
            std::string name_a = interface->enter_name(), name_b = interface->enter_name();
            board_a = fill_board();
            interface->change_players();
            board_b = fill_board();
            interface->change_players();
            player_a = new LivePlayer(name_a, board_b, interface);
            player_b = new LivePlayer(name_b, board_a, interface);
            break;
    }

    run(mode);
}

Game::~Game() {
    delete interface;
    delete board_gen;
    delete shipset;
    delete board_a;
    delete board_b;
    delete player_a;
    delete player_b;
}

//TODO shipsets
//TODO choice of shipsets
//TODO board size
//TODO AI