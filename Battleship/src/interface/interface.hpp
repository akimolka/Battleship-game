#ifndef BATTLESHIP_INTERFACE_HPP
#define BATTLESHIP_INTERFACE_HPP

#include "entities/figure.hpp"
#include "entities/board.hpp"
#include "entities/ship.hpp"

class Interface {
protected:
    std::vector<std::string> string_hit_results = {"none", "miss", "hit", "kill"};
public:
    virtual std::vector<Coord> read() = 0;
    virtual void board_creation(const Board* board, std::vector<const Figure*> ships) = 0;
    virtual void board_creation_finished(const Board* board) = 0;
    virtual void move(const std::string& name, const Board* board) = 0;
    virtual void report_success(HitResult result) = 0;
    virtual void report_losses(const std::string& name, const Coord& shot, HitResult result, const Board* board) = 0;
    virtual void winning_message(const std::string& name) = 0;
    virtual ~Interface() = default;
};

#endif //BATTLESHIP_INTERFACE_HPP
