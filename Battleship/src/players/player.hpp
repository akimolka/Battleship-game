#ifndef BATTLESHIP_PLAYER_HPP
#define BATTLESHIP_PLAYER_HPP

#include "entities/board.hpp"
#include "entities/ship.hpp"
#include "entities/coord.hpp"
#include "interface/interface.hpp"

class Player {
protected:
    const Board* opponent_board;
    inline static const std::vector<const std::pair<int, int>> neighbour_moves = {{-1, -1}, {-1, 0}, {-1, 1},
                                                                                  {0,  -1}, {0, 1},
                                                                                  {1,  -1}, {1, 0}, {1, 1}};

    static bool is_valid(const Coord& coord);
    void mark_uninteresting_rec(const Coord& coord, std::vector<std::vector<bool>>& interesting,
                                std::vector<std::vector<bool>>& used);
    void mark_uninteresting(const Coord& coord, std::vector<std::vector<bool>>& interesting);

public:
    explicit Player(const Board* board);
    virtual Coord get_move() = 0;
    virtual void report_success(HitResult result) = 0;
    virtual void report_losses(const Coord& shot, HitResult result, const Board* board) = 0;
    virtual ~Player() = default;
};

#endif //BATTLESHIP_PLAYER_HPP
