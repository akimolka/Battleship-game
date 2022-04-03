#ifndef BATTLESHIP_OUTPUT_HPP
#define BATTLESHIP_OUTPUT_HPP

#include <iostream>
#include "entities.hpp"

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
    virtual void board_creation_finished(const Board* board) = 0;
    virtual void move(const std::string& name, const Board* board) = 0;
    virtual void report_success(HitResult result) = 0;
    virtual void report_losses(const std::string& name, const Coord& shot, HitResult result, const Board* board) = 0;
    virtual void winning_message(const std::string& name) = 0;
};


class ConsoleOutput: public Output {
private:
    void draw_board_init(const Board* board);
    void draw_opponent_board(const Board* board);
    void draw_ship(const Figure* ship);
    void draw_players_board(const Board* board);

public:
    void move(const std::string& name, const Board* board) override;
    void board_creation(const Board* board, std::vector<const Figure*> ships) override;
    void board_creation_finished(const Board* board) override;
    void report_success(HitResult result) override;
    void report_losses(const std::string& name, const Coord& shot, HitResult result, const Board* board) override;
    void winning_message(const std::string& name) override;
};

#endif //BATTLESHIP_OUTPUT_HPP
