#include "console_interface.hpp"

bool ConsoleInterface::check_input(const std::string& word) {
    if (word.size() < 2 || word.size() > 3)
        return false;
    if (!('a' <= word[0] && word[0] <= 'j' || 'A' <= word[0] && word[0] <= 'J'))
        return false;
    return (word.size() == 2 && '0' <= word[1] && word[1] <= '9') ||
           (word.size() == 3 && word[1] == '1' && word[2] == '0');
}

Mode ConsoleInterface::select_mode() {
    cout << YELLOW << "Hello! To play the game please select the mode:\n";
    cout << "1 - play against AI with a generated board for you\n";
    cout << "2 - play against AI with a manually created board\n";
    cout << "3 - play against your friend with manually created boards\n" << RESET;
    std::string mode_str;
    int mode_int = 0;
    while (true){
        cin >> mode_str;
        try {
            mode_int = std::stoi(mode_str);
        } catch (...) {
            cout << RED << "Please enter a number\n" << RESET;
        }
        if (mode_int < 1 || mode_int > 3)
            cout << RED << "Incorrect input" << std::endl << RESET;
        else
            break;
    }
    return Mode(mode_int);
}

int ConsoleInterface::select_board_size() {
    cout << YELLOW << "Select a board size: from 3 through 10\n";
    std::string size_str;
    int size_int = 0;
    while (true){
        cin >> size_str;
        try {
            size_int = std::stoi(size_str);
        } catch (...) {
            cout << RED << "Error. Please enter a number\n" << RESET;
        }
        if (size_int < 3 || size_int > 10)
            cout << RED << "Incorrect input. Your number should be >= 3 and <= 10" << std::endl << RESET;
        else
            break;
    }
    return size_int;
}

ShipSet* ConsoleInterface::select_shipset(int board_size) {
    ShipSet* shipset = new ShipSet;
    std::vector<ShipSetName> shipset_names = {ShipSetName::STANDART, ShipSetName::TRIANGLE, ShipSetName::FUNNY};
    std::vector<std::string> str_names = {"standard shipset", "triangle shipset", "funny shipset"};
    cout << YELLOW << "Now select the shipset\n" << RESET;
    for (int type = 0; type < shipset_names.size(); type++) {
        cout << YELLOW << type + 1 << " - " << str_names[type] << ":\n" << RESET;
        shipset->build(shipset_names[type], board_size);
        draw_ships(shipset->get(), board_size);
    }

    std::string choice_str;
    int choice_int = 0;
    while (true){
        cin >> choice_str;
        try {
            choice_int = std::stoi(choice_str);
        } catch (...) {
            cout << RED << "Please enter a number\n" << RESET;
        }
        if (choice_int < 1 || choice_int > shipset_names.size())
            cout << RED << "Incorrect input" << std::endl << RESET;
        else
            break;
    }
    choice_int--;

    shipset->build(shipset_names[choice_int], board_size);
    return shipset;
}

std::string ConsoleInterface::enter_name() {
    cout << YELLOW << "Enter your name\n" << RESET;
    std::string name;
    cin >> name;
    return name;
}

std::vector<Coord> ConsoleInterface::read() {
    std::string line, word;
    do {
        std::getline(std::cin, line);
    } while (line == "\n" || line.empty());
    std::stringstream ss;
    ss << line;

    std::vector<Coord> ans;
    while (ss >> word) {
        if (!check_input(word)) {
            std::cout << "Incorrect input" << std::endl;
            return {};
        }
        ans.emplace_back(word);
    }
    return std::move(ans);
}


