#ifndef BATTLESHIP_PLAYER_HPP
#define BATTLESHIP_PLAYER_HPP

#include <utility>

#include "entities/board.hpp"
#include "entities/ship.hpp"
#include "entities/coord.hpp"
#include "interface/interface.hpp"

class Player {
protected:
    const Board* opponent_board;
    const int board_size;

    inline static const std::vector<const std::pair<int, int>> neighbour_moves = {{-1, -1}, {-1, 0}, {-1, 1},
                                                                                  {0,  -1}, {0, 1},
                                                                                  {1,  -1}, {1, 0}, {1, 1}};

    bool is_valid(const Coord& coord);
    void mark_uninteresting_rec(const Coord& coord, std::vector<std::vector<bool>>& interesting,
                                std::vector<std::vector<bool>>& used);
    void mark_uninteresting(const Coord& coord, std::vector<std::vector<bool>>& interesting);

public:
    std::string name;
    Player(const Board* board, std::string  name);
    virtual Coord get_move() = 0;
    virtual void report_success(HitResult result) = 0;
    virtual void report_losses(const std::vector<std::pair<Coord, HitResult>>& losses, const Board* board) = 0;
    virtual ~Player() = default;
};

#endif //BATTLESHIP_PLAYER_HPP
