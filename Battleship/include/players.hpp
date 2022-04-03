#ifndef BATTLESHIP_PLAYERS_HPP
#define BATTLESHIP_PLAYERS_HPP

#include "entities.hpp"
#include "output.hpp"
#include "input.hpp"
#include <ctime>
#include <cstdlib>
#include <queue>

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

//const std::vector<const std::pair<int, int>>Player::neighbour_moves = {{-1, -1}, {-1, 0}, {-1, 1},
//                                                                       {0,  -1}, {0, 1},
//                                                                       {1,  -1}, {1, 0}, {1, 1}};

class LivePlayer: public Player {
    const std::string name;
    Input* input;
    Output* output;
public:
    LivePlayer(std::string  name, const Board* board, Input* input, Output* output);
    Coord get_move() override;
    void report_success(HitResult result) override;
    void report_losses(const Coord& shot, HitResult result, const Board* board) override;
};

class RandomPlayer: public Player {
public:
    explicit RandomPlayer(const Board* board);
    Coord get_move() override;
    void report_success(HitResult result) override;
    void report_losses(const Coord& shot, HitResult result, const Board* board) override;
};


class DummyRectanglePlayer: public Player {
    std::vector<std::vector<bool>> interesting;
    std::queue<Coord> potential_moves;

    Coord find_interesting(int x, int y);
    Coord find_another_hit(const Coord& coord);
    void make_neighbours_potential(const Coord& coord);

public:
    DummyRectanglePlayer(const Board* board);

    Coord get_move() override;
    void report_success(HitResult result) override;
    void report_losses(const Coord& shot, HitResult result, const Board* board) override;
};

#endif //BATTLESHIP_PLAYERS_HPP
