#ifndef BATTLESHIP_CONSOLE_INTERFACE_HPP
#define BATTLESHIP_CONSOLE_INTERFACE_HPP

#include "interface.hpp"
#include <iostream>
#include <sstream>

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

using std::cin;
using std::cout;

class ConsoleInterface: public Interface {
private:
    static bool check_input(const std::string& word, int board_size);
    void draw_board_init(const Board* board);
    void draw_opponent_board(const Board* board);
    std::pair<int, int> get_grid_proportions(const std::vector<const Figure*>& ships);
    void draw_ships_in_line(int block_size, std::vector<Figure>&& ships, int line_size);
    void draw_players_board(const Board* board);

public:
    Mode select_mode() override;
    int select_board_size() override;
    ShipSet* select_shipset(int board_size) override;
    std::string enter_name() override;
    std::vector<Coord> read(int board_size) override;
    void move(const std::string& name, const Board* board) override;
    void draw_ships(const std::vector<const Figure*>& ships, int board_size) override;
    void board_creation(const Board* board, std::vector<const Figure*> ships) override;
    void board_creation_finished(const Board* board) override;
    void board_generation_finished(const Board* board) override;
    void report_success(HitResult result) override;
    void report_losses(const std::string& name, const std::vector<std::pair<Coord, HitResult>>& losses,
                       const Board* board) override;
    void winning_message(const std::string& name) override;
    void change_players() override;
};

#endif //BATTLESHIP_CONSOLE_INTERFACE_HPP
