#include "Output.h"


void ConsoleOutput::draw_board_init(const Board* board) {
    int n = Board::size;
    const std::vector<std::vector<int>>& ships = board->get_ships();
    cout << "  ";
    for (int j = 1; j <= n; j++)
        cout << BOLDYELLOW << " " << j << (j < 10 ? " " : "") << RESET;
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << BOLDYELLOW << char('A' + i) << " " << RESET;
        for (int j = 0; j < n; j++)
            if (ships[i][j] != -1) cout << BOLDGREEN << "[o]" << RESET;
            else cout << "[ ]";
        cout << "\n";
    }
}


void ConsoleOutput::draw_opponent_board(const Board* board) {
    int n = Board::size;
    const std::vector<std::vector<HitResult>>& scheme = board->get_board();
    cout << "  ";
    for (int j = 1; j <= n; j++)
        cout << BOLDYELLOW << " " << j << (j < 10 ? " " : "") << RESET;
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << BOLDYELLOW << char('A' + i) << " " << RESET;
        for (int j = 0; j < n; j++)
            switch (scheme[i][j]) {
                case HitResult::NONE:
                    cout << CYAN << "[~]" << RESET;
                    break;
                case HitResult::MISS:
                    cout << CYAN << "   " << RESET;
                    break;
                case HitResult::HIT:
                    cout << RED << "[x]" << RESET;
                    break;
                case HitResult::KILL:
                    cout << BLACK << "[x]" << RESET;
            }
        cout << "\n";
    }
}


void ConsoleOutput::draw_ship(const Figure* ship) {
    cout << ship->get_coords().size() << " ";  //TODO
}


void ConsoleOutput::draw_players_board(const Board* board) {
    int n = Board::size;
    const std::vector<std::vector<HitResult>>& scheme = board->get_board();
    const std::vector<std::vector<int>>& ships = board->get_ships();
    cout << "  ";
    for (int j = 1; j <= n; j++)
        cout << BOLDYELLOW << " " << j << (j < 10 ? " " : "") << RESET;
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << BOLDYELLOW << char('A' + i) << " " << RESET;
        for (int j = 0; j < n; j++)
            switch (scheme[i][j]) {
                case HitResult::NONE:
                    if (ships[i][j] == -1) cout << CYAN << "[~]" << RESET;
                    else cout << GREEN << "[o]" << RESET;
                    break;
                case HitResult::MISS:
                    cout << CYAN << "   " << RESET;
                    break;
                default:
                    cout << RED << "[x]" << RESET;
            }
        cout << "\n";
    }
}


void ConsoleOutput::move(const std::string& name, const Board* board) {
    cout << YELLOW << "\n\n" << name << "! Enter your shot (eg B7)\n" << RESET;
    draw_opponent_board(board);
}


void ConsoleOutput::board_creation(const Board* board, std::vector<const Figure*> ships) {
    cout << YELLOW << "\nPlace the following ships via enumeration of their coordinates (eg B2 B3 B4)\n";
    for (const Figure* figure : ships)
        draw_ship(figure);
    cout << "\n\n";
    draw_board_init(board);
}


void ConsoleOutput::board_creation_finished(const Board* board) {
    cout << YELLOW << "\nYou have successfully filled the board. Here it is:\n" << RESET;
    draw_board_init(board);
}


void ConsoleOutput::report_success(HitResult result) {
    switch (result) {
        case HitResult::MISS:
            cout << YELLOW << "Oh you've missed :(\n" << RESET;
            break;
        case HitResult::HIT:
            cout << YELLOW << "Bang! You've hit it\n" << RESET;
            break;
        case HitResult::KILL:
            cout << YELLOW << "Smash! KILL\n" << RESET;
    }
}


void ConsoleOutput::report_losses(const std::string& name, const Coord& shot, HitResult result, const Board* board) {
    cout << YELLOW << "\n\n"<< name << "! Your opponent had a " << string_hit_results[int(result)] <<
         " at " << shot << std::endl;
    draw_players_board(board);
}

void ConsoleOutput::winning_message(const std::string& name) {  // TODO add name if LivePlayer, note AI otherwise
    cout << "RED" << "\nPlayer " << name << " won!\n";
}
