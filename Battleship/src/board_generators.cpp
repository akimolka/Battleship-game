#include "board_generators.hpp"

bool RandomBoardGenerator::check_figure_coords(const Figure& figure) {
    for (const Coord& coord : figure.get_coords())
        if (coord.x < 0 || coord.y < 0 || coord.x >= size || coord.y >= size)
            return false;
    return true;
}


bool RandomBoardGenerator::place_figure(Figure& figure, Board* board) {
    for (int random_time = 0; random_time < max_random_times; random_time++) {
        int x = rand() % size;
        int y = rand() % size;
        figure.shift_to({x, y});
        if (check_figure_coords(figure) && board->add_ships(figure.get_coords()))
            return true;
    }
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            figure.shift_to({x, y});
            if (check_figure_coords(figure) && board->add_ships(figure.get_coords()))
                return true;
        }
    return false;
}


RandomBoardGenerator::RandomBoardGenerator() {
    std::srand(std::time(nullptr));
}


Board* RandomBoardGenerator::get(const ShipSet* shipset) const {
    Board* board;
    for (int fill_board_try = 0; fill_board_try < max_fill_board_tries; fill_board_try++) {
        board = new Board();
        std::vector<const Figure*> ships_to_place = shipset->get();
        bool board_filled = true;
        while (!ships_to_place.empty()) {
            bool figure_placed = false;

            for (int place_figure_try = 0; place_figure_try < max_place_figure_tries; place_figure_try++) {
                Figure figure(*ships_to_place.back());
                int turn = rand() % 3;
                int reflect = rand() % 2;
                for (int i = 0; i < turn; i++)
                    figure.rotate();
                for (int i = 0; i < reflect; i++)
                    figure.reflect();
                if (place_figure(figure, board)) {
                    figure_placed = true;
                    ships_to_place.pop_back();
                    break;
                }
            }

            if (!figure_placed) {
                board_filled = false;
                break;
            }
        }

        if (board_filled)
            return board;
        else
            board->~Board();
    }
    throw std::exception();
}