void ConsoleInterface::draw_board_init(const Board* board) {
    int n = board->size;
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


void ConsoleInterface::draw_opponent_board(const Board* board) {
    int n = board->size;
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


std::pair<int, int> ConsoleInterface::get_grid_proportions(const std::vector<const Figure *> &ships) {
    std::pair<int, int> span = {-1, -1};
    for (auto& figure: ships) {
        auto curr_span = figure->get_proportions();
        if (curr_span.first > curr_span.second)
            std::swap(curr_span.first, curr_span.second);
        span.first = std::max(span.first, curr_span.first);
        span.second = std::max(span.second, curr_span.second);
    }
    return span;
}


void ConsoleInterface::draw_ships_in_line(int block_size, std::vector<Figure>&& ships, int line_size) {
    int height = 0;
    for (auto& figure : ships) {
        figure.standardize();
        height = std::max(height, figure.get_proportions().first);
    }
    std::vector<std::vector<int>> lines(height);
    for (int i = 0; i < ships.size(); i++) {
        for (auto& coord : ships[i].get_coords())
            lines[coord.x].push_back(coord.y + block_size * i);
    }

    for (auto& line : lines) {
        height--;
        std::sort(line.begin(), line.end());
        for (int j = 0, place = 0; j < line.size(); j++, place++) {
            while (place < line[j]) {
                cout << BLACK << (height == 0 ? "___" : "   ") << RESET;
                place++;
            }
            cout << YELLOW << "[o]" << RESET;
        }
        for (int pos = line.back() + 1; pos < line_size; pos++)
            cout << BLACK << (height == 0 ? "___" : "   ") << RESET;
        cout << "\n";
    }
}


void ConsoleInterface::draw_ships(const std::vector<const Figure*>& ships, int board_size) {
    auto grid = get_grid_proportions(ships);
    int cnt_line = (board_size + 2) / (grid.second + 1);
    int block_width = (board_size + 2) / cnt_line;
    for (int i = 0; i < ships.size(); i += cnt_line) {
        std::vector<Figure> in_one_line;
        for (int j = i; j < std::min((int)ships.size(), i + cnt_line); j++) {
            in_one_line.emplace_back(*ships[j]);
            auto prop = ships[j]->get_proportions();
            if (prop.first > prop.second)
                in_one_line.back().rotate();
        }
        draw_ships_in_line(block_width, std::move(in_one_line), board_size + 1);
    }
}


void ConsoleInterface::draw_players_board(const Board* board) {
    int n = board->size;
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


void ConsoleInterface::move(const std::string& name, const Board* board) {
    cout << YELLOW << "\n\n" << name << "! Enter your shot (eg B7)\n" << RESET;
    draw_opponent_board(board);
}


void ConsoleInterface::board_creation(const Board* board, std::vector<const Figure*> ships) {
    cout << YELLOW << "\nPlace the following ships via enumeration of their coordinates (eg B2 B3 B4)\n";
    draw_ships(ships, board->size);
    draw_board_init(board);
}


void ConsoleInterface::board_creation_finished(const Board* board) {
    cout << YELLOW << "\nYou have successfully filled the board. Here it is:\n" << RESET;
    draw_board_init(board);
}


void ConsoleInterface::board_generation_finished(const Board* board) {
    cout << YELLOW << "\nYour board was generated for you. Here it is:\n" << RESET;
    draw_board_init(board);
}


void ConsoleInterface::report_success(HitResult result) {
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


void ConsoleInterface::report_losses(const std::string& name, const std::vector<std::pair<Coord, HitResult>>& losses,
                                     const Board* board) {
    cout << "\n\n";
    for (auto& loss : losses)
        cout << YELLOW << name << "! Your opponent had a " << string_hit_results[int(loss.second)] <<
             " at " << loss.first << std::endl;
    draw_players_board(board);
}

void ConsoleInterface::winning_message(const std::string& name) {
    cout << RED << "\nPlayer " << name << " won!\n";
}

void ConsoleInterface::change_players() {
    std::string sign_to_proceed;
    cout << YELLOW << "Enter anything to proceed\n" << RESET;
    cin >> sign_to_proceed;
    system("clear");
    cout << YELLOW << "Give a turn to the other player. Enter anything to proceed\n" << RESET;
    cin >> sign_to_proceed;
}