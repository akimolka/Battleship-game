#include <iostream>
#include "BattleshipEntities.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using std::cout;

class Output {
protected:
    std::vector<std::string> string_hit_results = {"none", "miss", "hit", "kill"};

public:
    virtual void board_creation(const Board* board, std::vector<const Figure*> ships) = 0;
    virtual void move(const std::string& name, const Board* board) = 0;
    virtual void report_success(HitResult result) = 0;
    virtual void report_losses(const std::string& name, const Coord& shot, HitResult result, const Board* board) = 0;
};

class ConsoleOutput: public Output {
private:
    void draw_board_init(const Board* board) {
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

    void draw_opponent_board(const Board* board) {
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

    void draw_ship(const Figure* ship) {
        cout << ship->get_coords().size() << "\n";  //TODO
    }

    void draw_players_board(const Board* board) {
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

public:
    void move(const std::string& name, const Board* board) override {
        cout << YELLOW << name << "! Enter your shot (eg B7)\n" << RESET;
        draw_opponent_board(board);
    }


    void board_creation(const Board* board, std::vector<const Figure*> ships) override {
        cout << YELLOW << "Place the following ships:\n";
        for (const Figure* figure : ships)
            draw_ship(figure);
        draw_board_init(board);
    }

    void report_success(HitResult result) override {
        switch (result) {
            case HitResult::MISS:
                cout << YELLOW << "Oh you've missed :(\n" << RESET;
                break;
            case HitResult::HIT:
                cout << YELLOW << "Bang! You've hit it\n" << RESET;
                break;
            case HitResult::KILL:
                cout << YELLOW << "Smash! --- kill ---\n" << RESET;
        }
    }

    void report_losses(const std::string& name, const Coord& shot, HitResult result, const Board* board) override {
        std::cout << YELLOW << name << "! Yout opponent had a " << string_hit_results[int(result)] <<
            " at " << shot << std::endl;
        draw_players_board(board);
    }
};