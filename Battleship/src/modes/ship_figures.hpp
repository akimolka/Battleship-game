#ifndef BATTLESHIP_SHIP_FIGURES_HPP
#define BATTLESHIP_SHIP_FIGURES_HPP

#include <vector>
#include "entities/figure.hpp"

struct ShipFigures {
    inline static const std::vector<Figure> rectangle =
            {{{0, 0}, {0, 0}},  // ◊
             {{0, 0}, {0, 1}},  // ◊◊
             {{0, 0}, {0, 2}},  // ◊◊◊
             {{0, 0}, {0, 3}}}; // ◊◊◊◊

    inline static const std::vector<Figure> triangle =
            {Figure({{0, 0}, {1, 0}, {1, 1}}),
                    // ◊
                    // ◊◊
             Figure({{0, 0}, {1, 0}, {1, 1}, {1, 2}}),
                    // ◊
                    // ◊◊◊
             Figure({{0, 0}, {1, 0}, {1, 1}, {1, 2}, {1, 3}})};
    // ◊
    // ◊◊◊◊

    inline static const Figure zigzag =
            Figure({{0, 0}, {0, 1}, {1, 1}, {1, 2}});
    // ◊◊
    //  ◊◊
    inline static const Figure t_shape =
            Figure({{0, 0}, {0, 1}, {0, 2}, {1, 1}});
    // ◊◊◊
    //  ◊
    inline static const Figure c_shape =
            Figure({{0, 0}, {0, 1}, {1, 0}, {2, 0}, {2, 1}});
    // ◊◊
    // ◊
    // ◊◊

};


#endif //BATTLESHIP_SHIP_FIGURES_HPP
