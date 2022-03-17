#include <iostream>

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
public:
    virtual void board_creation(const Board* board, std::vector<const Figure*> ships) = 0;
};

class ConsoleOutput: public Output {
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

    void draw_ship(const Figure* ship) {
        cout << ship->get_coords().size() << "\n";  //TODO
    }
public:
    void board_creation(const Board* board, std::vector<const Figure*> ships) override {
        cout << YELLOW << "Place the following ships:\n";
        for (const Figure* figure : ships)
            draw_ship(figure);
        draw_board_init(board);
    }
};