#ifndef BATTLESHIP_INTERFACE_HPP
#define BATTLESHIP_INTERFACE_HPP

#include "entities/figure.hpp"
#include "entities/board.hpp"
#include "entities/ship.hpp"
#include "modes/modes.hpp"
#include "modes/ship_sets.hpp"

class Interface {
protected:
    std::vector<std::string> string_hit_results = {"none", "miss", "hit", "kill"};
public:
    virtual Mode select_mode() = 0;
    virtual ShipSet* select_shipset(int board_size) = 0;
    virtual std::string enter_name() = 0;
    virtual std::vector<Coord> read() = 0;
    virtual void board_creation(const Board* board, std::vector<const Figure*> ships) = 0;
    virtual void board_creation_finished(const Board* board) = 0;
    virtual void board_generation_finished(const Board* board) = 0;
    virtual void move(const std::string& name, const Board* board) = 0;
    virtual void draw_ships(const std::vector<const Figure*>& ships, int board_size) = 0;
    virtual void report_success(HitResult result) = 0;
    virtual void report_losses(const std::string& name, const std::vector<std::pair<Coord, HitResult>>& losses,
                               const Board* board) = 0;
    virtual void winning_message(const std::string& name) = 0;
    virtual void change_players() = 0;
    virtual ~Interface() = default;
};

#endif //BATTLESHIP_INTERFACE_HPP
